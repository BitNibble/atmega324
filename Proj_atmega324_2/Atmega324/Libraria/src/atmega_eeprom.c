/*************************************************************************
	eeprom wrapper
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ATmega
Date:     04072025
*************************************************************************/
#include "atmega_eeprom.h"

static EEPROM eeprom_setup;

/*** Handler ***/
void eeprom_enable(void) {
	// V-table
	eeprom_setup.read_byte = eeprom_read_byte;
	eeprom_setup.write_byte = eeprom_write_byte;
	eeprom_setup.update_byte = eeprom_update_byte;
	eeprom_setup.read_word = eeprom_read_word;
	eeprom_setup.write_word = eeprom_write_word;
	eeprom_setup.update_word = eeprom_update_word;
	//eeprom_setup.read_dword = eeprom_read_dword;
	eeprom_setup.write_dword = eeprom_write_dword;
	eeprom_setup.write_dword = eeprom_write_dword;
	//eeprom_setup.read_float = eeprom_read_float;
	eeprom_setup.write_float = eeprom_write_float;
	eeprom_setup.update_float = eeprom_update_float;
	eeprom_setup.read_block = eeprom_read_block;
	eeprom_setup.write_block = eeprom_write_block;
	eeprom_setup.update_block = eeprom_update_block;
}

EEPROM* eeprom(void){ return &eeprom_setup; };

/*** EOF ***/

