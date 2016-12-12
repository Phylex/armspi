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

// TODO rework this after deciding on a good deesign sheme
uint8_t spi_irq_txdata_handler(struct spi *spimodule){
	// the Send part
	// first we perform the Check and redirect stuff
	if(spimodule.txbuffer.tail.sendbyte >= spimodule.txbuffer.tail.plength){
		// here the current packet is empty and we assume we have sent the entire packet and swich
		spimodule.txbuffer.tail.sendbyte = 0;
		spimodule.txbuffer.tail.plength = 0;
		// now we check if the buffer is empty
		if(spimodule.txbuffer.tail + 1 >= spimodule.txbuffer.start + spimodule.txbuffer.buffersize){
			if(spimodule.txbuffer.head == spimodule.txbuffer.start){
				spimodule.status |= SPIBUFFER_EMPTY;
				return 0;
			}
			else{
				spimodule.txbuffer.tail = spimodule.txbuffer.start;
			}
		}
		else{
			if(spimodule.txbuffer.head == spimodule.txbuffer.start){
				spimodule.status |= SPIBUFFER_EMPTY;
				return 0;
			}
			else{
				spimodule.txbuffer.tail ++;
			}
		}
		return spimodule.txbuffer.tail.contents[spimodule.txbuffer.tail.sendbyte];
	}
	else{
		// we are stil sending the same packet and have mot reached its end yet, so we continue sending
		returnbyte = spimodule.txbuffer.tail.content[ spimodule.txbuffer.tail.sendbyte ];
		spimodule.txbuffer.tail.sendbyte ++;
		return returnbyte;
	}
}

void spi_irq_rxdata_handler(struct spi *spimodule, uint8_t data){
	if()
}

