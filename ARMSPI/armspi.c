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
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/nvic.h>
#include <stdlib.h>

struct packet {
	uint8_t contents[PACKETLENGTH];
	uint8_t plength;
	uint8_t sendbyte;
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
	struct ringbuffer rxbuffer;
	struct ringbuffer txbuffer;
	uint8_t status;
}

// if the module is activated the space for the buffers is allocated
// and initialize the data structures

#ifdef SPI_MODULE_0
struct spi *spi_module_0 = malloc(sizeof(struct spi));
// transmit buffer initialization
spi_module_0.txbuffer.start = spi_module_0.tbuffer;
spi_module_0.txbuffer.head = spi_module_0.tbuffer;
spi_module_0.txbuffer.tail = spi_module_0.tbuffer;
spi_module_0.txbuffer.buffersize = TRANSMITBUFFERLENGTH;
// recieve buffer initialization
spi_module_0.rxbuffer.start = spi_module_0.rbuffer;
spi_module_0.rxbuffer.head = spi_module_0.rbuffer;
spi_module_0.rxbuffer.tail = spi_module_0.rbuffer;
spi_module_0.rxbuffer.buffersize = RECIEVEBUFFERLENGHT;
#endif

#ifdef SPI_MODULE_1
struct spi *spi_module_1 = malloc(sizeof(struct spi));
// transmit buffer initialization
spi_module_1.txbuffer.start = spi_module_1.tbuffer;
spi_module_1.txbuffer.head = spi_module_1.tbuffer;
spi_module_1.txbuffer.tail = spi_module_1.tbuffer;
spi_module_1.txbuffer.buffersize = TRANSMITBUFFERLENGTH;
// recieve buffer initialization
spi_module_1.rxbuffer.start = spi_module_1.rbuffer;
spi_module_1.rxbuffer.head = spi_module_1.rbuffer;
spi_module_1.rxbuffer.tail = spi_module_1.rbuffer;
spi_module_1.rxbuffer.buffersize = RECIEVEBUFFERLENGHT;
#endif

#ifdef SPI_MODULE_2
struct spi *spi_module_2 = malloc(sizeof(struct spi));
// transmit buffer initialization
spi_module_2.txbuffer.start = spi_module_2.tbuffer;
spi_module_2.txbuffer.head = spi_module_2.tbuffer;
spi_module_2.txbuffer.tail = spi_module_2.tbuffer;
spi_module_2.txbuffer.buffersize = TRANSMITBUFFERLENGTH;
// recieve buffer initialization
spi_module_2.rxbuffer.start = spi_module_2.rbuffer;
spi_module_2.rxbuffer.head = spi_module_2.rbuffer;
spi_module_2.rxbuffer.tail = spi_module_2.rbuffer;
spi_module_2.rxbuffer.buffersize = RECIEVEBUFFERLENGHT;
#endif

#ifdef SPI_MODULE_3
// transmit buffer initialization
struct spi *spi_module_3 = malloc(sizeof(struct spi));
spi_module_3.txbuffer.start = spi_module_3.tbuffer;
spi_module_3.txbuffer.head = spi_module_3.tbuffer;
spi_module_3.txbuffer.tail = spi_module_3.tbuffer;
spi_module_3.txbuffer.buffersize = TRANSMITBUFFERLENGTH;
// recieve buffer initialization
spi_module_3.rxbuffer.start = spi_module_3.rbuffer;
spi_module_3.rxbuffer.head = spi_module_3.rbuffer;
spi_module_3.rxbuffer.tail = spi_module_3.rbuffer;
spi_module_3.rxbuffer.buffersize = RECIEVEBUFFERLENGHT;
#endif

#ifdef SPI_MODULE_4
struct spi *spi_module_4 = malloc(sizeof(struct spi));
// transmit buffer initialization
spi_module_4.txbuffer.start = spi_module_4.tbuffer;
spi_module_4.txbuffer.head = spi_module_4.tbuffer;
spi_module_4.txbuffer.tail = spi_module_4.tbuffer;
spi_module_4.txbuffer.buffersize = TRANSMITBUFFERLENGTH;
// recieve buffer initialization
spi_module_4.rxbuffer.start = spi_module_4.rbuffer;
spi_module_4.rxbuffer.head = spi_module_4.rbuffer;
spi_module_4.rxbuffer.tail = spi_module_4.rbuffer;
spi_module_4.rxbuffer.buffersize = RECIEVEBUFFERLENGHT;
#endif

#ifdef SPI_MODULE_5
struct spi *spi_module_5 = malloc(sizeof(struct spi));
// transmit buffer initialization
spi_module_5.txbuffer.start = spi_module_5.tbuffer;
spi_module_5.txbuffer.head = spi_module_5.tbuffer;
spi_module_5.txbuffer.tail = spi_module_5.tbuffer;
spi_module_5.txbuffer.buffersize = TRANSMITBUFFERLENGTH;
// recieve buffer initialization
spi_module_5.rxbuffer.start = spi_module_5.rbuffer;
spi_module_5.rxbuffer.head = spi_module_5.rbuffer;
spi_module_5.rxbuffer.tail = spi_module_5.rbuffer;
spi_module_5.rxbuffer.buffersize = RECIEVEBUFFERLENGHT;
#endif

// TODO this is not finished yet
void init_spi(uint8_t mode, uint8_t spi_module){
	// set up the Hardware module
	if(mode == SPI_MASTER){
		#ifdef SPI_MODULE_0
		spi_init_master(SPI1, SPI_CR1_BAUDRATE_FPCLK_DIV_8, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE
				SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_enable_tx_buffer_empty(SPI1);
		spi_enable(SPI0);
		#endif

		#ifdef SPI_MODULE_1
		spi_init_master(SPI2, SPI_CR1_BAUDRATE_FPCLK_DIV_8, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE
				SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_enable_tx_buffer_empty(SPI2);
		spi_enable(SPI1);
		#endif

		#ifdef SPI_MODULE_2
		spi_init_master(SPI3, SPI_CR1_BAUDRATE_FPCLK_DIV_8, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE
				SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_enable_tx_buffer_empty(SPI3);
		spi_enable(SPI2);
		#endif

		#ifdef SPI_MODULE_3
		spi_init_master(SPI4, SPI_CR1_BAUDRATE_FPCLK_DIV_8, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE
				SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_enable_tx_buffer_empty(SPI4);
		spi_enable(SPI3);
		#endif

		#ifdef SPI_MODULE_4
		spi_init_master(SPI5, SPI_CR1_BAUDRATE_FPCLK_DIV_8, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE
				SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_enable_tx_buffer_empty(SPI5);
		spi_enable(SPI4);
		#endif

		#ifdef SPI_MODULE_5
		spi_init_master(SPI6, SPI_CR1_BAUDRATE_FPCLK_DIV_8, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE
				SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_enable_tx_buffer_empty(SPI6);
		spi_enable(SPI5);
		#endif
	}
	else if(mode == SPI_SLAVE){
		// TODO follow the procedure on page 697 of the manual
	}
}

// helper funktions -----------------------------------------------------------
void set_SS_pin_high(){
// TODO still need to implement
}

void set_SS_pin_low(){
// TODO still need to implement
}

// the first byte of the 16Bit is the "flag-register"
uint16_t get_next_byte_from_packet(struct packet packet){
	uint8_t status = 0;
	if(packet.sendbyte >= packet.plength){
		packet.sendbyte = 0;
		packet.plength = 0;
		status  |= SPI_SENDING_PACKET;
		return 0 | (status<<8);
	}
	else{
		uint8_t returnbyte;
		returnbyte = packet.contents[packet.sendbyte]
		sendbyte ++;
		return returnbyte;
	}
}

// the returned byte is the status of the operation
uint8_t write_byte_into_packet(struct packet *packet, uint8_t data){
	uint8_t status = 0;
	if(packet.plength >= PACKETLENGTH){
		status |= RX_PACKET_FULL;
		return status;
	}
	else{
		packet.contents[packet.plength] = data;
		return status;
	}
}

void increment_bufferpointer(struct packet *pointer, struct ringbuffer *buffer){
	pointer ++;
	if(pointer >= buffer.start+buffersize){
		pointer = buffer.start;
	}
}

// end helper functions -------------------------------------------------------


// the first byte of the 16Bit is the "flag-register"
uint16_t spi_irq_master_handler(struct spi *spimodule, uint32_t spi, uint32_t pin){
	rxdata = spi_read(spi);
	spimodule.rxbuffer.head.contents[spimodule.rxbuffer.head.plength] = uint8_t(rxdata);
	spimodule.rxbuffer.head.plength++;
	if(spimodule.status & SPI_PACKET_BEING_SENT){
		spi_write(spi, uint16_t(spimodule.txbuffer.tail.contents[spimodule.txbuffer.tail.sendbyte]));
		spimodule.txbuffer.tail.sendbyte++;
		if(spimodule.txbuffer.tail.sendbyte < spimodule.txbuffer.tail.plength){
			return 0;
		}
		else{
			spimodule.status &= ~SPI_PACKET_BEING_SENT;
			spimodule.txbuffer.tail.plength = 0;
			spimodule.txbuffer.tail.sendbyte = 0;
			return 0;
		}
	}
	else{
		set_SS_pin_high(pin);
		increment_bufferpointer(spimodule.rxbuffer.head, spimodule.rxbuffer);
		increment_bufferpointer(spimodule.txbuffer.tail, spimodule.txbuffer);
		if(spimodule.rxbuffer.head == spimodule.rxbuffer.tail){
			spimodule.rxbuffer.tail.plength = 0;
			spimodule.rxbuffer.tail.sendbyte = 0;
			increment_bufferpointer(spimodule.rxbuffer.tail, spimodule.rxbuffer);
		}
		if(spimodule.txbuffer.tail == spimodule.txbuffer.head){
			spimodule.status |= SPIBUFFER_EMPTY;
		}
		else{
			set_SS_pin_low(pin);
			if(spimodule.txbuffer.tail.plength > 1){
				spimodule.status |= SPI_PACKET_BEING_SENT;
			}
			spi_write(spi, spimodule.txbuffer.tail.contents[spimodule.txbuffer.tail.sendbyte]);
			return 0;
		}
	}
}

uint16_t spi_irq_rxdata_handler(struct ringbuffer *rxbuffer, uint8_t data){
	status = write_byte_into_packet(data, rxbuffer.head);
	if(status != 0){
		if(status & RX_PACKET_FULL){
			
		}
	}
}

