# max32625pico

This example initializes UART and drives on-board LED.

Connect UART pins as follows:

| MAX32625PICO      | UART-to-USB adapter  |
| ----------------- | -------------------- |
| P0.0 (RX)         | TX                   |
| P0.1 (TX)         | RX                   |

UART baud rate: 115200

### Build under Linux

    $ export CROSS_COMPILE=arm-none-eabi-
    $ git clone --recursive https://github.com/osfive/max32625pico
    $ cd max32625pico
    $ bmake

### Build under FreeBSD

    $ setenv CROSS_COMPILE arm-none-eabi-
    $ git clone --recursive https://github.com/osfive/max32625pico
    $ cd max32625pico
    $ make

![alt text](https://raw.githubusercontent.com/osfive/max32625pico/master/images/max32625pico.jpg)
