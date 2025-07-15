/************************************************************************
	ROTENC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Rotary encoder Potentiometer
Date:     25102020
************************************************************************/
/*** Library ***/
#include "rotenc.h"

/*** Procedure and Funtion declaration ***/
rotaryencoderparameter RotEnc_rte(rotaryencoderparameter* par, uint8_t data);

/*** Handler ***/
ROTENC rotenc_enable( uint8_t ChnApin, uint8_t ChnBpin )
{
	// struct object
	ROTENC rtnc_setup;
	// Initialize variables
	rtnc_setup.par.PinChnA = ChnApin;
	rtnc_setup.par.PinChnB = ChnBpin;
	rtnc_setup.par.pchn = rtnc_setup.par.chn = (1 << ChnBpin) | (1 << ChnApin);
	rtnc_setup.par.num = 0;
	// V-table
	rtnc_setup.rte = RotEnc_rte;
	
	return rtnc_setup;
}

/*** Procedure and Funtion definition ***/
rotaryencoderparameter RotEnc_rte(rotaryencoderparameter* par, uint8_t data)
{
	uint8_t hl;
	par->chn = data & ((1 << par->PinChnB) | (1 << par->PinChnA));
	hl = par->chn ^ par->pchn;
	hl &= par->pchn;
	if(par->pchn != par->chn){
		if((par->pchn == ((1 << par->PinChnB) | (1 << par->PinChnA))) && (hl & (1 << par->PinChnA)))
		par->num++;
		if((par->pchn == ((1 << par->PinChnB) | (1 << par->PinChnA))) && (hl & (1 << par->PinChnB)))
		par->num--;
	}
	par->pchn = par->chn;
	return *par;
}

/*** EOF ***/

