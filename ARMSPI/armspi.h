/* This is the header file for the armspi library, providing an abstraction layer for the SPI interface
 *
 * Author: Alexander Becker
 * Version: 0.0
 */

#ifndef ARMSPI
#define ARMSPI

//the defines for the bits in the spi struct status byte
#define SPIBUFFER_EMPTY		(1<<7)
#define SPIBUFFER_FULL		(1<<6)
#define SPI_PACKET_BEING_SENT	(1<<5)

#define PACKETLENGTH = 4
#define TRANSMITBUFFERLENGTH = 4
#define RECIEVEBUFFERLENGHT = 4

//Uncomment, to activate the module
#define SPI_MODULE_0
#define SPI_MODULE_1
// #define SPI_MODULE_2
// #define SPI_MODULE_3
// #define SPI_MODULE_4
// #define SPI_MODULE_5

#endif
