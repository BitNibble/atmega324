/************************************************************************
	ROTENC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Rotary encoder Potentiometer
Date:     25102020
************************************************************************/
#ifndef _ROTENC_H_
	#define _ROTENC_H_

/*** Library ***/
#include <inttypes.h>

/*** Parameter ***/
typedef struct{
	uint8_t PinChnA;
	uint8_t PinChnB;
	uint8_t pchn;
	uint8_t chn;
	uint16_t num;
}rotaryencoderparameter;
	
struct rotenc{
	// VARIABLIES
	rotaryencoderparameter par;
	// V-table
	rotaryencoderparameter (*rte)(rotaryencoderparameter* par, uint8_t data);
};
typedef struct rotenc ROTENC;

ROTENC rotenc_enable(uint8_t ChnApin, uint8_t ChnBpin);

#endif
/***EOF***/

