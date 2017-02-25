#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "armspi.h"

extern struct spi spi_module_1;

void main(void)
{
	uint8_t data[] ={
		0,1,2,3,
	};
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
	gpio_toggle(GPIOC, GPIO13);
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_SPI1);
	init_spi();
	
	while(1) {
		write_spi_packet(&spi_module_1, data, 4);
		gpio_toggle(GPIOC, GPIO13);
		for(int i = 0; i < 800000; i++){
			__asm__("nop");
		}
	}
}
