/*************************************************************************
	ATMEGA 324 TIMER
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega 324 at 8Mhz
Date:     04072025
*************************************************************************/
/*
** library
*/
#include "atmega324_timer.h"

/**** Procedure and Function declaration ****/
void TIMER_COUNTER0_compoutmodeA(uint8_t compoutmode);
void TIMER_COUNTER0_compoutmodeB(uint8_t compoutmode);
void TIMER_COUNTER0_compareA(uint8_t compare);
void TIMER_COUNTER0_compareB(uint8_t compare);
void TIMER_COUNTER0_start(uint16_t prescaler);
void TIMER_COUNTER0_stop(void);
/******/
void TIMER_COUNTER1_compoutmodeA(uint8_t compoutmode);
void TIMER_COUNTER1_compoutmodeB(uint8_t compoutmode);
void TIMER_COUNTER1_compareA(uint16_t compare);
void TIMER_COUNTER1_compareB(uint16_t compare);
void TIMER_COUNTER1_start(uint16_t prescaler);
void TIMER_COUNTER1_stop(void);
/******/
void TIMER_COUNTER2_compoutmodeA(uint8_t compoutmode);
void TIMER_COUNTER2_compoutmodeB(uint8_t compoutmode);
void TIMER_COUNTER2_compareA(uint8_t compare);
void TIMER_COUNTER2_compareB(uint8_t compare);
void TIMER_COUNTER2_start(uint16_t prescaler);
void TIMER_COUNTER2_stop(void);
/******/
void TIMER_COUNTER3_compoutmodeA(uint8_t compoutmode);
void TIMER_COUNTER3_compoutmodeB(uint8_t compoutmode);
void TIMER_COUNTER3_compareA(uint16_t compare);
void TIMER_COUNTER3_compareB(uint16_t compare);
void TIMER_COUNTER3_start(uint16_t prescaler);
void TIMER_COUNTER3_stop(void);

/*** Internal State ***/
static TIMER_COUNTER0 timer0_setup = {
	.compoutmodeA=TIMER_COUNTER0_compoutmodeA,
	.compoutmodeB=TIMER_COUNTER0_compoutmodeB,
	.compareA=TIMER_COUNTER0_compareA,
	.compareB=TIMER_COUNTER0_compareB,
	.start=TIMER_COUNTER0_start,
	.stop=TIMER_COUNTER0_stop
};
static uint8_t timer0_state;

/*** Internal State ***/
static TIMER_COUNTER1 timer1_setup = {
	.compoutmodeA=TIMER_COUNTER1_compoutmodeA,
	.compoutmodeB=TIMER_COUNTER1_compoutmodeB,
	.compareA=TIMER_COUNTER1_compareA,
	.compareB=TIMER_COUNTER1_compareB,
	.start=TIMER_COUNTER1_start,
	.stop=TIMER_COUNTER1_stop
};
static uint8_t timer1_state;

/*** Internal State ***/
static TIMER_COUNTER2 timer2_setup = {
	.compoutmodeA=TIMER_COUNTER2_compoutmodeA,
	.compoutmodeB=TIMER_COUNTER2_compoutmodeB,
	.compareA=TIMER_COUNTER2_compareA,
	.compareB=TIMER_COUNTER2_compareB,
	.start=TIMER_COUNTER2_start,
	.stop=TIMER_COUNTER2_stop
};
static uint8_t timer2_state;

/*** Internal State ***/
static TIMER_COUNTER3 timer3_setup = {
	.compoutmodeA=TIMER_COUNTER3_compoutmodeA,
	.compoutmodeB=TIMER_COUNTER3_compoutmodeB,
	.compareA=TIMER_COUNTER3_compareA,
	.compareB=TIMER_COUNTER3_compareB,
	.start=TIMER_COUNTER3_start,
	.stop=TIMER_COUNTER3_stop
};
static uint8_t timer3_state;

/**** Handler ****/
void tc0_enable(uint8_t wavegenmode, uint8_t interrupt)
{
	timer0_state=0;
	
	tc0_reg()->ocr0a->var = 0XFF;
	tc0_reg()->ocr0b->var = 0XFF;
	tc0_reg()->tccr0a->var &= ~((1<<WGM00) | (1<<WGM01));
	tc0_reg()->tccr0b->var &= ~(1<<WGM02);
	switch(wavegenmode){
		case 1: // PWM, Phase Correct
			// TOP = 0xFF
			tc0_reg()->tccr0a->var|=(1<<WGM00);
			break;
		case 2: // CTC
			// TOP = OCRA
			tc0_reg()->tccr0a->var|=(1<<WGM01);
			break;
		case 3: // Fast PWM
			// TOP = 0xFF
			tc0_reg()->tccr0a->var|=((1<<WGM01) | (1<<WGM00));
			break;
		case 5: // PWM, Phase Correct
			// TOP = OCRA
			tc0_reg()->tccr0a->var|=((1<<WGM02) | (1<<WGM00));
			break;			
		case 7: // Fast PWM
			// TOP = OCRA
			tc0_reg()->tccr0a->var|=((1<<WGM02) | (1<<WGM01) | (1<<WGM00));
			break;				
		default: // Normal
			// TOP = 0xFF
			break;
	}
	tc0_reg()->timsk0->var &= ~((1<<OCIE0B) | (1<<OCIE0A) | (1<<TOIE0));
	switch(interrupt){
		case 1:
			tc0_reg()->timsk0->var|=(1<<TOIE0);
			cpu_reg()->sreg->par.i = 1;
			break;
		case 2:
			tc0_reg()->timsk0->var|=(1<<OCIE0A);
			cpu_reg()->sreg->par.i = 1;
			break;
		case 3:
			tc0_reg()->timsk0->var|=(1<<OCIE0B);
			cpu_reg()->sreg->par.i = 1;
			break;
		case 4:
			tc0_reg()->timsk0->var|=((1<<OCIE0A) | (1<<OCIE0B));
			cpu_reg()->sreg->par.i = 1;
			break;
		case 5:
			tc0_reg()->timsk0->var|=((1<<TOIE0) | (1<<OCIE0A) | (1<<OCIE0B));
			cpu_reg()->sreg->par.i = 1;
			break;
		case 6:
			tc0_reg()->timsk0->var|=((1<<TOIE0) | (1<<OCIE0A));
			cpu_reg()->sreg->par.i = 1;
			break;
		case 7:
			tc0_reg()->timsk0->var|=((1<<TOIE0) | (1<<OCIE0B));
			cpu_reg()->sreg->par.i = 1;
			break;
		default:
			break;
	}
}

TIMER_COUNTER0* tc0(void){ return &timer0_setup; }

/**** Procedure and Function definition ****/
void TIMER_COUNTER0_start(uint16_t prescaler)
{
	uint8_t timer0_prescaler;
	tc0_reg()->tccr0b->var &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));
	if(timer0_state==0){
		tc0_reg()->tcnt0->var=0X00;
		switch(prescaler){
			case 0: // No clock source (Timer/Counter stopped).
			timer0_prescaler = 0x00;
			break;
			case 1: // clk T0S /(No prescaler)
			timer0_prescaler=(1<<CS00);
			break;
			case 8: // clk T0S /8 (From prescaler)
			timer0_prescaler=(1<<CS01);
			break;
			case 64: // clk T0S /64 (From prescaler)
			timer0_prescaler=((1<<CS01) | (1<<CS00));
			break;
			case 256: // clk T 0 S /256 (From prescaler)
			timer0_prescaler=(1<<CS02);
			break;
			case 1024: // clk T 0 S /1024 (From prescaler)
			timer0_prescaler=((1<<CS02) | (1<<CS00));
			break;
			case 6: // External clock source on T0 pin. Clock on falling edge.
			timer0_prescaler=((1<<CS02) | (1<<CS01));
			break;
			case 7: // External clock source on T0 pin. Clock on rising edge.
			timer0_prescaler=((1<<CS02) | (1<<CS01) | (1<<CS00));
			break;
			default: // clk T 0 S /1024 (From prescaler)
			timer0_prescaler=((1<<CS02) | (1<<CS00));
			break;
		}
		tc0_reg()->tccr0b->var|=timer0_prescaler;
		timer0_state=1;
	}
}
void TIMER_COUNTER0_compoutmodeA(uint8_t compoutmode)
{
	tc0_reg()->tccr0a->var&=~((1<<COM0A1) | (1<<COM0A0));
	switch(compoutmode){
		case 1:
		/***Compare Output mode, non-PWM mode.***/
		// Toggle OC0A on compare match
		/*** Compare Output mode, Fast PWM mode. ***/
		// WGM02 = 0: Normal Port Operation, OC0A Disconnected.
		// WGM02 = 1: Toggle OC0A on Compare Match.
		/*** Compare Output mode, Phase Correct PWM mode. ***/
		// WGM02 = 0: Normal Port Operation, OC0A Disconnected.
		// WGM02 = 1: Toggle OC0A on Compare Match.
		gpiob_reg()->ddr->par.bit3 = 1;
		tc0_reg()->tccr0a->var|=(1<<COM0A0);
		break;
		case 2:
		/***Compare Output mode, non-PWM mode.***/
		// Clear OC0A on compare match
		/*** Compare Output mode, Fast PWM mode. ***/
		// Clear OC0A on Compare Match, set OC0A at BOTTOM, (non-inverting mode).
		/*** Compare Output mode, Phase Correct PWM mode. ***/
		// Clear OC0A on Compare Match when up-counting. Set OC0A on Compare Match when down-counting.
		gpiob_reg()->ddr->par.bit3 = 1;
		tc0_reg()->tccr0a->var|=(1<<COM0A1);
		break;
		case 3:
		/***Compare Output mode, non-PWM mode.***/
		// Set OC0A on compare match
		/*** Compare Output mode, Fast PWM mode. ***/
		// Set OC0A on Compare Match, clear OC0A at BOTTOM, (inverting mode).
		/*** Compare Output mode, Phase Correct PWM mode. ***/
		// Set OC0A on Compare Match when up-counting. Clear OC0A on Compare Match when down-counting.
		gpiob_reg()->ddr->par.bit3 = 1;
		tc0_reg()->tccr0a->var|=((1<<COM0A0) | (1<<COM0A1));
		break;
		default:
		/***Compare Output mode, non-PWM mode.***/
		// Normal port operation, OC0A disconnected
		/*** Compare Output mode, Fast PWM mode. ***/
		// Normal port operation, OC0A disconnected
		/*** Compare Output mode, Phase Correct PWM mode. ***/
		// Normal port operation, OC0A disconnected
		break;
	}
}
void TIMER_COUNTER0_compoutmodeB(uint8_t compoutmode)
{
	tc0_reg()->tccr0a->var&=~((1<<COM0B1) | (1<<COM0B0));
	switch(compoutmode){
		case 1:
		/*** Compare Output mode, non-PWM mode. ***/
		// Toggle OC0B on Compare Match
		/*** Compare Output mode, Fast PWM mode. ***/
		// Reserved
		/*** Compare Output mode, Phase Correct PWM mode ***/
		// Reserved
		gpiob_reg()->ddr->par.bit4 = 1;
		tc0_reg()->tccr0a->var|=(1<<COM0B0);
		break;
		case 2:
		/*** Compare Output mode, non-PWM mode. ***/
		// Clear OC0B on Compare Match
		/*** Compare Output mode, Fast PWM mode. ***/
		// Clear OC0B on Compare Match, set OC0B at BOTTOM, (non-inverting mode).
		/*** Compare Output mode, Phase Correct PWM mode ***/
		// Clear OC0B on Compare Match when up-counting. Set OC0B on Compare Match when down-counting.
		gpiob_reg()->ddr->par.bit4 = 1;
		tc0_reg()->tccr0a->var|=(1<<COM0B1);
		break;
		case 3:
		/*** Compare Output mode, non-PWM mode. ***/
		// Set OC0B on Compare Match
		/*** Compare Output mode, Fast PWM mode. ***/
		// Set OC0B on Compare Match, clear OC0B at BOTTOM, (inverting mode).
		/*** Compare Output mode, Phase Correct PWM mode ***/
		// Set OC0B on Compare Match when up-counting. Clear OC0B on Compare Match when down-counting.
		gpiob_reg()->ddr->par.bit4 = 1;
		tc0_reg()->tccr0a->var|=((1<<COM0B0) | (1<<COM0B1));
		break;
		default:
		/*** Compare Output mode, non-PWM mode. ***/
		// Normal port operation, OC0B disconnected.
		/*** Compare Output mode, Fast PWM mode. ***/
		// Normal port operation, OC0B disconnected.
		/*** Compare Output mode, Phase Correct PWM mode ***/
		// Normal port operation, OC0B disconnected.
		break;
	}
}
void TIMER_COUNTER0_compareA(uint8_t compare)
{
	tc0_reg()->ocr0a->var=compare;
}
void TIMER_COUNTER0_compareB(uint8_t compare)
{
	tc0_reg()->ocr0b->var=compare;
}
void TIMER_COUNTER0_stop(void)
{
	tc0_reg()->tccr0b->var&=~((1<<CS02) | (1<<CS01) | (1<<CS00));
	timer0_state=0;
}

/***** Handler *****/
void tc1_enable(uint8_t wavegenmode, uint8_t interrupt)
{
	timer1_state=0;
	
	tc1_reg()->ocr1a->var = 0XFFFF;
	tc1_reg()->ocr1b->var = 0XFFFF;
	tc1_reg()->tccr1a->var &= ~((1<<WGM11) | (1<<WGM10));
	tc1_reg()->tccr1b->var &= ~((1<<WGM13) | (1<<WGM12));
	
	switch(wavegenmode){
		case 1: // PWM, Phase Correct, 8-bit
			// TOP = 0x00FF
			tc1_reg()->tccr1a->var|=(1<<WGM10);
			break;
		case 2:	// PWM, Phase Correct, 9-bit
			// TOP = 0x01FF
			tc1_reg()->tccr1a->var|=(1<<WGM11);
			break;
		case 3:	// PWM, Phase Correct, 10-bit
			// TOP = 0x3FF
			tc1_reg()->tccr1a->var|=((1<<WGM11) | (1<<WGM10));
			break;
		case 4:	// CTC
			// TOP = OCR1A
			tc1_reg()->tccr1b->var|=(1<<WGM12);
			break;
		case 5:	// Fast PWM, 8-bit
			// TOP = 0x00FF
			tc1_reg()->tccr1a->var|=(1<<WGM10);
			tc1_reg()->tccr1b->var|=(1<<WGM12);
			break;
		case 6:	// Fast PWM, 9-bit
			// TOP = 0x1FF
			tc1_reg()->tccr1a->var|=(1<<WGM11);
			tc1_reg()->tccr1b->var|=(1<<WGM12);
			break;
		case 7:	// Fast PWM, 10-bit
			// TOP = 0x3FF
			tc1_reg()->tccr1a->var|=((1<<WGM11) | (1<<WGM10));
			tc1_reg()->tccr1b->var|=(1<<WGM12);
			break;
		case 8:	// PWM, Phase and Frequency Correct
			// TOP = ICR1
			tc1_reg()->tccr1b->var|=(1<<WGM13);
			break;
		case 9:	// PWM, Phase and Frequency Correct
			// TOP = OCR1A
			tc1_reg()->tccr1c->var&=~((1<<FOC1A) | (1<<FOC1B));
			tc1_reg()->tccr1a->var|=(1<<WGM10);
			tc1_reg()->tccr1b->var|=(1<<WGM13);
			break;
		case 10: // PWM, Phase Correct
			// TOP = ICR1
			tc1_reg()->tccr1a->var|=(1<<WGM11);
			tc1_reg()->tccr1b->var|=(1<<WGM13);
			break;
		case 11: // PWM, Phase Correct
			// TOP = OCR1A
			tc1_reg()->tccr1c->var&=~((1<<FOC1A) | (1<<FOC1B));
			tc1_reg()->tccr1a->var|=((1<<WGM11) | (1<<WGM10));
			tc1_reg()->tccr1b->var|=(1<<WGM13);
			break;
		case 12: // CTC
			// TOP = ICR1
			tc1_reg()->tccr1b->var|=((1<<WGM13) | (1<<WGM12));
			break;
		case 14: // Fast PWM
			// TOP = ICR1
			tc1_reg()->tccr1a->var|=(1<<WGM11);
			tc1_reg()->tccr1b->var|=((1<<WGM13) | (1<<WGM12));
			break;
		case 15: // Fast PWM
			// TOP = OCR1A
			tc1_reg()->tccr1c->var&=~((1<<FOC1A) | (1<<FOC1B));
			tc1_reg()->tccr1a->var|=((1<<WGM11) | (1<<WGM10));
			tc1_reg()->tccr1b->var|=((1<<WGM13) | (1<<WGM12));
			break;
		default: // Normal
			// TOP = 0xFFFF
			break;
	}
	tc1_reg()->timsk1->var&=~((1<<ICIE1) | (1<<OCIE1A) | (1<<OCIE1B) | (1<<TOIE1));
	switch(interrupt){
		case 1:
			tc1_reg()->timsk1->var|=(1<<TOIE1);
			cpu_reg()->sreg->par.i = 1;
			break;
		case 2:
			tc1_reg()->timsk1->var|=(1<<OCIE1B);
			cpu_reg()->sreg->par.i = 1;
			break;
		case 3:
			tc1_reg()->timsk1->var|=(1<<OCIE1A);
			cpu_reg()->sreg->par.i = 1;
		break;
			case 4:
			tc1_reg()->timsk1->var|=(1<<ICIE1);
			cpu_reg()->sreg->par.i = 1;
		break;
			case 6:
			tc1_reg()->timsk1->var|=((1<<OCIE1B) | (1<<TOIE1));
			cpu_reg()->sreg->par.i = 1;
			break;
		case 7:
			tc1_reg()->timsk1->var|=((1<<OCIE1A) | (1<<TOIE1));
			cpu_reg()->sreg->par.i = 1;
			break;
		case 8:
			tc1_reg()->timsk1->var|=((1<<OCIE1A) | (1<<OCIE1B));
			cpu_reg()->sreg->par.i = 1;
			break;
		case 9:
			tc1_reg()->timsk1->var|=((1<<OCIE1A) | (1<<OCIE1B) | (1<<TOIE1));
			cpu_reg()->sreg->par.i = 1;
			break;
		default:
			break;
	}
}

TIMER_COUNTER1* tc1(void){ return &timer1_setup; }

/**** Procedure and Function definition ****/
void TIMER_COUNTER1_start(uint16_t prescaler)
{
	uint8_t timer1_prescaler;
	tc1_reg()->tccr1b->var &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));
	if(timer1_state==0){
		tc1_reg()->tcnt1->var=0X0000;
		switch(prescaler){
			case 0: // No clock source (Timer/Counter stopped).
				timer1_prescaler=0x0000; 
			case 1: // clkI/O/1 (No prescaling)
				timer1_prescaler=(1<<CS10);
				break;
			case 8: // clkI/O/8 (From prescaler)
				timer1_prescaler=(1<<CS11);
				break;
			case 64: // clkI/O/64 (From prescaler)
				timer1_prescaler=((1<<CS11) | (1<<CS10));
				break;
			case 256: // clkI/O/256 (From prescaler)
				timer1_prescaler=(1<<CS12);
				break;
			case 1024: // clkI/O/1024 (From prescaler)
				timer1_prescaler=((1<<CS12) | (1<<CS10));
				break;
			case 6: // External clock source on Tn pin. Clock on falling edge
				timer1_prescaler=((1<<CS12) | (1<<CS11));
				break;
			case 7: // External clock source on Tn pin. Clock on rising edge
				timer1_prescaler=((1<<CS12) | (1<<CS11) | (7<<CS10));
				break;
			default:
				timer1_prescaler=((1<<CS12) | (1<<CS10));
				break;
		}
		tc1_reg()->tccr1b->var|=timer1_prescaler;
		timer1_state=1;
	}
}
void TIMER_COUNTER1_compoutmodeA(uint8_t compoutmode)
{
	tc1_reg()->tccr1a->var&=~((1<<COM1A1) | (1<<COM1A0));
	switch(compoutmode){
		case 1:
			/*** Compare Output mode, non-PWM. ***/
			// Toggle OCnA/OCnB on Compare Match.
			/*** Compare Output mode, fast PWM ***/
			// WGMn3:0 = 14 or 15: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation).
			// For all other WGM1 settings, normal port operation, OC1A/OC1B disconnected.
			/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
			// WGMn3:0 = 9 or 11: Toggle OCnA on Compare Match, OCnB disconnected (normal port operation).
			// For all other WGM1 settings, normal port operation, OC1A/OC1B disconnected.
			gpiod_reg()->ddr->par.bit5 = 1;
			tc1_reg()->tccr1a->var|=(1<<COM1A0);
			break;
		case 2:
			/*** Compare Output mode, non-PWM. ***/
			// Clear OCnA/OCnB on Compare Match (Set output to low level).
			/*** Compare Output mode, fast PWM ***/
			// Clear OCnA/OCnB on Compare Match, set OCnA/OCnB at BOTTOM (non-inverting mode)
			/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
			// Clear OCnA/OCnB on Compare Match when up-counting.
			// Set OCnA/OCnB on Compare Match when down counting.
			gpiod_reg()->ddr->par.bit5 = 1;
			tc1_reg()->tccr1a->var|=(1<<COM1A1);
			break;
		case 3:
			/*** Compare Output mode, non-PWM. ***/
			// Set OCnA/OCnB on Compare Match (Set output to high level).
			/*** Compare Output mode, fast PWM ***/
			// Set OCnA/OCnB on Compare Match, clear OCnA/OCnB at BOTTOM (inverting mode)
			/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
			// Set OCnA/OCnB on Compare Match when up-counting.
			// Clear OCnA/OCnB on Compare Match when down counting.
			gpiod_reg()->ddr->par.bit5 = 1;
			tc1_reg()->tccr1a->var|=((1<<COM1A0) | (1<<COM1A1));
			break;
		default:
			/*** Compare Output mode, non-PWM. ***/
			// Normal port operation, OCnA/OCnB disconnected.
			/*** Compare Output mode, fast PWM ***/
			// Normal port operation, OCnA/OCnB disconnected.
			/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/ 
			// Normal port operation, OCnA/OCnB disconnected.
			break;
	}
}
void TIMER_COUNTER1_compoutmodeB(uint8_t compoutmode)
{
	tc1_reg()->tccr1a->var&=~((1<<COM1B1) | (1<<COM1B0));
	switch(compoutmode){
		case 1:
		/*** Compare Output mode, non-PWM. ***/
		// Toggle OCnA/OCnB on Compare Match.
		/*** Compare Output mode, fast PWM ***/
		// WGMn3:0 = 14 or 15: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation).
		// For all other WGM1 settings, normal port operation, OC1A/OC1B disconnected.
		/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
		// WGMn3:0 = 9 or 11: Toggle OCnA on Compare Match, OCnB disconnected (normal port operation).
		// For all other WGM1 settings, normal port operation, OC1A/OC1B disconnected.
		gpiod_reg()->ddr->par.bit4 = 1;
		tc1_reg()->tccr1a->var|=(1<<COM1B0);
		break;
		case 2:
		/*** Compare Output mode, non-PWM. ***/
		// Clear OCnA/OCnB on Compare Match (Set output to low level).
		/*** Compare Output mode, fast PWM ***/
		// Clear OCnA/OCnB on Compare Match, set OCnA/OCnB at BOTTOM (non-inverting mode)
		/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
		// Clear OCnA/OCnB on Compare Match when up-counting.
		// Set OCnA/OCnB on Compare Match when down counting.
		gpiod_reg()->ddr->par.bit4 = 1;
		tc1_reg()->tccr1a->var|=(1<<COM1B1);
		break;
		case 3:
		/*** Compare Output mode, non-PWM. ***/
		// Set OCnA/OCnB on Compare Match (Set output to high level).
		/*** Compare Output mode, fast PWM ***/
		// Set OCnA/OCnB on Compare Match, clear OCnA/OCnB at BOTTOM (inverting mode)
		/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
		// Set OCnA/OCnB on Compare Match when up-counting.
		// Clear OCnA/OCnB on Compare Match when down counting.
		gpiod_reg()->ddr->par.bit4 = 1;
		tc1_reg()->tccr1a->var|=((1<<COM1B0) | (1<<COM1B1));
		break;
		default:
		/*** Compare Output mode, non-PWM. ***/
		// Normal port operation, OCnA/OCnB disconnected.
		/*** Compare Output mode, fast PWM ***/
		// Normal port operation, OCnA/OCnB disconnected.
		/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
		// Normal port operation, OCnA/OCnB disconnected.
		break;
	}
}
void TIMER_COUNTER1_compareA(uint16_t compare)
{
	tc1_reg()->ocr1a->var=compare;
}
void TIMER_COUNTER1_compareB(uint16_t compare)
{
	tc1_reg()->ocr1b->var=compare;
}
void TIMER_COUNTER1_stop(void)
{
	tc1_reg()->tccr1b->var&=~((1<<CS12) | (1<<CS11) | (1<<CS10));
	timer1_state=0;
}

/**** Handler *****/
void tc2_enable(unsigned char wavegenmode, unsigned char interrupt)
{
	timer2_state=0;
	
	tc2_reg()->ocr2a->var = 0XFF;
	tc2_reg()->ocr2b->var = 0XFF;
	tc2_reg()->tccr2a->var &= ~((1<<WGM20) | (1<<WGM21));
	tc2_reg()->tccr2b->var &= ~(1<<WGM22);
	
	switch(wavegenmode){
		case 1: // PWM, Phase Correct
			// TOP = 0xFF
			tc2_reg()->tccr2a->var|=(1<<WGM20);
			break;
		case 2: // CTC
			// TOP = OCRA
			tc2_reg()->tccr2a->var|=(1<<WGM21);
			break;
		case 3: // Fast PWM
			// TOP = 0xFF
			tc2_reg()->tccr2a->var|=((1<<WGM20) | (1<<WGM21));
			break;
		case 5: // PWM, Phase Correct
			// TOP = OCRA
			tc2_reg()->tccr2b->var&=~((1<<FOC2A) | (1<<FOC2B));
			tc2_reg()->tccr2a->var|=(1<<WGM20);
			tc2_reg()->tccr2b->var|=(1<<WGM22);
			break;
		case 7: // Fast PWM
			// TOP = OCRA
			tc2_reg()->tccr2b->var&=~((1<<FOC2A) | (1<<FOC2B));
			tc2_reg()->tccr2a->var|=((1<<WGM20) | (1<<WGM21));
			tc2_reg()->tccr2b->var|=(1<<WGM22);
			break;
		default: //// Normal
			// TOP = 0xFF
			break;
	}
	tc2_reg()->timsk2->var &= ~((1<<TOIE2) | (1<<OCIE2A) | (1<<OCIE2B));
	switch(interrupt){
		case 1:
			tc2_reg()->timsk2->var|=(1<<TOIE2);
			cpu_reg()->sreg->par.i = 1;
			break;
		case 2:
			tc2_reg()->timsk2->var|=(1<<OCIE2A);
			cpu_reg()->sreg->par.i = 1;
			break;
		case 3:
			tc2_reg()->timsk2->var|=(1<<OCIE2B);
			cpu_reg()->sreg->par.i = 1;
			break;
		case 4:
			tc2_reg()->timsk2->var|=((1<<OCIE2A) | (1<<OCIE2B));
			cpu_reg()->sreg->par.i = 1;
			break;
		case 5:
			tc2_reg()->timsk2->var|=((1<<OCIE2A) | (1<<OCIE2B) | (1<<TOIE2));
			cpu_reg()->sreg->par.i = 1;
			break;
		case 6:
			tc2_reg()->timsk2->var|=((1<<TOIE2) | (1<<OCIE2A));
			cpu_reg()->sreg->par.i = 1;
			break;
		case 7:
			tc2_reg()->timsk2->var|=((1<<TOIE2) | (1<<OCIE2B));
			cpu_reg()->sreg->par.i = 1;
			break;
		default:
			break;
	}
}

TIMER_COUNTER2* tc2(void){ return &timer2_setup; }

/**** Procedure and Function definition ****/
void TIMER_COUNTER2_start(uint16_t prescaler)
{
	uint8_t timer2_prescaler;
	tc2_reg()->tccr2b->var &= ~((1<<CS22) | (1<<CS21) | (1<<CS20));
	if(timer2_state==0){
		tc2_reg()->tcnt2->var=0X00;
		switch(prescaler){
			case 0: // No clock source (Timer/Counter stopped).
				timer2_prescaler=0x00;
				break;
			case 1: // clkI/O/(No prescaler)
				timer2_prescaler=(1<<CS20);
				break;
			case 8: // clkI/O/8 (From prescaler)
				timer2_prescaler=(1<<CS21);
				break;
			case 32: // clkI/O/32 (From prescaler)
				timer2_prescaler=((1<<CS21) | (1<<CS20));
				break;
			case 64: // clkI/O/64 (From prescaler)
				timer2_prescaler=(1<<CS22);
				break;
			case 128: // clkI/O/128 (From prescaler)
				timer2_prescaler=((1<<CS22) | (1<<CS20));
				break;
			case 256: // clkI/O/256 (From prescaler)
				timer2_prescaler=((1<<CS22) | (1<<CS21));
				break;
			case 1024: // clkI/O/1024 (From prescaler)
				timer2_prescaler=((1<<CS22) | (1<<CS21) | (1<<CS20));
				break;
			default:
				timer2_prescaler=((1<<CS22) | (1<<CS21) | (1<<CS20));
				break;
		}
		tc2_reg()->tccr2b->var|=timer2_prescaler;
		timer2_state=1;
	}
}
void TIMER_COUNTER2_compoutmodeA(uint8_t compoutmode)
{
	tc2_reg()->tccr2a->var&=~((1<<COM2A1) | (1<<COM2A0));
	switch(compoutmode){ // see table 53, 54, 55 in data sheet for more information
		case 1:
		/***Compare Output mode, non-PWM mode.***/
		// Toggle OC2A on compare match
		/*** Compare Output mode, Fast PWM mode. ***/
		// WGM02 = 0: Normal Port Operation, OC2A Disconnected.
		// WGM02 = 1: Toggle OC2A on Compare Match.
		/*** Compare Output mode, Phase Correct PWM mode. ***/
		// WGM02 = 0: Normal Port Operation, OC2A Disconnected.
		// WGM02 = 1: Toggle OC2A on Compare Match.
		gpiod_reg()->ddr->par.bit7 = 1;
		tc2_reg()->tccr2a->var|=(1<<COM2A0);
		break;
		case 2:
		/***Compare Output mode, non-PWM mode.***/
		// Clear OC2A on compare match
		/*** Compare Output mode, Fast PWM mode. ***/
		// Clear OC2A on Compare Match, set OC2A at BOTTOM, (non-inverting mode).
		/*** Compare Output mode, Phase Correct PWM mode. ***/
		// Clear OC2A on Compare Match when up-counting. Set OC2A on Compare Match when down-counting.
		gpiod_reg()->ddr->par.bit7 = 1;
		tc2_reg()->tccr2a->var|=(1<<COM2A1);
		break;
		case 3:
		/***Compare Output mode, non-PWM mode.***/
		// Set OC2A on compare match
		/*** Compare Output mode, Fast PWM mode. ***/
		// Set OC2A on Compare Match, clear OC2A at BOTTOM, (inverting mode).
		/*** Compare Output mode, Phase Correct PWM mode. ***/
		// Set OC2A on Compare Match when up-counting. Clear OC2A on Compare Match when down-counting.
		gpiod_reg()->ddr->par.bit7 = 1;
		tc2_reg()->tccr2a->var|=((1<<COM2A0) | (1<<COM2A1));
		break;
		default:
		/***Compare Output mode, non-PWM mode.***/
		// Normal port operation, OC2A disconnected
		/*** Compare Output mode, Fast PWM mode. ***/
		// Normal port operation, OC2A disconnected
		/*** Compare Output mode, Phase Correct PWM mode. ***/
		// Normal port operation, OC2A disconnected
		break;
	}
}
void TIMER_COUNTER2_compoutmodeB(uint8_t compoutmode)
{
	tc2_reg()->tccr2a->var&=~((1<<COM2B1) | (1<<COM2B0));
	switch(compoutmode){
		case 1:
		/*** Compare Output mode, non-PWM mode. ***/
		// Toggle OC2B on Compare Match
		/*** Compare Output mode, Fast PWM mode. ***/
		// Reserved
		/*** Compare Output mode, Phase Correct PWM mode ***/
		// Reserved
		gpiod_reg()->ddr->par.bit6 = 1;
		tc2_reg()->tccr2a->var|=(1<<COM2B0);
		break;
		case 2:
		/*** Compare Output mode, non-PWM mode. ***/
		// Clear OC2B on Compare Match
		/*** Compare Output mode, Fast PWM mode. ***/
		// Clear OC2B on Compare Match, set OC2B at BOTTOM, (non-inverting mode).
		/*** Compare Output mode, Phase Correct PWM mode ***/
		// Clear OC2B on Compare Match when up-counting. Set OC2B on Compare Match when down-counting.
		gpiod_reg()->ddr->par.bit6 = 1;
		tc2_reg()->tccr2a->var|=(1<<COM2B1);
		break;
		case 3:
		/*** Compare Output mode, non-PWM mode. ***/
		// Set OC2B on Compare Match
		/*** Compare Output mode, Fast PWM mode. ***/
		// Set OC2B on Compare Match, clear OC2B at BOTTOM, (inverting mode).
		/*** Compare Output mode, Phase Correct PWM mode ***/
		// Set OC2B on Compare Match when up-counting. Clear OC2B on Compare Match when down-counting.
		gpiod_reg()->ddr->par.bit6 = 1;
		tc2_reg()->tccr2a->var|=((1<<COM2B0) | (1<<COM2B1));
		break;
		default:
		/*** Compare Output mode, non-PWM mode. ***/
		// Normal port operation, OC2B disconnected.
		/*** Compare Output mode, Fast PWM mode. ***/
		// Normal port operation, OC2B disconnected.
		/*** Compare Output mode, Phase Correct PWM mode ***/
		// Normal port operation, OC2B disconnected.
		break;
	}
}
void TIMER_COUNTER2_compareA(uint8_t compare)
{
	tc2_reg()->ocr2a->var=compare;
}
void TIMER_COUNTER2_compareB(uint8_t compare)
{
	tc2_reg()->ocr2b->var=compare;
}
void TIMER_COUNTER2_stop(void)
{
	tc2_reg()->tccr2b->var &= ~((1<<CS22) | (1<<CS21) | (1<<CS20));
	timer2_state=0;
}

/***** Handler *****/
void tc3_enable(uint8_t wavegenmode, uint8_t interrupt)
{
	timer3_state=0;
	
	tc3_reg()->ocr3a->var = 0XFFFF;
	tc3_reg()->ocr3b->var = 0XFFFF;
	tc3_reg()->tccr3a->var &= ~((1<<WGM11) | (1<<WGM10));
	tc3_reg()->tccr3b->var &= ~((1<<WGM13) | (1<<WGM12));
	
	switch(wavegenmode){
		case 1: // PWM, Phase Correct, 8-bit
		// TOP = 0x00FF
		tc3_reg()->tccr3a->var|=(1<<WGM10);
		break;
		case 2:	// PWM, Phase Correct, 9-bit
		// TOP = 0x01FF
		tc3_reg()->tccr3a->var|=(1<<WGM11);
		break;
		case 3:	// PWM, Phase Correct, 10-bit
		// TOP = 0x3FF
		tc3_reg()->tccr3a->var|=((1<<WGM11) | (1<<WGM10));
		break;
		case 4:	// CTC
		// TOP =OCR3A
		tc3_reg()->tccr3b->var|=(1<<WGM12);
		break;
		case 5:	// Fast PWM, 8-bit
		// TOP = 0x00FF
		tc3_reg()->tccr3a->var|=(1<<WGM10);
		tc3_reg()->tccr3b->var|=(1<<WGM12);
		break;
		case 6:	// Fast PWM, 9-bit
		// TOP = 0x1FF
		tc3_reg()->tccr3a->var|=(1<<WGM11);
		tc3_reg()->tccr3b->var|=(1<<WGM12);
		break;
		case 7:	// Fast PWM, 10-bit
		// TOP = 0x3FF
		tc3_reg()->tccr3a->var|=((1<<WGM11) | (1<<WGM10));
		tc3_reg()->tccr3b->var|=(1<<WGM12);
		break;
		case 8:	// PWM, Phase and Frequency Correct
		// TOP = ICR3
		tc3_reg()->tccr3b->var|=(1<<WGM13);
		break;
		case 9:	// PWM, Phase and Frequency Correct
		// TOP = OCR3A
		tc3_reg()->tccr3c->var&=~((1<<FOC1A) | (1<<FOC1B));
		tc3_reg()->tccr3a->var|=(1<<WGM10);
		tc3_reg()->tccr3b->var|=(1<<WGM13);
		break;
		case 10: // PWM, Phase Correct
		// TOP = ICR3
		tc3_reg()->tccr3a->var|=(1<<WGM11);
		tc3_reg()->tccr3b->var|=(1<<WGM13);
		break;
		case 11: // PWM, Phase Correct
		// TOP = OCR3A
		tc3_reg()->tccr3c->var&=~((1<<FOC1A) | (1<<FOC1B));
		tc3_reg()->tccr3a->var|=((1<<WGM11) | (1<<WGM10));
		tc3_reg()->tccr3b->var|=(1<<WGM13);
		break;
		case 12: // CTC
		// TOP = ICR3
		tc3_reg()->tccr3b->var|=((1<<WGM13) | (1<<WGM12));
		break;
		case 14: // Fast PWM
		// TOP = ICR3
		tc3_reg()->tccr3a->var|=(1<<WGM11);
		tc3_reg()->tccr3b->var|=((1<<WGM13) | (1<<WGM12));
		break;
		case 15: // Fast PWM
		// TOP = OCR3A
		tc3_reg()->tccr3c->var&=~((1<<FOC1A) | (1<<FOC1B));
		tc3_reg()->tccr3a->var|=((1<<WGM11) | (1<<WGM10));
		tc3_reg()->tccr3b->var|=((1<<WGM13) | (1<<WGM12));
		break;
		default: // Normal
		// TOP = 0xFFFF
		break;
	}
	tc3_reg()->timsk3->var&=~((1<<ICIE1) | (1<<OCIE1A) | (1<<OCIE1B) | (1<<TOIE1));
	switch(interrupt){
		case 1:
		tc3_reg()->timsk3->var|=(1<<TOIE1);
		cpu_reg()->sreg->par.i = 1;
		break;
		case 2:
		tc3_reg()->timsk3->var|=(1<<OCIE1B);
		cpu_reg()->sreg->par.i = 1;
		break;
		case 3:
		tc3_reg()->timsk3->var|=(1<<OCIE1A);
		cpu_reg()->sreg->par.i = 1;
		break;
		case 4:
		tc3_reg()->timsk3->var|=(1<<ICIE1);
		cpu_reg()->sreg->par.i = 1;
		break;
		case 6:
		tc3_reg()->timsk3->var|=((1<<OCIE1B) | (1<<TOIE1));
		cpu_reg()->sreg->par.i = 1;
		break;
		case 7:
		tc3_reg()->timsk3->var|=((1<<OCIE1A) | (1<<TOIE1));
		cpu_reg()->sreg->par.i = 1;
		break;
		case 8:
		tc3_reg()->timsk3->var|=((1<<OCIE1A) | (1<<OCIE1B));
		cpu_reg()->sreg->par.i = 1;
		break;
		case 9:
		tc3_reg()->timsk3->var|=((1<<OCIE1A) | (1<<OCIE1B) | (1<<TOIE1));
		cpu_reg()->sreg->par.i = 1;
		break;
		default:
		break;
	}
}

TIMER_COUNTER3* tc3(void){ return &timer3_setup; }

/**** Procedure and Function definition ****/
void TIMER_COUNTER3_start(uint16_t prescaler)
{
	uint8_t timer3_prescaler;
	tc3_reg()->tccr3b->var &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));
	if(timer3_state==0){
		tc3_reg()->tcnt3->var=0X0000;
		switch(prescaler){
			case 0: // No clock source (Timer/Counter stopped).
			timer3_prescaler=0x0000;
			case 1: // clkI/O/1 (No prescaling)
			timer3_prescaler=(1<<CS10);
			break;
			case 8: // clkI/O/8 (From prescaler)
			timer3_prescaler=(1<<CS11);
			break;
			case 64: // clkI/O/64 (From prescaler)
			timer3_prescaler=((1<<CS11) | (1<<CS10));
			break;
			case 256: // clkI/O/256 (From prescaler)
			timer3_prescaler=(1<<CS12);
			break;
			case 1024: // clkI/O/1024 (From prescaler)
			timer3_prescaler=((1<<CS12) | (1<<CS10));
			break;
			case 6: // External clock source on Tn pin. Clock on falling edge
			timer3_prescaler=((1<<CS12) | (1<<CS11));
			break;
			case 7: // External clock source on Tn pin. Clock on rising edge
			timer3_prescaler=((1<<CS12) | (1<<CS11) | (7<<CS10));
			break;
			default:
			timer3_prescaler=((1<<CS12) | (1<<CS10));
			break;
		}
		tc3_reg()->tccr3b->var|=timer3_prescaler;
		timer3_state=1;
	}
}
void TIMER_COUNTER3_compoutmodeA(uint8_t compoutmode)
{
	tc3_reg()->tccr3a->var&=~((1<<COM1A1) | (1<<COM1A0));
	switch(compoutmode){
		case 1:
		/*** Compare Output mode, non-PWM. ***/
		// Toggle OCnA/OCnB on Compare Match.
		/*** Compare Output mode, fast PWM ***/
		// WGMn3:0 = 14 or 15: Toggle OC3A on Compare Match, OC3B disconnected (normal port operation).
		// For all other WGM1 settings, normal port operation, OC3A/OC3B disconnected.
		/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
		// WGMn3:0 = 9 or 11: Toggle OCnA on Compare Match, OCnB disconnected (normal port operation).
		// For all other WGM1 settings, normal port operation, OC3A/OC3B disconnected.
		gpiob_reg()->ddr->par.bit6 = 1;
		tc3_reg()->tccr3a->var|=(1<<COM1A0);
		break;
		case 2:
		/*** Compare Output mode, non-PWM. ***/
		// Clear OCnA/OCnB on Compare Match (Set output to low level).
		/*** Compare Output mode, fast PWM ***/
		// Clear OCnA/OCnB on Compare Match, set OCnA/OCnB at BOTTOM (non-inverting mode)
		/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
		// Clear OCnA/OCnB on Compare Match when up-counting.
		// Set OCnA/OCnB on Compare Match when down counting.
		gpiob_reg()->ddr->par.bit6 = 1;
		tc3_reg()->tccr3a->var|=(1<<COM1A1);
		break;
		case 3:
		/*** Compare Output mode, non-PWM. ***/
		// Set OCnA/OCnB on Compare Match (Set output to high level).
		/*** Compare Output mode, fast PWM ***/
		// Set OCnA/OCnB on Compare Match, clear OCnA/OCnB at BOTTOM (inverting mode)
		/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
		// Set OCnA/OCnB on Compare Match when up-counting.
		// Clear OCnA/OCnB on Compare Match when down counting.
		gpiob_reg()->ddr->par.bit6 = 1;
		tc3_reg()->tccr3a->var|=((1<<COM1A0) | (1<<COM1A1));
		break;
		default:
		/*** Compare Output mode, non-PWM. ***/
		// Normal port operation, OCnA/OCnB disconnected.
		/*** Compare Output mode, fast PWM ***/
		// Normal port operation, OCnA/OCnB disconnected.
		/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
		// Normal port operation, OCnA/OCnB disconnected.
		break;
	}
}
void TIMER_COUNTER3_compoutmodeB(uint8_t compoutmode)
{
	tc3_reg()->tccr3a->var&=~((1<<COM1B1) | (1<<COM1B0));
	switch(compoutmode){
		case 1:
		/*** Compare Output mode, non-PWM. ***/
		// Toggle OCnA/OCnB on Compare Match.
		/*** Compare Output mode, fast PWM ***/
		// WGMn3:0 = 14 or 15: Toggle OC3A on Compare Match, OC3B disconnected (normal port operation).
		// For all other WGM1 settings, normal port operation, OC3A/OC3B disconnected.
		/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
		// WGMn3:0 = 9 or 11: Toggle OCnA on Compare Match, OCnB disconnected (normal port operation).
		// For all other WGM1 settings, normal port operation, OC3A/OC3B disconnected.
		gpiob_reg()->ddr->par.bit7 = 1;
		tc3_reg()->tccr3a->var|=(1<<COM1B0);
		break;
		case 2:
		/*** Compare Output mode, non-PWM. ***/
		// Clear OCnA/OCnB on Compare Match (Set output to low level).
		/*** Compare Output mode, fast PWM ***/
		// Clear OCnA/OCnB on Compare Match, set OCnA/OCnB at BOTTOM (non-inverting mode)
		/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
		// Clear OCnA/OCnB on Compare Match when up-counting.
		// Set OCnA/OCnB on Compare Match when down counting.
		gpiob_reg()->ddr->par.bit7 = 1;
		tc3_reg()->tccr3a->var|=(1<<COM1B1);
		break;
		case 3:
		/*** Compare Output mode, non-PWM. ***/
		// Set OCnA/OCnB on Compare Match (Set output to high level).
		/*** Compare Output mode, fast PWM ***/
		// Set OCnA/OCnB on Compare Match, clear OCnA/OCnB at BOTTOM (inverting mode)
		/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
		// Set OCnA/OCnB on Compare Match when up-counting.
		// Clear OCnA/OCnB on Compare Match when down counting.
		gpiob_reg()->ddr->par.bit7 = 1;
		tc3_reg()->tccr3a->var|=((1<<COM1B0) | (1<<COM1B1));
		break;
		default:
		/*** Compare Output mode, non-PWM. ***/
		// Normal port operation, OCnA/OCnB disconnected.
		/*** Compare Output mode, fast PWM ***/
		// Normal port operation, OCnA/OCnB disconnected.
		/*** Compare Output mode, phase correct and phase and frequency correct PWM. ***/
		// Normal port operation, OCnA/OCnB disconnected.
		break;
	}
}
void TIMER_COUNTER3_compareA(uint16_t compare)
{
	tc3_reg()->ocr3a->var=compare;
}
void TIMER_COUNTER3_compareB(uint16_t compare)
{
	tc3_reg()->ocr3b->var=compare;
}
void TIMER_COUNTER3_stop(void)
{
	tc3_reg()->tccr3b->var&=~((1<<CS12) | (1<<CS11) | (1<<CS10));
	timer3_state=0;
}

/*** EOF ***/

