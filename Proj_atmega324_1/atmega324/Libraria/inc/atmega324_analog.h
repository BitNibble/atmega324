/************************************************************************
	Interrupt ANALOG INPUT
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Date:     30062025
************************************************************************/
#ifndef ATMEGA324_ANALOG_H
	#define ATMEGA324_ANALOG_H

/*** Compiler ***/	
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*** Library ***/
#include "atmega324.h"

#define ADC_NUMBER_SAMPLE 4 // 0 to 4.

/*** Handler ***/
struct ANALOG{
	// V-table
	int (*read)(int selection);
};
typedef struct ANALOG ANALOG;

void adc_enable( uint8_t Vreff, uint8_t Divfactor, int n_channel, ... );
ANALOG* adc(void);

#endif
/*** EOF ***/
