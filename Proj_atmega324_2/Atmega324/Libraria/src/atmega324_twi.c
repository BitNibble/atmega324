/***************************************************************************************************
	ATMEGA 324 TWI
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ATmega324A
Update:   30062025
***************************************************************************************************/
/*** File Library ***/
#include "atmega324_twi.h"
#include <util/delay.h>

/*** File Variable ***/
static TWI0 twi_setup;

/*** Procedure & Function declaration***/
void TWI_init(uint8_t device_id, uint8_t prescaler);
void TWI_start(void);
void TWI_connect(uint8_t address, uint8_t rw);
void TWI_master_write(uint8_t var_twiData_u8);
uint8_t TWI_master_read(uint8_t ack_nack);
void TWI_stop(void);
// auxiliary
uint8_t TWI_status(void);
void TWI_wait_twint( uint16_t nticks );

/*** Handler ***/
void twi_enable(uint8_t atmega_ID,  uint8_t prescaler)
{
	// V-table
	twi_setup.start = TWI_start;
	twi_setup.connect = TWI_connect;
	twi_setup.stop = TWI_stop;
	twi_setup.master_write = TWI_master_write;
	twi_setup.master_read = TWI_master_read;
	twi_setup.status = TWI_status;
	
	TWI_init(atmega_ID, prescaler);
}

TWI0* twi(void){ return &twi_setup; }

/*** Procedure & Function definition ***/
// void TWI_Init(uint8_t device_id, uint8_t prescaler)
void TWI_init(uint8_t device_id, uint8_t prescaler)
{
	if(device_id > 0 && device_id < 128){
		twi_reg()->twar->par.twa = device_id;
		twi_reg()->twar->par.twgce = 1;
	}else{
		twi_reg()->twar->par.twgce = 1;
	}
	gpioc_reg()->ddr->var |= TWI_IO_MASK;
	gpioc_reg()->port->var |= TWI_IO_MASK;
	switch(prescaler){
		case 1:
			twi_reg()->twsr->par.twps = 0;
		break;
		case 4:
			twi_reg()->twsr->par.twps = 1;
		break;
		case 16:
			twi_reg()->twsr->par.twps = 2;
		break;
		case 64:
			twi_reg()->twsr->par.twps = 3;
		break;
		default:
			prescaler = 1;
			twi_reg()->twsr->par.twps = 0;
		break;
	}
	twi_reg()->twbr->var = ((F_CPU / TWI_SCL_CLOCK) - 16) / (2 * prescaler);
	// Standard Config begin
	// twi_reg()->twsr->var = 0x00; //set presca1er bits to zero
	// twi_reg()->twbr = 0x46; //SCL frequency is 50K for 16Mhz
	// twi_reg()->twcr = 0x04; //enab1e TWI module
	// Standard Config end
}
// void TWI_Start(void)
void TWI_start(void) // $08
{	
	uint8_t cmd = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	twi_reg()->twcr->var = cmd;
	
	TWI_wait_twint( Nticks );
	
	switch( TWI_status( ) ){
		case TW_START:
			// Do nothing
		break;
		default:
			TWI_stop( ); // error
		break;
	}
}
// void TWI_Connect(uint8_t address, uint8_t rw)
void TWI_connect( uint8_t address, uint8_t rw )
{
	uint8_t cmd = 0;
	if( rw ){ cmd = (address << 1) | (1 << 0); }
	else{ cmd = (address << 1) | (0 << 0); }
	twi_reg()->twdr->var = cmd;
	
	cmd = (1 << TWINT) | (1 << TWEN);
	twi_reg()->twcr->var = cmd;
	
	TWI_wait_twint( Nticks );
	
	switch( TWI_status( ) ){
		case TW_MT_SLA_ACK:
			// Do nothing
		break;
		case TW_MR_SLA_ACK:
			// Do nothing
		break;
		default:
			TWI_stop( ); // error
		break;
	}
}
// void TWI_Write(uint8_t var_twiData_u8)
void TWI_master_write( uint8_t var_twiData_u8 )
{
	uint8_t cmd = var_twiData_u8;
	twi_reg()->twdr->var = cmd;
	
	cmd = (1 << TWINT) | (1 << TWEN);
	twi_reg()->twcr->var = cmd;
	
	TWI_wait_twint( Nticks );
	
	switch( TWI_status( ) ){
		case TW_MR_DATA_ACK:
			// Do nothing
		break;
		default:
			TWI_stop( ); // error
		break;
	}
}
// uint8_t TWI_Read(uint8_t ack_nack)
uint8_t TWI_master_read( uint8_t ack_nack )
{
	uint8_t cmd = 0x00;
	if( ack_nack ){ cmd |= ( 1 << TWEA ); }
	cmd |= ( 1 << TWINT ) | ( 1 << TWEN );
	twi_reg()->twcr->var = cmd;
	
	TWI_wait_twint( Nticks );
	
	switch( TWI_status( ) ){
		case TWI_ARBLSLARNACK:
			TWI_stop( );
		break;
		default:
		break;
	}
	
	cmd = twi_reg()->twdr->var;
	return cmd;
}
// void TWI_Stop(void)
void TWI_stop( void )
{
	uint8_t cmd = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	twi_reg()->twcr->var = cmd; 
	
	_delay_us(100); // wait for a short time
}
// auxiliary
uint8_t TWI_status( void )
{
	uint8_t cmd = twi_reg()->twsr->var & TW_NO_INFO;
	return cmd;
}
void TWI_wait_twint( uint16_t nticks ) // hardware triggered
{
	unsigned int i; // wait for acknowledgment confirmation bit.
	for(i = 0; !( twi_reg()->twcr->var & (1 << TWINT)); i++ ){ 
		if( i > nticks ) // timeout
			break;
	}
}

/*** EOF ***/

