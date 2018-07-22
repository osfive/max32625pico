APP =		max32625pico
ARCH =		arm

CC =		${CROSS_COMPILE}gcc
LD =		${CROSS_COMPILE}ld
OBJCOPY =	${CROSS_COMPILE}objcopy

LDSCRIPT =	${.CURDIR}/ldscript

OBJECTS =	main.o						\
		osfive/sys/arm/maxim/max32625_uart.o		\
		osfive/sys/arm/maxim/max32625_gpio.o		\
		osfive/sys/arm/maxim/max32625_ioman.o		\
		osfive/sys/arm/arm/nvic.o			\
		osfive/sys/arm/arm/trap.o			\
		osfive/sys/arm/arm/exception.o			\
		osfive/sys/kern/subr_prf.o			\
		osfive/sys/kern/subr_console.o			\
		osfive/sys/kern/kern_panic.o			\
		start.o

.include "osfive/lib/libc/Makefile.inc"

CFLAGS =	-mthumb -mcpu=cortex-m4		\
		-nostdlib -fno-builtin-printf	\
		-g -Wall -Werror

all:	compile link binary

clean:
	rm -f ${OBJECTS:M*} ${APP}.elf

.include "osfive/mk/user.mk"
.include "osfive/mk/compile.mk"
.include "osfive/mk/link.mk"
.include "osfive/mk/binutils.mk"
