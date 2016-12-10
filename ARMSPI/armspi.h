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

// The interface to the data will be the ringbuffer struct defined above, not the arrays.
struct packet rbuffer[RECIEVEBUFFER];
struct packet tbuffer[TRANSMITBUFFERLENGTH];
struct ringbuffer transmitbuffer;
struct ringbuffer recievebuffer;

// TODO this is not finished yet
#ifdef MASTER
void init_spi(void){
	// init of the transmitbuffer
	transmitbuffer.buffersize = TRANSMITBUFFERLENGTH;
	transmitbuffer.start = tbuffer;
	transmitbuffer.head = tbuffer;
	transmitbuffer.tail = transmitbuffer.head+TRANSMITBUFFERLENGTH;

	// init of the recievebuffer
	recievebuffer.buffersize = RECIEVEBUFFERLENGTH;
	recievebuffer.start = rbuffer;
	recievebuffer.head = rbuffer;
	recievebuffer.tail = recievebuffer.head+RECIEVEBUFFERLENGTH;
} 
#endif

#ifdef SLAVE
void init_spi(void){
	// init of the transmitbuffer
	transmitbuffer.buffersize = TRANSMITBUFFERLENGTH;
	transmitbuffer.start = tbuffer;
	transmitbuffer.head = tbuffer;
	transmitbuffer.tail = transmitbuffer.head+TRANSMITBUFFERLENGTH;

	// init of the recievebuffer
	recievebuffer.buffersize = RECIEVEBUFFERLENGTH;
	recievebuffer.start = rbuffer;
	recievebuffer.head = rbuffer;
	recievebuffer.tail = recievebuffer.head+RECIEVEBUFFERLENGTH;
}

