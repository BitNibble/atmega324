/*************************************************************************
Title:    Interrupt ANALOG INPUT
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Date:     30062025
*************************************************************************/
#include <stdarg.h>
#include "atmega324_analog.h"

#define MAX_CHANNEL 8
#define GLOBAL_INTERRUPT_ENABLE 7
#define MUX_MASK 31
#define ANALOG_INTERRUPT ADC_vect

static ANALOG adc_setup;
static uint16_t ADC_VALUE[MAX_CHANNEL] = {0};
static uint8_t ADC_CHANNEL[MAX_CHANNEL] = {0};
uint8_t ADC_N_CHANNEL;
uint8_t ADC_SELECTOR;
uint8_t adc_n_sample;
uint16_t adc_tmp;
uint16_t adc_sample;


/*** Procedure & Function declaration ***/
int ANALOG_read(int selection);

/*** Handler ***/
void adc_enable( uint8_t Vreff, uint8_t Divfactor, int n_channel, ... )
{
	va_list list;
	int i;
	
	cpu_reg()->sreg->var &= ~(1<<GLOBAL_INTERRUPT_ENABLE);
	
	ADC_N_CHANNEL = n_channel;
	ADC_SELECTOR = 0;
	adc_n_sample = 0;
	// V-table
	adc_setup.read = ANALOG_read;
	/******/
	adc_reg()->admux->var &= ~(3<<REFS0);
	switch( Vreff ){
		case 0: //AREF, Internal Vref turned off
			break;
		case 1: //AVCC with external capacitor at AREF pin
			adc_reg()->admux->var |= (1<<REFS0);
			break;
		case 2: //Internal 1.1V Voltage Reference with external capacitor at AREF pin
			adc_reg()->admux->var |= (1<<REFS1);
			break;
		case 3: //Internal 2.56V Voltage Reference with external capacitor at AREF pin
			adc_reg()->admux->var |= (3<<REFS0);
			break;
		default:
			break;
	}
	
	adc_reg()->adcsra->var &= ~(7 << ADPS0);
	switch( Divfactor ) {
		case 2://1
			break;
		case 4://2
			adc_reg()->adcsra->var |= (1 << ADPS1);
			break;
		case 8://3
			adc_reg()->adcsra->var |= (3 << ADPS0);
			break;
		case 16://4
			adc_reg()->adcsra->var |= (1 << ADPS2);
			break;
		case 32://5
			adc_reg()->adcsra->var |= (5 << ADPS0);
			break;
		case 64://6
			adc_reg()->adcsra->var |= (3 << ADPS1);
			break;
		case 128://7
			adc_reg()->adcsra->var |= (7 << ADPS0);
			break;
		default:
			adc_reg()->adcsra->var |= (7 << ADPS0);
			break;
	}
	/******/
	adc_reg()->admux->var &= ~(1<<ADLAR);
	/******/
	va_start(list, n_channel);
	for( i=0; i < n_channel; i++ ) {
		ADC_CHANNEL[i] = va_arg(list, int);
	}
	va_end(list);
	adc_reg()->admux->var &= ~MUX_MASK;
	adc_reg()->admux->var |= (MUX_MASK & ADC_CHANNEL[ADC_SELECTOR]);
	/******/
	adc_reg()->adcsra->var |= (1 << ADEN);
	adc_reg()->adcsra->var |= (1 << ADSC);
	adc_reg()->adcsra->var &= ~(1 << ADATE);
	adc_reg()->adcsrb->var &= ~(7 << ADTS0);
	adc_reg()->adcsra->var |= (1 << ADIE);
	/******/
	cpu_reg()->sreg->var |= (1 << GLOBAL_INTERRUPT_ENABLE);
	/******/
}

ANALOG* adc(void){return &adc_setup;}

/*** Procedure & Function definition ***/
int ANALOG_read(int selection)
{
	uint8_t ADSC_FLAG;
	ADSC_FLAG = (1 << ADSC);
	if( !(adc_reg()->adcsra->var & ADSC_FLAG) ) {
		/***/
		adc_reg()->adcsra->var |= ADSC_FLAG;
	}
	return ADC_VALUE[selection];
}

ISR(ANALOG_INTERRUPT)
{
	adc_tmp = ADCL;
	adc_tmp |= (ADCH << 8);
	if(adc_n_sample < (1 << ADC_NUMBER_SAMPLE)){
		adc_n_sample++;
		adc_sample += adc_tmp;
	}else{
		ADC_VALUE[ADC_SELECTOR] = adc_sample >> ADC_NUMBER_SAMPLE;
		adc_n_sample = adc_sample = 0;
		
		if(ADC_SELECTOR < ADC_N_CHANNEL)
			ADC_SELECTOR++;
		else
			ADC_SELECTOR = 0;
		adc_reg()->admux->var &= ~MUX_MASK;
		adc_reg()->admux->var |= (ADC_CHANNEL[ADC_SELECTOR] & MUX_MASK);
	}
}

/*** EOF ***/

