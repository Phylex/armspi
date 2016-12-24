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
	uint8_t writeindex;
	uint8_t readindex;
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
volatile struct spi *spi_module_0 = malloc(sizeof(struct spi));
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
volatile struct spi *spi_module_1 = malloc(sizeof(struct spi));
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
volatile struct spi *spi_module_2 = malloc(sizeof(struct spi));
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
volatile struct spi *spi_module_3 = malloc(sizeof(struct spi));
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
volatile struct spi *spi_module_4 = malloc(sizeof(struct spi));
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
volatile struct spi *spi_module_5 = malloc(sizeof(struct spi));
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
		spi_enable(SPI4);
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
	#ifdef SPI_MODULE_0

	}
}

// helper funktions -----------------------------------------------------------
void set_SS_pin_high(){
// TODO still need to implement
}

void set_SS_pin_low(){
// TODO still need to implement
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
	spimodule.rxbuffer.head.contents[spimodule.rxbuffer.head.writeindex] = uint8_t(rxdata);
	spimodule.rxbuffer.head.writeindex++;
	if(spimodule.status & SPI_PACKET_BEING_SENT){
		spi_write(spi, uint16_t(spimodule.txbuffer.tail.contents[spimodule.txbuffer.tail.readindex]));
		spimodule.txbuffer.tail.readindex++;
		if(spimodule.txbuffer.tail.readindex < spimodule.txbuffer.tail.writeindex){
			return 0;
		}
		else{
			spimodule.status &= ~SPI_PACKET_BEING_SENT;
			spimodule.txbuffer.tail.writeindex = 0;
			spimodule.txbuffer.tail.readindex = 0;
			return 0;
		}
	}
	else{
		set_SS_pin_high(pin);
		increment_bufferpointer(spimodule.rxbuffer.head, spimodule.rxbuffer);
		increment_bufferpointer(spimodule.txbuffer.tail, spimodule.txbuffer);
		if(spimodule.rxbuffer.head == spimodule.rxbuffer.tail){
			spimodule.rxbuffer.tail.writeindex = 0;
			spimodule.rxbuffer.tail.readindex = 0;
			increment_bufferpointer(spimodule.rxbuffer.tail, spimodule.rxbuffer);
			spimodule.rxbuffer.tail.writeindex = 0;
			spimodule.rxbuffer.tail.readindex = 0;
		}
		if(spimodule.txbuffer.tail == spimodule.txbuffer.head){
			spimodule.status |= SPIBUFFER_EMPTY;
		}
		else{
			set_SS_pin_low(pin);
			if(spimodule.txbuffer.tail.writeindex > 1){
				spimodule.status |= SPI_PACKET_BEING_SENT;
			}
			spi_write(spi, spimodule.txbuffer.tail.contents[spimodule.txbuffer.tail.readindex]);
			return 0;
		}
	}
}

uint16_t spi_irq_rxdata_handler(struct spi *spimodule, uint8_t data, uint32_t spi){
	uint8_t tmprxdata = spi_read(spi);
	for(uint8_t i=0; i>=MAXLOOP; i++){
		if()
	}
}

#ifdef SPI_MODULE_0
void spi1_isr(void){
	if(spi_module_0.status & SPI_MASTER){
		spi_irq_master_handler(spi_module_0);
	}
	else{
		spi_irq_slave_handler(spi_module_0);
	}
}

#ifdef SPI_MODULE_1
void spi2_isr(void){
	if(spi_module_1.status & SPI_MASTER){
		spi_irq_master_handler(spi_module_1);
	}
	else{
		spi_irq_slave_handler(spi_module_1);
	}
}

#ifdef SPI_MODULE_2
void spi3_isr(void){
	if(spi_module_2.status & SPI_MASTER){
		spi_irq_master_handler(spi_module_2);
	}
	else{
		spi_irq_slave_handler(spi_module_2);
	}
}

#ifdef SPI_MODULE_3
void spi4_isr(void){
	if(spi_module_3.status & SPI_MASTER){
		spi_irq_master_handler(spi_module_3);
	}
	else{
		spi_irq_slave_handler(spi_module_3);
	}
}

#ifdef SPI_MODULE_4
void spi5_isr(void){
	if(spi_module_4.status & SPI_MASTER){
		spi_irq_master_handler(spi_module_4);
	}
	else{
		spi_irq_slave_handler(spi_module_4);
	}
}

#ifdef SPI_MODULE_5
void spi6_isr(void){
	if(spi_module_5.status & SPI_MASTER){
		spi_irq_master_handler(spi_module_5);
	}
	else{
		spi_irq_slave_handler(spi_module_5);
	}
}
