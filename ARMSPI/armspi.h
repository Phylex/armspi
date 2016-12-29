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
#include <libopencm3/cm3/nvic.h>

//the defines for the bits in the spi struct status byte
#define SPIBUFFER_EMPTY		(1<<7)
#define SPIBUFFER_FULL		(1<<6)
#define SPI_MASTER		(1<<5)
#define SPI_PACKET_RECIEVED	(1<<4)

#define PACKETLENGTH 4
#define TRANSMITBUFFERLENGTH 4
#define RECIEVEBUFFERLENGHT 4
#define MAXLOOP 10

//Uncomment, to activate the module
// #define SPI_MODULE_0
// #define SPI_MODULE_1
// #define SPI_MODULE_2
// #define SPI_MODULE_3
// #define SPI_MODULE_4
// #define SPI_MODULE_5

// Now we define how many slaves are connected to the
#define SPI_0_CONNECTED_SLAVES 1
#define SPI_1_CONNECTED_SLAVES 1
#define SPI_2_CONNECTED_SLAVES 1
#define SPI_3_CONNECTED_SLAVES 1
#define SPI_4_CONNECTED_SLAVES 1
#define SPI_5_CONNECTED_SLAVES 1

// and the corresponding port and pin registers
// the SS lines for Slave 0 are all allready set to the 
//
#define SPI_0_SLAVE_0_PORT GPIO_BANK_SPI1_NSS 
#define SPI_0_SLAVE_0_PIN GPIO_SPI1_NSS
//#define SPI_0_SLAVE_0_PORT
//#define SPI_0_SLAVE_0_PIN

#define SPI_1_SLAVE_0_PORT GPIO_BANK_SPI2_NSS
#define SPI_1_SLAVE_0_PIN GPIO_SPI2_NSS
//#define SPI_1_SLAVE_0_PORT
//#define SPI_1_SLAVE_0_PIN

#define SPI_2_SLAVE_0_PORT GPIO_BANK_SPI3_NSS
#define SPI_2_SLAVE_0_PIN GPIO_SPI3_NSS
//#define SPI_2_SLAVE_0_PORT
//#define SPI_2_SLAVE_0_PIN

#define SPI_3_SLAVE_0_PORT GPIO_BANK_SPI4_NSS  
#define SPI_3_SLAVE_0_PIN GPIO_SPI4_NSS
//#define SPI_3_SLAVE_0_PORT
//#define SPI_3_SLAVE_0_PIN

#define SPI_4_SLAVE_0_PORT GPIO_BANK_SPI5_NSS 
#define SPI_4_SLAVE_0_PIN GPIO_SPI5_NSS
//#define SPI_4_SLAVE_0_PORT
//#define SPI_4_SLAVE_0_PIN

#define SPI_5_SLAVE_0_PORT GPIO_BANK_SPI6_NSS 
#define SPI_5_SLAVE_0_PIN GPIO_SPI6_NSS
//#define SPI_5_SLAVE_0_PORT
//#define SPI_5_SLAVE_0_PIN

// here we define the ports that the different modules operate on
// the ports defined in libopencm3/stm32/include/gpio.h and the
// subsequently used files shouled be used

#define SPI_0_MISO_PIN   GPIO_BANK_SPI1_MISO
#define SPI_0_MISO_PORT  GPIO_SPI1_MISO
#define SPI_0_MOSI_PIN   GPIO_BANK_SPI1_MOSI
#define SPI_0_MOSI_PORT  GPIO_SPI1_MOSI
#define SPI_0_SCK_PIN    GPIO_BANK_SPI1_SCK
#define SPI_0_SCK_PORT   GPIO_SPI1_SCK

#define SPI_1_MISO_PIN   GPIO_BANK_SPI2_MISO
#define SPI_1_MISO_PORT  GPIO_SPI2_MISO
#define SPI_1_MOSI_PIN   GPIO_BANK_SPI2_MOSI
#define SPI_1_MOSI_PORT  GPIO_SPI2_MOSI
#define SPI_1_SCK_PIN    GPIO_BANK_SPI2_SCK
#define SPI_1_SCK_PORT   GPIO_SPI2_SCK

#define SPI_2_MISO_PIN   GPIO_BANK_SPI3_MISO
#define SPI_2_MISO_PORT  GPIO_SPI3_MISO     
#define SPI_2_MOSI_PIN   GPIO_BANK_SPI3_MOSI
#define SPI_2_MOSI_PORT  GPIO_SPI3_MOSI
#define SPI_2_SCK_PIN    GPIO_BANK_SPI3_SCK
#define SPI_2_SCK_PORT   GPIO_SPI3_SCK

#define SPI_3_MISO_PIN   GPIO_BANK_SPI4_MISO
#define SPI_3_MISO_PORT  GPIO_SPI4_MISO     
#define SPI_3_MOSI_PIN   GPIO_BANK_SPI4_MOSI
#define SPI_3_MOSI_PORT  GPIO_SPI4_MOSI
#define SPI_3_SCK_PIN    GPIO_BANK_SPI4_SCK
#define SPI_3_SCK_PORT   GPIO_SPI4_SCK

#define SPI_4_MISO_PIN   GPIO_BANK_SPI5_MISO
#define SPI_4_MISO_PORT  GPIO_SPI5_MISO     
#define SPI_4_MOSI_PIN   GPIO_BANK_SPI5_MOSI
#define SPI_4_MOSI_PORT  GPIO_SPI5_MOSI
#define SPI_4_SCK_PIN    GPIO_BANK_SPI5_SCK
#define SPI_4_SCK_PORT   GPIO_SPI5_SCK

#define SPI_5_MISO_PIN   GPIO_BANK_SPI6_MISO
#define SPI_5_MISO_PORT  GPIO_SPI6_MISO     
#define SPI_5_MOSI_PIN   GPIO_BANK_SPI6_MOSI
#define SPI_5_MOSI_PORT  GPIO_SPI6_MOSI
#define SPI_5_SCK_PIN    GPIO_BANK_SPI6_SCK
#define SPI_5_SCK_PORT   GPIO_SPI6_SCK


#endif
