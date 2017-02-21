/*-
 * Copyright (c) 1999 Luoqi Chen.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/11.0/sys/dev/aic/aic_cbus.c 298431 2016-04-21 19:40:10Z pfg $");

#include <sys/param.h>
#include <sys/callout.h>
#include <sys/kernel.h>
#include <sys/lock.h>
#include <sys/module.h>
#include <sys/mutex.h>
#include <sys/bus.h>

#include <machine/bus.h>
#include <machine/resource.h>
#include <sys/rman.h>
 
#include <isa/isavar.h>
#include <dev/aic/aic6360reg.h>
#include <dev/aic/aicvar.h>
  
struct aic_isa_softc {
	struct	aic_softc sc_aic;
	struct	resource *sc_port;
	struct	resource *sc_irq;
	struct	resource *sc_drq;
	void	*sc_ih;
};

static int aic_isa_alloc_resources(device_t);
static void aic_isa_release_resources(device_t);
static int aic_isa_probe(device_t);
static int aic_isa_attach(device_t);

static u_int aic_isa_ports[] = { 0x1840 };

#define	AIC_ISA_NUMPORTS nitems(aic_isa_ports)
#define	AIC_ISA_PORTSIZE 0x20

#define	AIC98_GENERIC		0x00
#define	AIC98_NEC100		0x01
#define	AIC_TYPE98(x)		(((x) >> 16) & 0x01)

static bus_addr_t aicport_generic[AIC_ISA_PORTSIZE] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
};
static bus_addr_t aicport_100[AIC_ISA_PORTSIZE] = {
	0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e,
	0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e,
	0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e,
	0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e,
};

static struct isa_pnp_id aic_ids[] = {
	{ 0xa180a3b8, "NEC PC9801-100" },
 	{ 0 }
};

static int
aic_isa_alloc_resources(device_t dev)
{
	struct aic_isa_softc *sc = device_get_softc(dev);
	int rid;
	bus_addr_t *bs_iat;

	if ((isa_get_logicalid(dev) == 0xa180a3b8) ||
	    (AIC_TYPE98(device_get_flags(dev)) == AIC98_NEC100))
		bs_iat = aicport_100;
	else
		bs_iat = aicport_generic;

	sc->sc_port = sc->sc_irq = sc->sc_drq = NULL;

	rid = 0;
	sc->sc_port = isa_alloc_resourcev(dev, SYS_RES_IOPORT, &rid,
					  bs_iat, AIC_ISA_PORTSIZE, RF_ACTIVE);
	if (!sc->sc_port) {
		device_printf(dev, "I/O port allocation failed\n");
		return (ENOMEM);
	}
	isa_load_resourcev(sc->sc_port, bs_iat, AIC_ISA_PORTSIZE);
	mtx_init(&sc->sc_aic.lock, "aic", NULL, MTX_DEF);

	if (isa_get_irq(dev) != -1) {
		rid = 0;
		sc->sc_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
						    RF_ACTIVE);
		if (!sc->sc_irq) {
			device_printf(dev, "IRQ allocation failed\n");
			aic_isa_release_resources(dev);
			return (ENOMEM);
		}
	}

	if (isa_get_drq(dev) != -1) {
		rid = 0;
		sc->sc_drq = bus_alloc_resource_any(dev, SYS_RES_DRQ, &rid,
						    RF_ACTIVE);
		if (!sc->sc_drq) {
			device_printf(dev, "DRQ allocation failed\n");
			aic_isa_release_resources(dev);
			return (ENOMEM);
		}
	}

	sc->sc_aic.dev = dev;
	sc->sc_aic.res = sc->sc_port;
	return (0);
}

static void
aic_isa_release_resources(device_t dev)
{
	struct aic_isa_softc *sc = device_get_softc(dev);

	if (sc->sc_port)
		bus_release_resource(dev, SYS_RES_IOPORT, 0, sc->sc_port);
	if (sc->sc_irq)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_irq);
	if (sc->sc_drq)
		bus_release_resource(dev, SYS_RES_DRQ, 0, sc->sc_drq);
	sc->sc_port = sc->sc_irq = sc->sc_drq = NULL;
	mtx_destroy(&sc->sc_aic.lock);
}

static int
aic_isa_probe(device_t dev)
{
	struct aic_isa_softc *sc = device_get_softc(dev);
	struct aic_softc *aic = &sc->sc_aic;
	int numports, i;
	u_int port, *ports;
	u_int8_t porta;

	if (ISA_PNP_PROBE(device_get_parent(dev), dev, aic_ids) == ENXIO)
		return (ENXIO);

	port = isa_get_port(dev);
	if (port != -1) {
		ports = &port;
		numports = 1;
	} else {
		ports = aic_isa_ports;
		numports = AIC_ISA_NUMPORTS;
	}

	for (i = 0; i < numports; i++) {
		if (bus_set_resource(dev, SYS_RES_IOPORT, 0, ports[i], 1))
			continue;
		if (aic_isa_alloc_resources(dev))
			continue;
		if (aic_probe(aic) == 0)
			break;
		aic_isa_release_resources(dev);
	}

	if (i == numports)
		return (ENXIO);

	porta = aic_inb(aic, PORTA);
	aic_isa_release_resources(dev);
	if (isa_get_irq(dev) == -1)
		bus_set_resource(dev, SYS_RES_IRQ, 0, PORTA_IRQ(porta), 1);
	if ((aic->flags & AIC_DMA_ENABLE) && isa_get_drq(dev) == -1)
		bus_set_resource(dev, SYS_RES_DRQ, 0, PORTA_DRQ(porta), 1);
	device_set_desc(dev, "Adaptec 6260/6360 SCSI controller");
	return (0);
}

static int
aic_isa_attach(device_t dev)
{
	struct aic_isa_softc *sc = device_get_softc(dev);
	struct aic_softc *aic = &sc->sc_aic;
	int error;

	error = aic_isa_alloc_resources(dev);
	if (error) {
		device_printf(dev, "resource allocation failed\n");
		return (error);
	}

	error = aic_attach(aic);
	if (error) {
		device_printf(dev, "attach failed\n");
		aic_isa_release_resources(dev);
		return (error);
	}

	error = bus_setup_intr(dev, sc->sc_irq, INTR_TYPE_CAM | INTR_ENTROPY |
	    INTR_MPSAFE, NULL, aic_intr, aic, &sc->sc_ih);
	if (error) {
		device_printf(dev, "failed to register interrupt handler\n");
		aic_isa_release_resources(dev);
		return (error);
	}
	return (0);
}

static int
aic_isa_detach(device_t dev)
{
	struct aic_isa_softc *sc = device_get_softc(dev);
	struct aic_softc *aic = &sc->sc_aic;
	int error;

	error = aic_detach(aic);
	if (error) {
		device_printf(dev, "detach failed\n");
		return (error);
	}

	error = bus_teardown_intr(dev, sc->sc_irq, sc->sc_ih);
	if (error) {
		device_printf(dev, "failed to unregister interrupt handler\n");
	}

	aic_isa_release_resources(dev);
	return (0);
}

static device_method_t aic_isa_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe,		aic_isa_probe),
	DEVMETHOD(device_attach,	aic_isa_attach),
	DEVMETHOD(device_detach,	aic_isa_detach),
	{ 0, 0 }
};

static driver_t aic_isa_driver = {
	"aic",
	aic_isa_methods, sizeof(struct aic_isa_softc),
};

extern devclass_t aic_devclass;

MODULE_DEPEND(aic, cam, 1,1,1);
DRIVER_MODULE(aic, isa, aic_isa_driver, aic_devclass, 0, 0);
