/******************************************************************************
	BUFFER
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: all
Date:     26062025
*******************************************************************************/
#ifndef _BUFFER_H_
	#define _BUFFER_H_

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/
#define BUFFvar char

/*** Typedef ***/
typedef struct {
	BUFFvar* orig;
	BUFFvar* head;
	BUFFvar* end;
}buffer_parameter;

/*** Handler ***/
struct buffer
{
	buffer_parameter par;
	void (*push)(buffer_parameter* par, BUFFvar data);
	BUFFvar* (*raw)(buffer_parameter* par);
	void (*flush)(buffer_parameter* par);
};
typedef struct buffer BUFF;

BUFF buff_enable(uint8_t size_buff, BUFFvar* buff);

#endif
/***EOF***/

