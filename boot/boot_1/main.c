#ifndef __AVR_ATmega324A__
	#define __AVR_ATmega324A__
#endif

#define F_CPU 16000000UL

#include "atmega324.h"

int main(void)
{
	uint8_t i = 0xFF;
	DDRB |= ((1 << PB0) | (1 << PB7));

	if (pgm_read_word(0x0000) == 0xFFFF) {
		for (i = 0; i < 6; i++)
		{
			PORTB &= ~(1 << PB0);
			_delay_ms(500);
			PORTB |= 1 << PB0;
			_delay_ms(500);
		}
	}else{
		for (i = 0; i < 6; i++)
		{
			PORTB &= ~(1 << PB7);
			_delay_ms(50);
			PORTB |= (1 << PB7);
			_delay_ms(50);
		}
	}
	
	boot_rww_enable();
	
	asm("jmp 0");
}

// LINK: -Wl,-section-start=.text=0x7C00

