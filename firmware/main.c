#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "armspi.h"

extern struct spi spi_module_1;

void main(void)
{
	uint8_t data[] ={
		24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1
	};
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
	init_spi();
	
	while(1) {
		int i =0;
		for(i=0; i<3; i++){
			if(txbufferstatus(&spi_module_1))
				write_spi_packet(&spi_module_1, data+(i*4), 4, 0);
			if(txbufferstatus(&spi_module_1))
				write_spi_packet(&spi_module_1, data+((i+1)*4), 4, 0);
			if(txbufferstatus(&spi_module_1))
				write_spi_packet(&spi_module_1, data+((i+2)*4), 4, 0);
			if(txbufferstatus(&spi_module_1))
				write_spi_packet(&spi_module_1, data+((i+3)*4), 4, 0);
			if(txbufferstatus(&spi_module_1))
				write_spi_packet(&spi_module_1, data+((i+4)*4), 4, 0);
			gpio_toggle(GPIOC, GPIO13);
			for(int j = 0; j < 800000; j++){
				__asm__("nop");
			}
		}
	}
}
