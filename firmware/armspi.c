/*
 * Header File for the armspi library that implements a packet based abstraction layer
 * for the SPI interface and allows the user to simply send a packet overthe SPI and
 * not have to worry about the details.
 *
 * Author: Alexander Becker galax.becker@live.de
 * Version: 0.0
 */
#include "armspi.h"

struct hardware_pin {
	uint32_t port;
	uint32_t pin;
	uint32_t rcc;
};

#ifdef SPI_MODULE_1
static const struct hardware_pin connected_slaves_1[] =	{
	{.port = SPI_1_SLAVE_0_PORT, .pin = SPI_1_SLAVE_0_PIN, .rcc = SPI_1_SLAVE_0_RCC,}
#ifdef SPI_1_SLAVE_1_PORT
	{.port = SPI_1_SLAVE_1_PORT, .pin = SPI_1_SLAVE_1_PIN, .rcc = SPI_1_SLAVE_1_RCC}
#endif
#ifdef SPI_1_SLAVE_2_PORT
	{.port = SPI_1_SLAVE_2_PORT, .pin = SPI_1_SLAVE_2_PIN, .rcc = SPI_1_SLAVE_2_RCC}
#endif
#ifdef SPI_1_SLAVE_3_PORT
	{.port = SPI_1_SLAVE_3_PORT, .pin = SPI_1_SLAVE_3_PIN, .rcc = SPI_1_SLAVE_3_RCC}
#endif
#ifdef SPI_1_SLAVE_4_PORT
	{.port = SPI_1_SLAVE_4_PORT, .pin = SPI_1_SLAVE_4_PIN, .rcc = SPI_1_SLAVE_4_RCC}
#endif
};
#endif

#ifdef SPI_MODULE_2
static const struct hardware_pin connected_slaves_2[] =	{
	{.port = SPI_2_SLAVE_0_PORT, .pin = SPI_2_SLAVE_0_PIN, .rcc = SPI_2_SLAVE_0_RCC,}
#ifdef SPI_2_SLAVE_1_PORT
	{.port = SPI_2_SLAVE_1_PORT, .pin = SPI_2_SLAVE_1_PIN, .rcc = SPI_2_SLAVE_1_RCC,}
#endif
#ifdef SPI_2_SLAVE_2_PORT
	{.port = SPI_2_SLAVE_2_PORT, .pin = SPI_2_SLAVE_2_PIN, .rcc = SPI_2_SLAVE_2_RCC,}
#endif
#ifdef SPI_2_SLAVE_3_PORT
	{.port = SPI_2_SLAVE_3_PORT, .pin = SPI_2_SLAVE_3_PIN, .rcc = SPI_2_SLAVE_3_RCC,}
#endif
#ifdef SPI_2_SLAVE_4_PORT
	{.port = SPI_2_SLAVE_4_PORT, .pin = SPI_2_SLAVE_4_PIN, .rcc = SPI_2_SLAVE_4_RCC,}
#endif
};
#endif

#ifdef SPI_MODULE_3
static const struct hardware_pin connected_slaves_3[] =	{
	{.port = SPI_3_SLAVE_0_PORT, .pin = SPI_3_SLAVE_0_PIN, .rcc = SPI_3_SLAVE_0_RCC,}
#ifdef SPI_3_SLAVE_1_PORT
	{.port = SPI_3_SLAVE_1_PORT, .pin = SPI_3_SLAVE_1_PIN, .rcc = SPI_3_SLAVE_1_RCC,}
#endif
#ifdef SPI_3_SLAVE_2_PORT
	{.port = SPI_3_SLAVE_2_PORT, .pin = SPI_3_SLAVE_2_PIN, .rcc = SPI_3_SLAVE_2_RCC,}
#endif
#ifdef SPI_3_SLAVE_3_PORT
	{.port = SPI_3_SLAVE_3_PORT, .pin = SPI_3_SLAVE_3_PIN, .rcc = SPI_3_SLAVE_3_RCC,}
#endif
#ifdef SPI_3_SLAVE_4_PORT
	{.port = SPI_3_SLAVE_4_PORT, .pin = SPI_3_SLAVE_4_PIN, .rcc = SPI_3_SLAVE_4_RCC,}
#endif
};
#endif

#ifdef SPI_MODULE_4
static const struct hardware_pin connected_slaves_4[] =	{
	{.port = SPI_4_SLAVE_0_PORT, .pin = SPI_4_SLAVE_0_PIN, .rcc = SPI_4_SLAVE_0_RCC,}
#ifdef SPI_4_SLAVE_1_PORT
	{.port = SPI_4_SLAVE_1_PORT, .pin = SPI_4_SLAVE_1_PIN, .rcc = SPI_4_SLAVE_1_RCC,}
#endif
#ifdef SPI_4_SLAVE_2_PORT
	{.port = SPI_4_SLAVE_2_PORT, .pin = SPI_4_SLAVE_2_PIN, .rcc = SPI_4_SLAVE_2_RCC,}
#endif
#ifdef SPI_4_SLAVE_3_PORT
	{.port = SPI_4_SLAVE_3_PORT, .pin = SPI_4_SLAVE_3_PIN, .rcc = SPI_4_SLAVE_3_RCC,}
#endif
#ifdef SPI_4_SLAVE_4_PORT
	{.port = SPI_4_SLAVE_4_PORT, .pin = SPI_4_SLAVE_4_PIN, .rcc = SPI_4_SLAVE_4_RCC,}
#endif
};
#endif

#ifdef SPI_MODULE_5
static const struct hardware_pin connected_slaves_5[] =	{
	{.port = SPI_5_SLAVE_0_PORT, .pin = SPI_5_SLAVE_0_PIN, .rcc = SPI_5_SLAVE_0_RCC,},
#ifdef SPI_5_SLAVE_1_PORT
	{.port = SPI_5_SLAVE_1_PORT, .pin = SPI_5_SLAVE_1_PIN, .rcc = SPI_5_SLAVE_1_RCC,},
#endif
#ifdef SPI_5_SLAVE_2_PORT
	{.port = SPI_5_SLAVE_2_PORT, .pin = SPI_5_SLAVE_2_PIN, .rcc = SPI_5_SLAVE_2_RCC,},
#endif
#ifdef SPI_5_SLAVE_3_PORT
	{.port = SPI_5_SLAVE_3_PORT, .pin = SPI_5_SLAVE_3_PIN, .rcc = SPI_5_SLAVE_3_RCC,},
#endif
#ifdef SPI_5_SLAVE_4_PORT
	{.port = SPI_5_SLAVE_4_PORT, .pin = SPI_5_SLAVE_4_PIN, .rcc = SPI_5_SLAVE_4_RCC,},
#endif
};
#endif

#ifdef SPI_MODULE_6
static const struct hardware_pin connected_slaves_6[] =	{
	{.port = SPI_6_SLAVE_0_PORT, .pin = SPI_6_SLAVE_0_PIN, .rcc = SPI_6_SLAVE_0_RCC,},
#ifdef SPI_6_SLAVE_1_PORT
	{.port = SPI_6_SLAVE_1_PORT, .pin = SPI_6_SLAVE_1_PIN, .rcc = SPI_6_SLAVE_1_RCC,},
#endif
#ifdef SPI_6_SLAVE_2_PORT
	{.port = SPI_6_SLAVE_2_PORT, .pin = SPI_6_SLAVE_2_PIN, .rcc = SPI_6_SLAVE_2_RCC,},
#endif
#ifdef SPI_6_SLAVE_3_PORT
	{.port = SPI_6_SLAVE_3_PORT, .pin = SPI_6_SLAVE_3_PIN, .rcc = SPI_6_SLAVE_3_RCC,},
#endif
#ifdef SPI_6_SLAVE_4_PORT
	{.port = SPI_6_SLAVE_4_PORT, .pin = SPI_6_SLAVE_4_PIN, .rcc = SPI_6_SLAVE_4_RCC,},
#endif
};
#endif

// if the module is activated the space for the buffers is allocated
// and initialize the data structures

#ifdef SPI_MODULE_1
volatile struct spi spi_module_1 = {
	.txbuffer = {
		.start = spi_module_1.tbuffer,
		.head =  spi_module_1.tbuffer,
		.tail =  spi_module_1.tbuffer,
		.buffersize = TRANSMITBUFFERLENGTH,
	},
	.rxbuffer = {
		.start = spi_module_1.rbuffer,
		.head = spi_module_1.rbuffer,
		.tail = spi_module_1.rbuffer,
		.buffersize = RECIEVEBUFFERLENGHT,
	},
	.spi_hardware = SPI1,
	.connected_slaves = connected_slaves_1,
	.status = 0 | SPI_1_MODE,
};
#endif

#ifdef SPI_MODULE_2
volatile struct spi spi_module_2 = {
	.txbuffer = {
		.start = spi_module_2.tbuffer,
		.head =  spi_module_2.tbuffer,
		.tail =  spi_module_2.tbuffer,
		.buffersize = TRANSMITBUFFERLENGTH,
	},
	.rxbuffer = {
		.start = spi_module_2.rbuffer,
		.head = spi_module_2.rbuffer,
		.tail = spi_module_2.rbuffer,
		.buffersize = RECIEVEBUFFERLENGHT,
	},
	.spi_hardware = SPI2,
	.connected_slaves = connected_slaves_2,
	.status = 0 | SPI_2_MODE,
};
#endif

#ifdef SPI_MODULE_3
volatile struct spi spi_module_3 = {
	.txbuffer = {
		.start = spi_module_3.tbuffer,
		.head =  spi_module_3.tbuffer,
		.tail =  spi_module_3.tbuffer,
		.buffersize = TRANSMITBUFFERLENGTH,
	},
	.rxbuffer = {
		.start = spi_module_3.rbuffer,
		.head = spi_module_3.rbuffer,
		.tail = spi_module_3.rbuffer,
		.buffersize = RECIEVEBUFFERLENGHT,
	},
	.spi_hardware = SPI3,
	.connected_slaves = connected_slaves_3,
	.status = 0 | SPI_3_MODE,
};
#endif

#ifdef SPI_MODULE_4
// transmit buffer initialization
volatile struct spi spi_module_4 = {
	.txbuffer = {
		.start = spi_module_4.tbuffer,
		.head =  spi_module_4.tbuffer,
		.tail =  spi_module_4.tbuffer,
		.buffersize = TRANSMITBUFFERLENGTH,
	},
	.rxbuffer = {
		.start = spi_module_4.rbuffer,
		.head = spi_module_4.rbuffer,
		.tail = spi_module_4.rbuffer,
		.buffersize = RECIEVEBUFFERLENGHT,
	},
	.spi_hardware = SPI4,
	.connected_slaves = connected_slaves_4,
	.status = 0 | SPI_4_MODE,
};
#endif

#ifdef SPI_MODULE_5
volatile struct spi spi_module_5 = {
	.txbuffer = {
		.start = spi_module_5.tbuffer,
		.head =  spi_module_5.tbuffer,
		.tail =  spi_module_5.tbuffer,
		.buffersize = TRANSMITBUFFERLENGTH,
	},
	.rxbuffer = {
		.start = spi_module_5.rbuffer,
		.head = spi_module_5.rbuffer,
		.tail = spi_module_5.rbuffer,
		.buffersize = RECIEVEBUFFERLENGHT,
	},
	.spi_hardware = SPI5,
	.connected_slaves = connected_slaves_5,
	.status = 0 | SPI_5_MODE,
};
#endif

#ifdef SPI_MODULE_6
volatile struct spi spi_module_6 = {
	.txbuffer = {
		.start = spi_module_6.tbuffer,
		.head =  spi_module_6.tbuffer,
		.tail =  spi_module_6.tbuffer,
		.buffersize = TRANSMITBUFFERLENGTH,
	},
	.rxbuffer = {
		.start = spi_module_6.rbuffer,
		.head = spi_module_6.rbuffer,
		.tail = spi_module_6.rbuffer,
		.buffersize = RECIEVEBUFFERLENGHT,
	},
	.spi_hardware = SPI6,
	.connected_slaves = connected_slaves_6,
	.status = 0 | SPI_6_MODE,
};
#endif

// helper funktions -----------------------------------------------------------
void set_SS_pin_high(struct hardware_pin *ssline){
	gpio_set(ssline->port, ssline->pin);
}

void set_SS_pin_low(struct hardware_pin *ssline){
	gpio_clear(ssline->port, ssline->pin);
}

void increment_bufferpointer(volatile struct packet * volatile*cursor, volatile struct ringbuffer *buffer){
	(*cursor) ++;
	if(*cursor >= buffer->start+buffer->buffersize){
		*cursor = buffer->start;
	}
}
// end helper functions -------------------------------------------------------

void init_spi(void){
	#ifdef SPI_MODULE_1
	if(spi_module_1.status & SPI_MASTER){
		// Configuring the Hardware Interface
		// Setting up the clocks
		rcc_periph_clock_enable(SPI_1_MISO_RCC);
		rcc_periph_clock_enable(SPI_1_MOSI_RCC);
		rcc_periph_clock_enable(SPI_1_SCK_RCC);
		rcc_periph_clock_enable(RCC_AFIO);
		rcc_periph_clock_enable(RCC_SPI1);
		// enabeling the SPI1 Interrupts
		nvic_enable_irq(NVIC_SPI1_IRQ);
		// setting the TX-buffer empty flag in the Status register
		spi_module_1.status |= SPITXBUFFER_EMPTY;
		// Setting up pins
		// MISO
		gpio_set_mode(SPI_1_MISO_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_1_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_1_MOSI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_1_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_1_SCK_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_1_SCK_PIN);
		// Slaves
		for(uint8_t i = 0; i < SPI_1_CONNECTED_SLAVES; i++){
			rcc_periph_clock_enable(spi_module_1.connected_slaves[i].rcc);
			gpio_set_mode(spi_module_1.connected_slaves[i].port, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, spi_module_1.connected_slaves[i].pin);
			set_SS_pin_high(spi_module_1.connected_slaves+i);
		}
		// Configuring the module
		spi_init_master(spi_module_1.spi_hardware, SPI1_CLK_DIV, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE, SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_disable_crc(spi_module_1.spi_hardware);
		spi_enable_rx_buffer_not_empty_interrupt(spi_module_1.spi_hardware);
		spi_enable_software_slave_management(spi_module_1.spi_hardware);
		spi_set_nss_high(spi_module_1.spi_hardware);
		spi_enable(spi_module_1.spi_hardware);
	}
	else{
		// Configuring the Hardware Interface
		rcc_periph_clock_enable(SPI_1_MISO_RCC);
		rcc_periph_clock_enable(SPI_1_MOSI_RCC);
		rcc_periph_clock_enable(SPI_1_SCK_RCC);
		rcc_periph_clock_enable(spi_module_1.connected_slaves[0].rcc);
		rcc_periph_clock_enable(RCC_AFIO);
		rcc_periph_clock_enable(RCC_SPI1);
		nvic_enable_irq(NVIC_SPI1_IRQ);
		// MISO
		gpio_set_mode(SPI_1_MISO_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_1_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_1_MOSI_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_1_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_1_SCK_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_1_SCK_PIN);
		// the SS-input line
		gpio_set_mode(spi_module_1.connected_slaves[0].port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, spi_module_1.connected_slaves[0].pin);
		// now configurer the SPI_module
		spi_set_slave_mode(spi_module_1.spi_hardware);
		spi_set_dff_8bit(spi_module_1.spi_hardware);
		spi_set_clock_polarity_0(spi_module_1.spi_hardware);
		spi_set_clock_phase_1(spi_module_1.spi_hardware);
		spi_send_msb_first(spi_module_1.spi_hardware);
		spi_disable_software_slave_management(spi_module_1.spi_hardware);
		spi_enable_rx_buffer_not_empty_interrupt(spi_module_1.spi_hardware);
		spi_enable(spi_module_1.spi_hardware);
	}
	#endif

	#ifdef SPI_MODULE_2
	if(spi_module_2.status & SPI_MASTER){
		// Configuring the Hardware Interface
		// Setting up the clocks
		rcc_periph_clock_enable(SPI_2_MISO_RCC);
		rcc_periph_clock_enable(SPI_2_MOSI_RCC);
		rcc_periph_clock_enable(SPI_2_SCK_RCC);
		rcc_periph_clock_enable(RCC_AFIO);
		rcc_periph_clock_enable(RCC_SPI2);
		// enabeling the SPI1 Interrupts
		nvic_enable_irq(NVIC_SPI2_IRQ);
		// setting the TX-buffer empty flag in the Status register
		spi_module_2.status |= SPITXBUFFER_EMPTY;
		// Setting up pins
		// MISO
		gpio_set_mode(SPI_2_MISO_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_2_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_2_MOSI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_2_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_2_SCK_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_2_SCK_PIN);
		// Slaves
		for(uint8_t i=0; i < SPI_2_CONNECTED_SLAVES; i++){
			rcc_periph_clock_enable(spi_module_2.connected_slaves[i].rcc);
			gpio_set_mode(spi_module_2.connected_slaves[i].port, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, spi_module_2.connected_slaves[i].pin);
			set_SS_pin_high(spi_module_2.connected_slaves+i);
		}
		spi_init_master(spi_module_2.spi_hardware, SPI2_CLK_DIV, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE, SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_disable_crc(spi_module_2.spi_hardware);
		spi_enable_rx_buffer_not_empty_interrupt(spi_module_2.spi_hardware);
		spi_enable_software_slave_management(spi_module_2.spi_hardware);
		spi_set_nss_high(spi_module_2.spi_hardware)
		spi_enable(spi_module_2.spi_hardware);
	}
	else{
		// Configuring the Hardware Interface
		rcc_periph_clock_enable(SPI_2_MISO_RCC);
		rcc_periph_clock_enable(SPI_2_MOSI_RCC);
		rcc_periph_clock_enable(SPI_2_SCK_RCC);
		rcc_periph_clock_enable(spi_module_2.connected_slaves[0].rcc);
		rcc_periph_clock_enable(RCC_AFIO);
		rcc_periph_clock_enable(RCC_SPI2);
		nvic_enable_irq(NVIC_SPI2_IRQ);
		// MISO
		gpio_set_mode(SPI_2_MISO_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_2_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_2_MOSI_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_2_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_2_SCK_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_2_SCK_PIN);
		// the SS-input line
		gpio_set_mode(spi_module_2.connected_slaves[0].port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, spi_module_2.connected_slaves[0].pin);
		// now configurer the SPI_module
		spi_set_slave_mode(spi_module_2.spi_hardware);
		spi_set_dff_8bit(spi_module_2.spi_hardware);
		spi_set_clock_polarity_0(spi_module_2.spi_hardware);
		spi_set_clock_phase_1(spi_module_2.spi_hardware);
		spi_send_msb_first(spi_module_2.spi_hardware);
		spi_disable_software_slave_management(spi_module_2.spi_hardware);
		spi_enable_rx_buffer_not_empty_interrupt(spi_module_2.spi_hardware);
		spi_enable(spi_module_2.spi_hardware);
	}
	#endif

	#ifdef SPI_MODULE_3
	if(spi_module_3.status & SPI_MASTER){
		// Configuring the Hardware Interface
		// Setting up the clocks
		rcc_periph_clock_enable(SPI_3_MISO_RCC);
		rcc_periph_clock_enable(SPI_3_MOSI_RCC);
		rcc_periph_clock_enable(SPI_3_SCK_RCC);
		rcc_periph_clock_enable(RCC_AFIO);
		rcc_periph_clock_enable(RCC_SPI3);
		// enabeling the SPI1 Interrupts
		nvic_enable_irq(NVIC_SPI3_IRQ);
		// setting the TX-buffer empty flag in the Status register
		spi_module_3.status |= SPITXBUFFER_EMPTY;
		// Setting up pins
		// MISO
		gpio_set_mode(SPI_3_MISO_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_3_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_3_MOSI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_3_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_3_SCK_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_3_SCK_PIN);
		// Slaves
		for(uint8_t i=0; i < SPI_3_CONNECTED_SLAVES; i++){
			rcc_periph_clock_enable(spi_module_3.connected_slaves[i].rcc);
			gpio_set_mode(spi_module_3.connected_slaves[i].port, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, spi_module_3.connected_slaves[i].pin);
			set_SS_pin_high(spi_module_3.connected_slaves+i);
		}
		spi_init_master(spi_module_3.spi_hardware, SPI3_CLK_DIV, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE, SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_disable_crc(spi_module_3.spi_hardware);
		spi_enable_software_slave_management(spi_module_3.spi_hardware);
		spi_enable_rx_buffer_not_empty_interrupt(spi_module_3.spi_hardware);
		spi_set_nss_high(spi_module_3.spi_hardware)
		spi_enable(spi_module_3.spi_hardware);
	}
	else{
		// Configuring the Hardware Interface
		rcc_periph_clock_enable(SPI_3_MISO_RCC);
		rcc_periph_clock_enable(SPI_3_MOSI_RCC);
		rcc_periph_clock_enable(SPI_3_SCK_RCC);
		rcc_periph_clock_enable(spi_module_3.connected_slaves[0].rcc);
		rcc_periph_clock_enable(RCC_AFIO);
		rcc_periph_clock_enable(RCC_SPI3);
		nvic_enable_irq(NVIC_SPI3_IRQ);
		// MISO
		gpio_set_mode(SPI_3_MISO_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_3_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_3_MOSI_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_3_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_3_SCK_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_3_SCK_PIN);
		// the SS-input line
		gpio_set_mode(spi_module_3.connected_slaves[0].port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, spi_module_3.connected_slaves[0].pin);
		// now configurer the SPI_module
		spi_set_slave_mode(spi_module_3.spi_hardware);
		spi_set_dff_8bit(spi_module_3.spi_hardware);
		spi_set_clock_polarity_0(spi_module_3.spi_hardware);
		spi_set_clock_phase_1(spi_module_3.spi_hardware);
		spi_send_msb_first(spi_module_3.spi_hardware);
		spi_disable_software_slave_management(spi_module_3.spi_hardware);
		spi_enable_rx_buffer_not_empty_interrupt(spi_module_3.spi_hardware);
		spi_enable(spi_module_3.spi_hardware);
	}
	#endif

	#ifdef SPI_MODULE_4
	if(spi_module_4.status & SPI_MASTER){
		// Configuring the Hardware Interface
		// Setting up the clocks
		rcc_periph_clock_enable(SPI_4_MISO_RCC);
		rcc_periph_clock_enable(SPI_4_MOSI_RCC);
		rcc_periph_clock_enable(SPI_4_SCK_RCC);
		rcc_periph_clock_enable(RCC_AFIO);
		rcc_periph_clock_enable(RCC_SPI4);
		// enabeling the SPI1 Interrupts
		nvic_enable_irq(NVIC_SPI4_IRQ);
		// setting the TX-buffer empty flag in the Status register
		spi_module_4.status |= SPITXBUFFER_EMPTY;
		// Setting up pins
		// MISO
		gpio_set_mode(SPI_4_MISO_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_4_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_4_MOSI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_4_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_4_SCK_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_4_SCK_PIN);
		// Slaves
		for(uint8_t i=0; i < SPI_4_CONNECTED_SLAVES; i++){
			rcc_periph_clock_enable(spi_module_4.connected_slaves[i].rcc);
			gpio_set_mode(spi_module_4.connected_slaves[i].port, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, spi_module_4.connected_slaves[i].pin);
			set_SS_pin_high(spi_module_4.connected_slaves+i);
		}
		spi_init_master(spi_module_4.spi_hardware, SPI4_CLK_DIV, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE, SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_disable_crc(spi_module_4.spi_hardware);
		spi_enable_software_slave_management(spi_module_4.spi_hardware);
		spi_enable_rx_buffer_not_empty_interrupt(spi_module_4.spi_hardware);
		spi_set_nss_high(spi_module_4.spi_hardware)
		spi_enable(spi_module_4.spi_hardware);
	}
	else{
		// Configuring the Hardware Interface
		rcc_periph_clock_enable(SPI_4_MISO_RCC);
		rcc_periph_clock_enable(SPI_4_MOSI_RCC);
		rcc_periph_clock_enable(SPI_4_SCK_RCC);
		rcc_periph_clock_enable(spi_module_4.connected_slaves[0].rcc);
		rcc_periph_clock_enable(RCC_AFIO);
		rcc_periph_clock_enable(RCC_SPI4);
		nvic_enable_irq(NVIC_SPI4_IRQ);
		// MISO
		gpio_set_mode(SPI_4_MISO_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_4_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_4_MOSI_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_4_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_4_SCK_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_4_SCK_PIN);
		// the SS-input line
		gpio_set_mode(spi_module_4.connected_slaves[0].port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, spi_module_4.connected_slaves[0].pin);
		// now configurer the SPI_module
		spi_set_slave_mode(spi_module_4.spi_hardware);
		spi_set_dff_8bit(spi_module_4.spi_hardware);
		spi_set_clock_polarity_0(spi_module_4.spi_hardware);
		spi_set_clock_phase_1(spi_module_4.spi_hardware);
		spi_send_msb_first(spi_module_4.spi_hardware);
		spi_disable_software_slave_management(spi_module_4.spi_hardware);
		spi_enable_rx_buffer_not_empty_interrupt(spi_module_4.spi_hardware);
		spi_enable(spi_module_4.spi_hardware);
	}
	#endif

	#ifdef SPI_MODULE_5
	if(spi_module_5.status & SPI_MASTER){
		// Configuring the Hardware Interface
		// Setting up the clocks
		rcc_periph_clock_enable(SPI_5_MISO_RCC);
		rcc_periph_clock_enable(SPI_5_MOSI_RCC);
		rcc_periph_clock_enable(SPI_5_SCK_RCC);
		rcc_periph_clock_enable(RCC_AFIO);
		rcc_periph_clock_enable(RCC_SPI5);
		// enabeling the SPI1 Interrupts
		nvic_enable_irq(NVIC_SPI5_IRQ);
		// setting the TX-buffer empty flag in the Status register
		spi_module_5.status |= SPITXBUFFER_EMPTY;
		// Setting up pins
		// MISO
		gpio_set_mode(SPI_5_MISO_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_5_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_5_MOSI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_5_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_5_SCK_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_5_SCK_PIN);
		// Slaves
		for(uint8_t i=0; i < SPI_5_CONNECTED_SLAVES; i++){
			rcc_periph_clock_enable(spi_module_4.connected_slaves[i].rcc);
			gpio_set_mode(spi_module_5.connected_slaves[i].port, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, spi_module_5.connected_slaves[i].pin);
			set_SS_pin_high(spi_module_5.connected_slaves+i);
		}
		spi_init_master(spi_module_5.spi_hardware, SPI5_CLK_DIV, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE, SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_disable_crc(spi_module_5.spi_hardware);
		spi_enable_software_slave_management(spi_module_5.spi_hardware);
		spi_enable_rx_buffer_not_empty_interrupt(spi_module_5.spi_hardware);
		spi_set_nss_high(spi_module_5.spi_hardware)
		spi_enable(spi_module_5.spi_hardware);
	}
	else{
		// Configuring the Hardware Interface
		rcc_periph_clock_enable(SPI_5_MISO_RCC);
		rcc_periph_clock_enable(SPI_5_MOSI_RCC);
		rcc_periph_clock_enable(SPI_5_SCK_RCC);
		rcc_periph_clock_enable(spi_module_5.connected_slaves[0].rcc);
		rcc_periph_clock_enable(RCC_AFIO);
		rcc_periph_clock_enable(RCC_SPI5);
		nvic_enable_irq(NVIC_SPI5_IRQ);
		// MISO
		gpio_set_mode(SPI_5_MISO_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_5_MISO_PIN);
		// MOS4
		gpio_set_mode(SPI_5_MOSI_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_5_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_5_SCK_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_5_SCK_PIN);
		// the SS-input line
		gpio_set_mode(spi_module_5.connected_slaves[0].port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, spi_module_5.connected_slaves[0].pin);
		// now configurer the SPI_module
		spi_set_slave_mode(spi_module_5.spi_hardware);
		spi_set_dff_8bit(spi_module_5.spi_hardware);
		spi_set_clock_polarity_0(spi_module_5.spi_hardware);
		spi_set_clock_phase_1(spi_module_5.spi_hardware);
		spi_send_msb_first(spi_module_5.spi_hardware);
		spi_disable_software_slave_management(spi_module_5.spi_hardware);
		spi_enable_rx_buffer_not_empty_interrupt(spi_module_5.spi_hardware);
		spi_enable(spi_module_5.spi_hardware);
	}
	#endif

	#ifdef SPI_MODULE_6
	if(spi_module_6.status == SPI_MASTER){
		// Configuring the Hardware Interface
		// Setting up the clocks
		rcc_periph_clock_enable(SPI_6_MISO_PORT);
		rcc_periph_clock_enable(SPI_6_MOSI_PORT);
		rcc_periph_clock_enable(SPI_6_SCK_PORT);
		rcc_periph_clock_enable(RCC_AFIO);
		rcc_periph_clock_enable(RCC_SPI6);
		// enabeling the SPI1 Interrupts
		nvic_enable_irq(NVIC_SPI6_IRQ);
		// setting the TX-buffer empty flag in the Status register
		spi_module_6.status |= SPITXBUFFER_EMPTY;
		// Setting up pins
		// MISO
		gpio_set_mode(SPI_6_MISO_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_6_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_6_MOSI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_6_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_6_SCK_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_6_SCK_PIN);
		// Slaves
		for(uint8_t i=0; i < SPI_6_CONNECTED_SLAVES; i++){
			rcc_periph_clock_enable(spi_module_5.connected_slaves[i].rcc);
			gpio_set_mode(spi_module_6.connected_slaves[i].port, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, spi_module_6.connected_slaves[i].pin);
			set_SS_pin_high(spi_module_6.connected_slaves+i);
		}
		spi_init_master(spi_module_6.spi_hardware, SPI6_CLK_DIV, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE, SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
		spi_disable_crc(spi_module_6.spi_hardware)
		spi_enable_software_slave_management(spi_module_6.spi_hardware);
		spi_enable_rx_buffer_not_empty_interrupt(spi_module_6.spi_hardware);
		spi_set_nss_high(spi_module_6.spi_hardware)
		spi_enable(spi_module_6.spi_hardware);
	}
	else{
		// Configuring the Hardware Interface
		rcc_periph_clock_enable(SPI_6_MISO_PORT);
		rcc_periph_clock_enable(SPI_6_MOSI_PORT);
		rcc_periph_clock_enable(SPI_6_SCK_PORT);
		rcc_periph_clock_enable(spi_module_6.connected_slaves[0].rcc);
		rcc_periph_clock_enable(RCC_AFIO);
		rcc_periph_clock_enable(RCC_SPI6);
		nvic_enable_irq(NVIC_SPI6_IRQ);
		// MISO
		gpio_set_mode(SPI_6_MISO_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_6_MISO_PIN);
		// MOSI
		gpio_set_mode(SPI_6_MOSI_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_6_MOSI_PIN);
		// SCK
		gpio_set_mode(SPI_6_SCK_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SPI_6_SCK_PIN);
		// the SS-input line
		gpio_set_mode(spi_module_6.connected_slaves[0].port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, spi_module_6.connected_slaves[0].pin);
		// now configurer the SPI_module
		spi_set_slave_mode(spi_module_6.spi_hardware);
		spi_set_dff_8bit(spi_module_6.spi_hardware);
		spi_set_clock_polarity_0(spi_module_6.spi_hardware);
		spi_set_clock_phase_1(spi_module_6.spi_hardware);
		spi_send_msb_first(spi_module_6.spi_hardware);
		spi_disable_software_slave_management(spi_module_6.spi_hardware);
		spi_enable_rx_buffer_not_empty_interrupt(spi_module_6.spi_hardware);
		spi_enable(spi_module_6.spi_hardware);
	}
	#endif
}
uint8_t txbufferstatus(volatile struct spi *spimodule){
	if(spimodule->status & SPITXBUFFER_FULL){
		return 0;
	}
	else{
		return 1;
	}
}

uint8_t rxbufferstatus(volatile struct spi *spimodule){
	if(spimodule->status & SPIRXBUFFER_EMPTY){
		return 0;
	}
	else{
		return 1;
	}
}

//the value 0 indicates that 0 bytes have been written and that therefor no new packet has been added to the buffer. This ocurrs when the buffer is full.
uint8_t  write_spi_packet(volatile struct spi *spimodule, uint8_t *data, uint8_t size, uint8_t slave_nr){
	spi_disable_rx_buffer_not_empty_interrupt(spimodule->spi_hardware);
	if(spimodule->status & SPITXBUFFER_FULL){
		spi_enable_rx_buffer_not_empty_interrupt(spimodule->spi_hardware);
		return 0; //we simply do nothing and retun that the packet could not be written.
	}
	for(spimodule->txbuffer.head->writeindex = 0; spimodule->txbuffer.head->writeindex < PACKETLENGTH && spimodule->txbuffer.head->writeindex < size; (spimodule->txbuffer.head->writeindex)++){
		spimodule->txbuffer.head->contents[spimodule->txbuffer.head->writeindex] = data[spimodule->txbuffer.head->writeindex];
	}
	spimodule->txbuffer.head->slave = &(spimodule->connected_slaves[slave_nr]);
	uint8_t returnbyte = spimodule->txbuffer.head->writeindex;
	increment_bufferpointer(&(spimodule->txbuffer.head), &(spimodule->txbuffer));
	if(spimodule->txbuffer.head == spimodule->txbuffer.tail){
		spimodule->status |= SPITXBUFFER_FULL;
	}
	// Initiate the firs transfer, after this the Interrupt routine does all the work.
	if(spimodule->status & SPITXBUFFER_EMPTY && spimodule->status & SPI_MASTER){
		set_SS_pin_low(spimodule->txbuffer.tail->slave);
		spimodule->status |= SPI_PACKET_BEING_SENT;
		spi_write(spimodule->spi_hardware, spimodule->txbuffer.tail->contents[spimodule->txbuffer.tail->readindex]);
		spimodule->txbuffer.tail->readindex++;
		if(spimodule->txbuffer.tail->readindex < spimodule->txbuffer.tail->writeindex){
			spimodule->status &= ~SPITXBUFFER_EMPTY;
		}
	}
	spi_enable_rx_buffer_not_empty_interrupt(spimodule->spi_hardware);
	return returnbyte;
}

//the value 0 indicates that no byte has been read and that the buffer therefor is empty.
uint8_t read_spi_packet(volatile struct spi *spimodule, uint8_t *data, uint8_t size){
	spi_disable_rx_buffer_not_empty_interrupt(spimodule->spi_hardware);
	uint8_t i;
	if(spimodule->rxbuffer.tail == spimodule->rxbuffer.head){
		return 0;
	}
	for(i = 0; i < spimodule->rxbuffer.tail->writeindex && i < size; i++){
		*(data + i) = spimodule->rxbuffer.tail->contents[i];
	}
	spimodule->rxbuffer.tail->writeindex = 0;
	spimodule->rxbuffer.tail->readindex = 0;
	increment_bufferpointer(&(spimodule->rxbuffer.tail), &(spimodule->rxbuffer));
	spi_enable_rx_buffer_not_empty_interrupt(spimodule->spi_hardware);
	return i;
}

void spi_irq_master_handler(volatile struct spi *spimodule){
	spimodule->rxbuffer.head->contents[spimodule->rxbuffer.head->writeindex] = SPI_DR(spimodule->spi_hardware);
	spimodule->rxbuffer.head->writeindex++;
	if(spimodule->status & SPI_PACKET_BEING_SENT){
		// We are in the middle of sending a packet so we continue to send it
		spi_write(spimodule->spi_hardware, (uint16_t)(spimodule->txbuffer.tail->contents[spimodule->txbuffer.tail->readindex]));
		spimodule->txbuffer.tail->readindex++;
		if(spimodule->txbuffer.tail->readindex < spimodule->txbuffer.tail->writeindex){
			return;
		}
		else{
			spimodule->status &= ~SPI_PACKET_BEING_SENT;
			spimodule->txbuffer.tail->writeindex = 0;
			spimodule->txbuffer.tail->readindex = 0;
			return;
		}
	}
	else{
		// We have to switch to the next packet (if one is in the buffer) and send it, for we have fully sent the last
		set_SS_pin_high(spimodule->txbuffer.tail->slave);
		increment_bufferpointer(&(spimodule->rxbuffer.head), &(spimodule->rxbuffer));
		increment_bufferpointer(&(spimodule->txbuffer.tail), &(spimodule->txbuffer));
		spimodule->status &= ~SPITXBUFFER_FULL;
		if(spimodule->rxbuffer.head == spimodule->rxbuffer.tail){
			// we can just increment the tail of the rxbuffer because we ensure that the spi_read function disables the interrupt as it reads the packet.
			spimodule->rxbuffer.tail->writeindex = 0;
			spimodule->rxbuffer.tail->readindex = 0;
			increment_bufferpointer(&(spimodule->rxbuffer.tail), &(spimodule->rxbuffer));
		}
		if(spimodule->txbuffer.tail == spimodule->txbuffer.head){
			spimodule->status |= SPITXBUFFER_EMPTY;
		}
		else{
			set_SS_pin_low(spimodule->txbuffer.head->slave);
			if(spimodule->txbuffer.tail->writeindex > 1){
				spimodule->status |= SPI_PACKET_BEING_SENT;
			}
			spi_write(spimodule->spi_hardware, spimodule->txbuffer.tail->contents[spimodule->txbuffer.tail->readindex]);
			return;
		}
	}
}

void spi_irq_slave_handler(volatile struct spi *spimodule){
	uint8_t tmprxdata = SPI_DR(spimodule->spi_hardware);
	spimodule->status &= ~SPI_PACKET_RECIEVED;
	// Listen for the SS linte to go up if it does we have recieved a packet
	for(uint8_t i=0; i>=MAXLOOP; i++){
	// If the device is in slave mode it will always listen on the SS pin line
		if(gpio_get(spimodule->connected_slaves[0].port, spimodule->connected_slaves[0].pin)){
			spimodule->status |= SPI_PACKET_RECIEVED;
			break;
		}
	}
	if(spimodule->status & SPI_PACKET_RECIEVED){
		spimodule->txbuffer.tail->writeindex = 0;
		spimodule->txbuffer.tail->readindex = 0;
		increment_bufferpointer(&(spimodule->txbuffer.tail), &(spimodule->txbuffer));
		// If the transmission buffer is empty send back 0s
		if(spimodule->txbuffer.tail == spimodule->txbuffer.head){
			spi_write(spimodule->spi_hardware, 0);
		}
		else{
			spi_write(spimodule->spi_hardware, spimodule->txbuffer.tail->contents[spimodule->txbuffer.tail->readindex]);
			spimodule->txbuffer.tail->readindex++;
		}
		// store the recieeved byte before incrementing to the next recieved packet
		if(spimodule->rxbuffer.head->writeindex < PACKETLENGTH){
			spimodule->rxbuffer.head->writeindex = tmprxdata;
			spimodule->rxbuffer.head->writeindex++;
		}
		increment_bufferpointer(&(spimodule->rxbuffer.head), &(spimodule->rxbuffer));
		if(spimodule->rxbuffer.head == spimodule->rxbuffer.tail){
			spimodule->rxbuffer.head->writeindex = 0;
			spimodule->rxbuffer.head->readindex = 0;
			increment_bufferpointer(&(spimodule->rxbuffer.tail), &(spimodule->rxbuffer));
		}
	}
	else{
		if(spimodule->txbuffer.tail->readindex >= spimodule->txbuffer.tail->writeindex){
			spi_write(spimodule->spi_hardware, 0);
			spimodule->txbuffer.tail->readindex = 0;
			spimodule->txbuffer.tail->writeindex = 0;
		}
		else{
			spi_write(spimodule->spi_hardware, spimodule->txbuffer.tail->contents[spimodule->txbuffer.tail->readindex]);
			spimodule->txbuffer.tail->readindex++;
		}
		if(spimodule->rxbuffer.head->writeindex < PACKETLENGTH){
			spimodule->rxbuffer.head->writeindex = tmprxdata;
			spimodule->rxbuffer.head->writeindex++;
		}
	}
}

#ifdef SPI_MODULE_1
void spi1_isr(void){
	if(spi_module_1.status & SPI_MASTER){
		spi_irq_master_handler(&spi_module_1);
	}
	else{
		spi_irq_slave_handler(&spi_module_1);
	}
}
#endif

#ifdef SPI_MODULE_2
void spi2_isr(void){
	if(spi_module_2.status & SPI_MASTER){
		spi_irq_master_handler(&spi_module_2);
	}
	else{
		spi_irq_slave_handler(&spi_module_2);
	}
}
#endif

#ifdef SPI_MODULE_3
void spi3_isr(void){
	if(spi_module_3.status & SPI_MASTER){
		spi_irq_master_handler(&spi_module_3);
	}
	else{
		spi_irq_slave_handler(&spi_module_3);
	}
}
#endif

#ifdef SPI_MODULE_4
void spi4_isr(void){
	if(spi_module_4.status & SPI_MASTER){
		spi_irq_master_handler(&spi_module_4);
	}
	else{
		spi_irq_slave_handler(&spi_module_4);
	}
}
#endif

#ifdef SPI_MODULE_5
void spi5_isr(void){
	if(spi_module_5.status & SPI_MASTER){
		spi_irq_master_handler(&spi_module_5);
	}
	else{
		spi_irq_slave_handler(&spi_module_5);
	}
}
#endif

#ifdef SPI_MODULE_6
void spi6_isr(void){
	if(spi_module_6.status & SPI_MASTER){
		spi_irq_master_handler(&spi_module_6);
	}
	else{
		spi_irq_slave_handler(&spi_module_6);
	}
}
#endif
