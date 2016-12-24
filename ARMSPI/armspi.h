/* This is the header file for the armspi library, providing an abstraction layer for the SPI interface
 *
 * Author: Alexander Becker
 * Version: 0.0
 */

#ifndef ARMSPI
#define ARMSPI

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/nvic.h>
#include <stdlib.h>

//the defines for the bits in the spi struct status byte
#define SPIBUFFER_EMPTY		(1<<7)
#define SPIBUFFER_FULL		(1<<6)
#define SPI_PACKET_BEING_SENT	(1<<5)
#define SPI_MASTER		(1<<4)

#define PACKETLENGTH = 4
#define TRANSMITBUFFERLENGTH = 4
#define RECIEVEBUFFERLENGHT = 4

// here we define the ports that the different modules operate on
// the ports defined in libopencm3/stm32/include/gpio.h and the
// subsequently used files shouled be used

// below is an example define of a port and pin setup for SPI_0
// #define SPI_0_MISO_PORT GPIO_BANK_SPI1_MISO
// #define SPI_0_MISO_PIN GPIO_SPI1_MISO
//
// #define SPI_0_MOSI_PORT GPIO_BANK_SPI1_MOSI
// #define SPI_0_MOSI_PIN GPIO_SPI1_MOSI
//
// #define SPI_0_SCK_PORT GPIO_BANK_SPI1_SCK
// #define SPI_0_SCK_PIN GPIO_SPI1_SCK
//
// here we define the pins that are used as the SPI pins
#define SPI_0_MISO_PIN
#define SPI_0_MISO_PORT
#define SPI_0_MOSI_PIN
#define SPI_0_MOSI_PORT
#define SPI_0_SCK_PIN
#define SPI_0_SCK_PORT

#define SPI_1_MISO_PIN
#define SPI_1_MISO_PORT
#define SPI_1_MOSI_PIN
#define SPI_1_MOSI_PORT
#define SPI_1_SCK_PIN
#define SPI_1_SCK_PORT

#define SPI_2_MISO_PIN
#define SPI_2_MISO_PORT
#define SPI_2_MOSI_PIN
#define SPI_2_MOSI_PORT
#define SPI_2_SCK_PIN
#define SPI_2_SCK_PORT

#define SPI_3_MISO_PIN
#define SPI_3_MISO_PORT
#define SPI_3_MOSI_PIN
#define SPI_3_MOSI_PORT
#define SPI_3_SCK_PIN
#define SPI_3_SCK_PORT

#define SPI_4_MISO_PIN
#define SPI_4_MISO_PORT
#define SPI_4_MOSI_PIN
#define SPI_4_MOSI_PORT
#define SPI_4_SCK_PIN
#define SPI_4_SCK_PORT

#define SPI_5_MISO_PIN
#define SPI_5_MISO_PORT
#define SPI_5_MOSI_PIN
#define SPI_5_MOSI_PORT
#define SPI_5_SCK_PIN
#define SPI_5_SCK_PORT

//Uncomment, to activate the module
// #define SPI_MODULE_0
// #define SPI_MODULE_1
// #define SPI_MODULE_2
// #define SPI_MODULE_3
// #define SPI_MODULE_4
// #define SPI_MODULE_5
#endif
