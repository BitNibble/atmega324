/*************************************************************************
	ATMEGA 324 TIMER
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega 324 at 8Mhz
Date:     04072025
*************************************************************************/
#ifndef ATMEGA324_TIMER_H_
	#define ATMEGA324_TIMER_H_

#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

#include "atmega324.h"

/*** Interrupt sources 0 ***/
#define TIMER_COUNTER0A_COMPARE_MATCH_INTERRUPT TIMER0_COMPA_vect
#define TIMER_COUNTER0B_COMPARE_MATCH_INTERRUPT TIMER0_COMPB_vect
#define TIMER_COUNTER0_OVERFLOW_INTERRUPT TIMER0_OVF_vect
/*** Interrupt sources 1 ***/
#define TIMER_COUNTER1A_COMPARE_MATCH_INTERRUPT TIMER1_COMPA_vect
#define TIMER_COUNTER1B_COMPARE_MATCH_INTERRUPT TIMER1_COMPB_vect
#define TIMER_COUNTER1_CAPTURE_EVENT_INTERRUPT TIMER1_CAPT_vect
#define TIMER_COUNTER1_OVERFLOW_INTERRUPT TIMER1_OVF_vect
/*** Interrupt sources 2 ***/
#define TIMER_COUNTER2A_COMPARE_MATCH_INTERRUPT TIMER2_COMPA_vect
#define TIMER_COUNTER2B_COMPARE_MATCH_INTERRUPT TIMER2_COMPB_vect
#define TIMER_COUNTER2_OVERFLOW_INTERRUPT TIMER2_OVF_vect

/*** Handler ***/
typedef struct {
	// V-table
	void (*compoutmodeA)(uint8_t compoutmode);
	void (*compoutmodeB)(uint8_t compoutmode);
	void (*compareA)(uint8_t compare);
	void (*compareB)(uint8_t compare);
	void (*start)(uint16_t prescaler);
	void (*stop)(void);
} TIMER_COUNTER0;
/*** Handler ***/
typedef struct {
	// V-table
	void (*compoutmodeA)(uint8_t compoutmode);
	void (*compoutmodeB)(uint8_t compoutmode);
	void (*compareA)(uint16_t compare);
	void (*compareB)(uint16_t compare);
	void (*start)(uint16_t prescaler);
	void (*stop)(void);
} TIMER_COUNTER1, TIMER_COUNTER3;
/*** Handler ***/
typedef struct {
	// V-table
	void (*compoutmodeA)(uint8_t compoutmode);
	void (*compoutmodeB)(uint8_t compoutmode);
	void (*compareA)(uint8_t compare);
	void (*compareB)(uint8_t compare);
	void (*start)(uint16_t prescaler);
	void (*stop)(void);
} TIMER_COUNTER2;

void tc0_enable(uint8_t wavegenmode, uint8_t interrupt);
TIMER_COUNTER0* tc0(void);
void tc1_enable(uint8_t wavegenmode, uint8_t interrupt);
TIMER_COUNTER1* tc1(void);
void tc2_enable(uint8_t wavegenmode, uint8_t interrupt);
TIMER_COUNTER2* tc2(void);
void tc3_enable(uint8_t wavegenmode, uint8_t interrupt);
TIMER_COUNTER3* tc3(void);

#endif
/***EOF***/

