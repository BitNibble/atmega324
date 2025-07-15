/******************************************************************************
	BUFFER
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: all
Date:     26062025
******************************************************************************/
/*** Library ***/
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
	/*** Local State ***/
	BUFF ret_setup = {
	.par = {
		.orig = buff,
		.head = buff,
		.end = buff + ( size_buff )
	},
	// V-table
	.push = BUFF_push,
	.raw = BUFF_raw,
	.flush = BUFF_flush
	};
	
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

