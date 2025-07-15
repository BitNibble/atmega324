/************************************************************************
	ATCOMMANDS
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ALL
Date:     24042023
************************************************************************/
#ifndef _ATCOMMANDS_H_
	#define _ATCOMMANDS_H_

/*** Library ***/
#include <inttypes.h>

/*** Procedure and Function declaration ***/
char* BT05ATcmd(uint16_t num);
char* HC42ATcmd(uint16_t num);
char* HC05ATcmd(uint16_t num);
char* ESP8266cmd(uint16_t num);

#endif
/*** EOF ***/

