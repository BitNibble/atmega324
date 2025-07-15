/******************************************************************************
	BUFFER
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: all
Date:     26062025
******************************************************************************/
/*** File Library ***/
#include "buffer.h"
#include <stdio.h>
#include <string.h>

/*** Procedure & Function declaration ***/
void BUFF_push(buffer_parameter* par, BUFFvar data);
BUFFvar* BUFF_raw(buffer_parameter* par);
void BUFF_flush(buffer_parameter* par);

/*** Handler ***/
BUFF buff_enable( uint8_t size_buff, BUFFvar* buff )
{
	// OBJECT STRUCT
	BUFF ret_setup;
	// inic VAR
	ret_setup.par.orig = buff;
	ret_setup.par.head = buff;
	ret_setup.par.end = buff + ( size_buff );
	// V-table
	ret_setup.push = BUFF_push;
	ret_setup.raw = BUFF_raw;
	ret_setup.flush = BUFF_flush;
	return ret_setup; // return copy
}

/*** Procedure & Function definition ***/
void BUFF_push( buffer_parameter* par, BUFFvar data ){
	BUFFvar* head; BUFFvar* next;
	head = par->head;
	if(data){
		if( head == par->end ){
			head = par->orig;
			next = head + 1;
		}else{
			next = head + 1;
		}
			*head = data;
			*next = 0;
			par->head = next;
	}
}

BUFFvar* BUFF_raw( buffer_parameter* par ){
		return par->orig;
}

void BUFF_flush( buffer_parameter* par ){
	BUFFvar* head;
	head = par->orig;
	par->head = head;
	*head = 0;
}

/*** EOF ***/

