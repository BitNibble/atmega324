/*************************************************************************
	CLOCK
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: all
Date:     31062025
*************************************************************************/
/*** File Library ***/
#include "clock.h"

/*** File Constant & Macro ***/

/*** File Variable ***/
static CLOCK clock_setup;
static RELOGIO_TIME ctime = {0};
static char CLOCK_tmp[9] = {0};

/*** Procedure & Function declaration ***/
void CLOCK_set(uint8_t hour, uint8_t minute, uint8_t second);
void CLOCK_increment(void);
void CLOCK_decrement(void);
char* CLOCK_show(void);

/*** Handler ***/
void clock_enable(uint8_t hour, uint8_t minute, uint8_t second)
{
	
	(hour < 24) ? ctime.hour = hour : (void) hour;  
	(minute < 60) ? ctime.minute = minute : (void) minute;
	(second < 60) ? ctime.second = second : (void) second;
	// V-Table
	clock_setup.set = CLOCK_set;
	clock_setup.increment = CLOCK_increment;
	clock_setup.show = CLOCK_show;
}

CLOCK* clock(void){ return &clock_setup; }

/*** Procedure & Function definition ***/
void CLOCK_set(uint8_t hour, uint8_t minute, uint8_t second)
{
	(hour < 24) ? ctime.hour = hour : (void) hour;
	(minute < 60) ? ctime.minute = minute : (void) minute;
	(second < 60) ? ctime.second = second : (void) second;
}
void CLOCK_increment(void)
{
	ctime.second++;
	if(ctime.second > 59){
		ctime.minute++;
		ctime.second = 0;
		if(ctime.minute > 59){
			ctime.hour++;
			ctime.minute = 0;
			switch (CLOCK_HORA){
				case 24:
					if(ctime.hour > 23)
						ctime.hour = 0;
				break;
				case 12:
					if (ctime.hour > 12)
						ctime.hour = 1;
				break;
				default:
					if(ctime.hour > 23)
						ctime.hour = 0;
				break;
			}
		}
	}
}

void CLOCK_decrement(void)
{
	ctime.second--;
	if(ctime.second < 0){
		ctime.minute--;
		ctime.second = 59;
		if(ctime.minute < 0){
			ctime.hour--;
			ctime.minute = 59;
			switch (CLOCK_HORA){
				case 24:
					if(ctime.hour < 0)
						ctime.hour= 23;
				break;
				case 12:
					if (ctime.hour < 1)
						ctime.hour = 12;
				break;
				default:
					if(ctime.hour < 0)
						ctime.hour = 23;
				break;
			}
		}
	}		
}

char* CLOCK_show(void)
{
	uint8_t tmp;
	CLOCK_tmp[8] = '\0';
	CLOCK_tmp[7] = ctime.second % 10 + '0';
	tmp = ctime.second / 10;
	CLOCK_tmp[6] = tmp % 10 + '0';
	CLOCK_tmp[5] = ':';
	CLOCK_tmp[4] = ctime.minute % 10 + '0';
	tmp = ctime.minute / 10;
	CLOCK_tmp[3] = tmp % 10 + '0';
	CLOCK_tmp[2] = ':';
	CLOCK_tmp[1] = ctime.hour % 10 + '0';
	tmp = ctime.hour / 10;
	CLOCK_tmp[0] = tmp % 10 + '0';
	return CLOCK_tmp;
}

/*** EOF ***/

