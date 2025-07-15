/************************************************************************
Title:    watch.h
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Date:     03072025
************************************************************************/
#ifndef _WATCH_H_
	#define _WATCH_H_

/*** Global library ***/
#include <inttypes.h>

/*** Global Variable ***/
typedef struct {
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	volatile uint32_t seconds;
} WATCH_TIME;

/*** Handle ***/
typedef struct {
	void (*preset)(uint8_t hour, uint8_t minute, uint8_t second);
	uint8_t (*start_delay)(uint8_t n_delay, uint32_t seconds);
	void (*increment)(void);
	char* (*show)(void);
} WATCH;

void watch_enable(void);
WATCH* watch(void);

/*** Global Header ***/
extern void WATCH_increment(void);
extern void WATCH_decrement(void);

#endif
/***EOF***/

