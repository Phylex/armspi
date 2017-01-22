#include <stdlib.h>
#include <stdint.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "armspi.h"

void main(void)
{
	rcc_clock_setup_in_hse_8mhz_out_72mhz();


	// configure status LED
	init_spi();
	rcc_periph_clock_enable(RCC_SPI1);
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
	uint8_t data[] ={
		0,1,2,3,
	}

	while(1) {
		write_spi_packet(&spi_module_0, &data, 4);
		for(int i = 0; i < 80000000; i++)
			__asm__("nop");
	}
}
