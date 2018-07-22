/*-
 * Copyright (c) 2018 Ruslan Bukin <br@bsdpad.com>
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
#include <sys/console.h>
#include <sys/systm.h>
#include <sys/malloc.h>

#include <machine/frame.h>

#include <arm/arm/nvic.h>
#include <arm/maxim/max32625.h>

struct max32625_uart_softc uart_sc;
struct max32625_gpio_softc gpio_sc;
struct max32625_ioman_softc ioman_sc;

void app_main(void);

#define	LEDS_PORT	2
#define	LED_RED		4
#define	LED_GREEN	5
#define	LED_BLUE	6
#define	UART_BAUDRATE	115200

static void
uart_putchar(int c, void *arg)
{
	struct max32625_uart_softc *sc;
 
	sc = arg;
 
	if (c == '\n')
		max32625_uart_putc(sc, '\r');

	max32625_uart_putc(sc, c);
}

void
app_main(void)
{

	max32625_gpio_init(&gpio_sc, GPIO_BASE);
	max32625_gpio_mode(&gpio_sc, LEDS_PORT, LED_RED, MODE_OPEN_DRAIN);
	max32625_gpio_mode(&gpio_sc, LEDS_PORT, LED_GREEN, MODE_OPEN_DRAIN);
	max32625_gpio_mode(&gpio_sc, LEDS_PORT, LED_BLUE, MODE_OPEN_DRAIN);
	max32625_gpio_out_val(&gpio_sc, LEDS_PORT, LED_BLUE, 0);

	max32625_ioman_init(&ioman_sc, IOMAN_BASE);
	max32625_ioman_write(&ioman_sc, IOMAN_UART_REQ(0), UART_REQ_IO_REQ);

	max32625_uart_init(&uart_sc, UART0_BASE, UART0_FIFO_TX_BASE,
	    UART0_FIFO_RX_BASE, 6000000, UART_BAUDRATE);
	console_register(uart_putchar, (void *)&uart_sc);

	while (1)
		printf("Hello world!\n");
}
