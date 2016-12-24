/*
 * Header File for the armspi library that implements a packet based abstraction layer
 * for the SPI interface and allows the user to simply send a packet overthe SPI and
 * not have to worry about the details.
 *
 * Author: Alexander Becker galax.becker@live.de
 * Version: 0.0
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/nvic.h>
#include <stdlib.h>
#include "armspi.h"

struct hardware_pin {
	uint32_t port;
	uint32_t pin;
}

#ifdef SPI_MODULE_0
static struct hardware_pin connected_slaves_0[] =	{
	{.port = SPI_0_SLAVE_0_PORT, .pin = SPI_0_SLAVE_0_PIN}
#ifdef SPI_0_SLAVE_1_PORT
	{.port = SPI_0_SLAVE_1_PORT, .pin = SPI_0_SLAVE_1_PIN}
#endif
#ifdef SPI_0_SLAVE_2_PORT
	{.port = SPI_0_SLAVE_2_PORT, .pin = SPI_0_SLAVE_2_PIN}
#endif
#ifdef SPI_0_SLAVE_3_PORT
	{.port = SPI_0_SLAVE_3_PORT, .pin = SPI_0_SLAVE_3_PIN}
#endif
#ifdef SPI_0_SLAVE_4_PORT
	{.port = SPI_0_SLAVE_4_PORT, .pin = SPI_0_SLAVE_4_PIN}
#endif
}
#endif

#ifdef SPI_MODULE_1
static struct hardware_pin connected_slaves_1[] =	{
	{.port = SPI_1_SLAVE_0_PORT, .pin = SPI_0_SLAVE_0_PIN}
#ifdef SPI_1_SLAVE_1_PORT
	{.port = SPI_1_SLAVE_1_PORT, .pin = SPI_1_SLAVE_1_PIN}
#endif
#ifdef SPI_1_SLAVE_2_PORT
	{.port = SPI_1_SLAVE_2_PORT, .pin = SPI_1_SLAVE_2_PIN}
#endif
#ifdef SPI_1_SLAVE_3_PORT
	{.port = SPI_1_SLAVE_3_PORT, .pin = SPI_1_SLAVE_3_PIN}
#endif
#ifdef SPI_1_SLAVE_4_PORT
	{.port = SPI_1_SLAVE_4_PORT, .pin = SPI_1_SLAVE_4_PIN}
#endif
}
#endif

#ifdef SPI_MODULE_2
static struct hardware_pin connected_slaves_2[] =	{
	{.port = SPI_2_SLAVE_0_PORT, .pin = SPI_2_SLAVE_0_PIN}
#ifdef SPI_2_SLAVE_1_PORT
	{.port = SPI_2_SLAVE_1_PORT, .pin = SPI_2_SLAVE_1_PIN}
#endif
#ifdef SPI_2_SLAVE_2_PORT
	{.port = SPI_2_SLAVE_2_PORT, .pin = SPI_2_SLAVE_2_PIN}
#endif
#ifdef SPI_2_SLAVE_3_PORT
	{.port = SPI_2_SLAVE_3_PORT, .pin = SPI_2_SLAVE_3_PIN}
#endif
#ifdef SPI_2_SLAVE_4_PORT
	{.port = SPI_2_SLAVE_4_PORT, .pin = SPI_2_SLAVE_4_PIN}
#endif
}
#endif

#ifdef SPI_MODULE_3
static struct hardware_pin connected_slaves_3[] =	{
	{.port = SPI_3_SLAVE_0_PORT, .pin = SPI_3_SLAVE_0_PIN}
#ifdef SPI_3_SLAVE_1_PORT
	{.port = SPI_3_SLAVE_1_PORT, .pin = SPI_3_SLAVE_1_PIN}
#endif
#ifdef SPI_3_SLAVE_2_PORT
	{.port = SPI_3_SLAVE_2_PORT, .pin = SPI_3_SLAVE_2_PIN}
#endif
#ifdef SPI_3_SLAVE_3_PORT
	{.port = SPI_3_SLAVE_3_PORT, .pin = SPI_3_SLAVE_3_PIN}
#endif
#ifdef SPI_3_SLAVE_4_PORT
	{.port = SPI_3_SLAVE_4_PORT, .pin = SPI_3_SLAVE_4_PIN}
#endif
}
#endif

#ifdef SPI_MODULE_4
static struct hardware_pin connected_slaves_4[] =	{
	{.port = SPI_4_SLAVE_0_PORT, .pin = SPI_4_SLAVE_0_PIN}
#ifdef SPI_4_SLAVE_1_PORT
	{.port = SPI_4_SLAVE_1_PORT, .pin = SPI_4_SLAVE_1_PIN}
#endif
#ifdef SPI_4_SLAVE_2_PORT
	{.port = SPI_4_SLAVE_2_PORT, .pin = SPI_4_SLAVE_2_PIN}
#endif
#ifdef SPI_4_SLAVE_3_PORT
	{.port = SPI_4_SLAVE_3_PORT, .pin = SPI_4_SLAVE_3_PIN}
#endif
#ifdef SPI_4_SLAVE_4_PORT
	{.port = SPI_4_SLAVE_4_PORT, .pin = SPI_4_SLAVE_4_PIN}
#endif
}
#endif

#ifdef SPI_MODULE_5
static struct hardware_pin connected_slaves_5[] =	{
	{.port = SPI_5_SLAVE_0_PORT, .pin = SPI_5_SLAVE_0_PIN}
#ifdef SPI_5_SLAVE_1_PORT
	{.port = SPI_5_SLAVE_1_PORT, .pin = SPI_5_SLAVE_1_PIN}
#endif
#ifdef SPI_5_SLAVE_2_PORT
	{.port = SPI_5_SLAVE_2_PORT, .pin = SPI_5_SLAVE_2_PIN}
#endif
#ifdef SPI_5_SLAVE_3_PORT
	{.port = SPI_5_SLAVE_3_PORT, .pin = SPI_5_SLAVE_3_PIN}
#endif
#ifdef SPI_5_SLAVE_4_PORT
	{.port = SPI_5_SLAVE_4_PORT, .pin = SPI_5_SLAVE_4_PIN}
#endif
}
#endif

struct packet {
	uint8_t contents[PACKETLENGTH];
	uint8_t writeindex;
	uint8_t readindex;
	uint8_t slave;
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
	uint32_t spi_hardware;
	struct hardware_pin *connected_slaves;
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
// set the corresponding hardware address
spi_module_0.spi_hardware = SPI1
// link the slave select pin arrays via a pointer
spi_module_0.connected_slaves = connected_slaves_0;
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
// set the corresponding hardware address
spi_module_1.spi_hardware = SPI2
// link the slave select pin arrays via a pointer
spi_module_1.connected_slaves = connected_slaves_1;
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
// set the corresponding hardware address
spi_module_2.spi_hardware = SPI3
// link the slave select pin arrays via a pointer
spi_module_2.connected_slaves = connected_slaves_2;
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
// set the corresponding hardware address
spi_module_3.spi_hardware = SPI4
// link the slave select pin arrays via a pointer
spi_module_3.connected_slaves = connected_slaves_3;
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
// set the corresponding hardware address
spi_module_4.spi_hardware = SPI5
// link the slave select pin arrays via a pointer
spi_module_4.connected_slaves = connected_slaves_4;
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
// set the corresponding hardware address
spi_module_5.spi_hardware = SPI6
// link the slave select pin arrays via a pointer
spi_module_5.connected_slaves = connected_slaves_5;
#endif

// TODO this is not finished yet
void init_spi(uint8_t mode, struct spi *spi_module){
	// set up the Hardware modules and pins
	if(mode == SPI_MASTER){
		#ifdef SPI_MODULE_0
		// Configuring the Hardware Interface
		// MISO
		gpio_set_mode(SPI_0_MISO_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_0_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_0_MOSI_PORT, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_0_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_0_SCK_PORT, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_0_SCK_PIN);
		// Slaves
		for(uint8_t i = 0, i < SPI_0_CONNECTED_SLAVES; i++){
			gpio_set_mode(spi_module_0.connected_slaves[i].port, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_PUSHPULL, spi_module_0.connected_slaves[i].pin);
		}
		// Hardware modules
		spi_init_master(spi_module_0.spi_hardware, SPI_CR1_BAUDRATE_FPCLK_DIV_8, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE
				SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_disable_crc(spi_module_0.spi_hardware);
		spi_enable_rx_not_empty_interrupt(spi_module_0.spi_hardware);
		spi_enable_software_slave_management(spi_module_0.spi_hardware);
		spi_enable(spi_module_0.spi_hardware);
		#endif

		#ifdef SPI_MODULE_1
		// Configuring the Hardware Interface
		// MISO
		gpio_set_mode(SPI_1_MISO_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_1_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_1_MOSI_PORT, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_1_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_1_SCK_PORT, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_1_SCK_PIN);
		// Slaves
		for(uint8_t i=0, i < SPI_1_CONNECTED_SLAVES; i++){
			gpio_set_mode(spi_module_0.connected_slaves[i].port, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_PUSHPULL, spi_module_1.connected_slaves[i].pin);
		}
		spi_init_master(spi_module_1.spi_hardware, SPI_CR1_BAUDRATE_FPCLK_DIV_8, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE
				SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_disable_crc(spi_module_1.spi_hardware)
		spi_enable_rx_not_empty_interrupt(spi_module_1.spi_hardware);
		spi_enable_software_slave_management(spi_module_1.spi_hardware);
		spi_enable(spi_module_1.spi_hardware);
		#endif

		#ifdef SPI_MODULE_2
		// Configuring the Hardware Interface
		// MISO
		gpio_set_mode(SPI_2_MISO_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_2_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_2_MOSI_PORT, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_2_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_2_SCK_PORT, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_2_SCK_PIN);
		// Slaves
		for(uint8_t i=0, i < SPI_2_CONNECTED_SLAVES; i++){
			gpio_set_mode(spi_module_2.connected_slaves[i].port, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_PUSHPULL, spi_module_2.connected_slaves[i].pin);
		}
		spi_init_master(spi_module_2.spi_hardware, SPI_CR1_BAUDRATE_FPCLK_DIV_8, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE
				SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_disable_crc(spi_module_2.spi_hardware)
		spi_enable_rx_not_empty_interrupt(spi_module_2.spi_hardware);
		spi_enable_software_slave_management(spi_module_2.spi_hardware);
		spi_enable(spi_module_2.spi_hardware);
		#endif

		#ifdef SPI_MODULE_3
		// Configuring the Hardware Interface
		// MISO
		gpio_set_mode(SPI_3_MISO_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_3_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_3_MOSI_PORT, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_3_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_3_SCK_PORT, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_3_SCK_PIN);
		// Slaves
		for(uint8_t i=0, i < SPI_0_CONNECTED_SLAVES; i++){
			gpio_set_mode(spi_module_3.connected_slaves[i].port, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_PUSHPULL, spi_module_3.connected_slaves[i].pin);
		}
		spi_init_master(spi_module_3.spi_hardware, SPI_CR1_BAUDRATE_FPCLK_DIV_8, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE
				SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_disable_crc(spi_module_3.spi_hardware)
		spi_enable_rx_not_empty_interrupt(spi_module_3.spi_hardware);
		spi_enable_software_slave_management(spi_module_3.spi_hardware);
		spi_enable(spi_module_3.spi_hardware);
		#endif

		#ifdef SPI_MODULE_4
		// Configuring the Hardware Interface
		// MISO
		gpio_set_mode(SPI_4_MISO_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_4_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_4_MOSI_PORT, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_4_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_4_SCK_PORT, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_4_SCK_PIN);
		// Slaves
		for(uint8_t i=0, i < SPI_4_CONNECTED_SLAVES; i++){
			gpio_set_mode(spi_module_4.connected_slaves[i].port, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_PUSHPULL, spi_module_4.connected_slaves[i].pin);
		}
		spi_init_master(spi_module_4.spi_hardware, SPI_CR1_BAUDRATE_FPCLK_DIV_8, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE
				SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_disable_crc(spi_module_4.spi_hardware)
		spi_enable_rx_not_empty_interrupt(spi_module_4.spi_hardware);
		spi_enable_software_slave_management(spi_module_4.spi_hardware);
		spi_enable(spi_module_4.spi_hardware);
		#endif

		#ifdef SPI_MODULE_5
		// Configuring the Hardware Interface
		// MISO
		gpio_set_mode(SPI_5_MISO_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_5_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_5_MOSI_PORT, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_5_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_5_SCK_PORT, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_5_SCK_PIN);
		// Slaves
		for(uint8_t i=0, i < SPI_5_CONNECTED_SLAVES; i++){
			gpio_set_mode(spi_module_5.connected_slaves[i].port, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_PUSHPULL, spi_module_5.connected_slaves[i].pin);
		}
		spi_init_master(spi_module_5.spi_hardware, SPI_CR1_BAUDRATE_FPCLK_DIV_8, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE
				SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_disable_crc(spi_module_5.spi_hardware)
		spi_enable_rx_not_empty_interrupt(spi_module_5.spi_hardware);
		spi_enable_software_slave_management(spi_module_5.spi_hardware);
		spi_enable(spi_module_5.spi_hardware);
		#endif
	}
	else{
		// TODO follow the procedure on page 697 of the manual
	#ifdef SPI_MODULE_0
	}
}

// helper funktions -----------------------------------------------------------
void set_SS_pin_high(struct hardware_pin ssline){
	gpio_set(ssline.port, ssline.pin);
}

void set_SS_pin_low(struct hardware_pin ssline){
	gpio_clear(ssline.port, ssline.pin);
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

uint16_t spi_irq_slave_handler(struct spi *spimodule, uint8_t data){
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
