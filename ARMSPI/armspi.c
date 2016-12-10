/*
 * Header File for the armspi library that implements a packet based abstraction layer
 * for the SPI interface and allows the user to simply send a packet overthe SPI and
 * not have to worry about the details.
 *
 * Author: Alexander Becker galax.becker@live.de
 * Version: 0.0
 */

#include "armspi.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

struct packet {
	uint8_t contents[PACKETLENGTH];
	uint8_t plength;
};

struct ringbuffer {
	uint32_t buffersize;
	struct packet *start;
	struct packet *head;
	struct packet *tail;
};

struct spi {
	uint8_t packet rbuffer[RECIEVEBUFFERLENGHT];
	struct packet tbuffer[TRANSMITBUFFERLENGTH];
	struct ringbuffer recievebuffer;
	struct ringbuffer transmitbuffer;
	uint8_t status;
}

// The interface to the data will be the ringbuffer struct defined above, not the arrays.
volatile struct spi[DEVICE_AMONT];

// TODO this is not finished yet
void init_spi(uint8_t mode){
	for(i=0;i<DEVICE_AMOUNT,i++){
		// set up the recievebuffer pointers
		spi[i].recievebuffer.start = spi[i].rbuffer;
		spi[i].recievebuffer.head = spi[i].rbuffer;
		spi[i].recievebuffer.tail = spi[i].rbuffer;
		
		// set up the transmitbuffer pointers
		spi[i].transmitbuffer.start = spi[i].tbuffer;
		spi[i].transmitbuffer.head = spi[i].tbuffer;
		spi[i].transmitbuffer.tail = spi[i].tbuffer;
	}
	// Now the SPI is initialized following the instructions of the Datasheet page 698
	if(mode == SPI_MASTER){
		// set the baude clock rate in SPI_CR1 (BR[0:2])
		//
		// set the CPOL and CPHA
		//
		// set the Data frame format
		//
		// define LSB or MSB first in the SPI_CR1 register
		//
		// configure the NSS Bit (Slave Select)
		//
		// set the MSTR (for we are in master mode) bit and the SPE bit
	}
	else if(mode == SPI_SLAVE){
		// TODO follow the procedure on page 697 of the manual
	}
}

