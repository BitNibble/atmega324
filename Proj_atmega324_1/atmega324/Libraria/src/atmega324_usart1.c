/*************************************************************************
	ATMEGA 324 USART1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ATmega324
Update:   26/06/2025
*************************************************************************/
/*** Library ***/
#include "atmega324_usart1.h"
#include "buffer.h"
#include <avr/interrupt.h>
#include <string.h>

/*** Variable ***/
static USART1 usart1_setup;

static BUFF rx1buff;
static UARTvar UART1_Rx;

static UARTvar UART1_RxBuf[UART1_RX_BUFFER_SIZE] = {0};
static const uint16_t uart1_rx_buffer_size = (UART1_RX_BUFFER_SIZE - 1);
static uint8_t UART1_LastRxError;
static uint8_t uart1flag;

/*** Procedure & Function declaration ***/
UARTvar uart1_read(void);
UARTvar uart1_getch(void);
UARTvar* uart1_gets(void);
void uart1_rxflush(void);
void uart1_write(UARTvar data);
void uart1_putch(UARTvar c);
void uart1_puts(UARTvar* s);
/*** Complimentary function ***/
uint8_t USART1ReceiveComplete(void);
uint8_t USART1TransmitComplete(void);
uint8_t USART1DataRegisterEmpty(void);
uint8_t USART1FrameError(void);
uint8_t USART1DataOverRun(void);
uint8_t USART1ParityError(void);
uint8_t USART1ReadErrors(void);
void USART1ClearErrors(void);
void USART1DoubleTransmissionSpeed(void);

/*** Handler ***/
void usart1_enable( uint32_t baud, unsigned int FDbits, unsigned int Stopbits, unsigned int Parity )
{
	uart1flag = 1;
	uint16_t ubrr = 0;
	rx1buff = buff_enable( uart1_rx_buffer_size, UART1_RxBuf );
	ubrr = BAUDRATEnormal(baud);
	// V-table
	usart1_setup.read = uart1_read;
	usart1_setup.getch = uart1_getch;
	usart1_setup.gets = uart1_gets;
	usart1_setup.rxflush = uart1_rxflush;
	usart1_setup.write = uart1_write;
	usart1_setup.putch = uart1_putch;
	usart1_setup.puts = uart1_puts;
	// Set baud rate
	if ( ubrr & 0x8000 ) {
		USART1DoubleTransmissionSpeed(); // Enable 2x speed
		ubrr = BAUDRATEdouble(baud);
	}
	usart1_reg()->ubrr1->var = ubrr;
	// Enable USART receiver and transmitter and receive complete interrupt
	usart1_reg()->ucsr1b->var = (1 << RXCIE1) | (1 << RXEN1) | (1 << TXEN1);
	
	#ifdef URSEL1 // Set frame format: asynchronous, 8 data, no parity, 1 stop bit
		usart1_reg()->ucsr1c->var = (1 << UMSEL1) | (3 << UCSZ10);
	#else
		switch(FDbits){
			case 9:
				usart1_reg()->ucsr1b->var |= (1 << UCSZ12);
				usart1_reg()->ucsr1c->var |= (3 << UCSZ10);
			break;
			case 8:
				usart1_reg()->ucsr1b->var &= ~(1 << UCSZ12);
				usart1_reg()->ucsr1c->var |= (3 << UCSZ10);
			break;
			case 7:
				usart1_reg()->ucsr1b->var &= ~(1 << UCSZ12);
				usart1_reg()->ucsr1c->var |= (1 << UCSZ11);
				usart1_reg()->ucsr1c->var &= ~(1 << UCSZ10);
			break;
			case 6:
				usart1_reg()->ucsr1b->var &= ~(1 << UCSZ12);
				usart1_reg()->ucsr1c->var &= ~(1 << UCSZ11);
				usart1_reg()->ucsr1c->var |= (1 << UCSZ10);
			break;
			case 5:
				usart1_reg()->ucsr1b->var &= ~(1 << UCSZ12);
				usart1_reg()->ucsr1c->var &= ~(3 << UCSZ10);
			break;
			default:
				usart1_reg()->ucsr1b->var &= ~(1 << UCSZ12);
				usart1_reg()->ucsr1c->var |= (3 << UCSZ10);
			break;
		}
		switch(Stopbits){
			case 1:
				usart1_reg()->ucsr1c->var &= ~(1 << USBS1);
			break;
			case 2:
				usart1_reg()->ucsr1c->var |= (1 << USBS1);
			break;
			default:
				usart1_reg()->ucsr1c->var &= ~(1 << USBS1);
			break;
		}
		switch(Parity){
			case 0: // NONE
				usart1_reg()->ucsr1c->var &= ~(3 << UPM10);
			break;
			case 2: // EVEN
				usart1_reg()->ucsr1c->var |= (1 << UPM11);
				usart1_reg()->ucsr1c->var &= ~(1 << UPM10);
			break;
			case 3: // ODD
				usart1_reg()->ucsr1c->var |= (3 << UPM10);
			break;
			default:
				usart1_reg()->ucsr1c->var &= ~(3 << UPM10);
			break;
		}
	#endif
	cpu_reg()->sreg->par.i = 1;
}

USART1* usart1(void){ return &usart1_setup; }

/*** Procedure & Function definition ***/
UARTvar uart1_read(void)
{
	UARTvar c;
	c = UART1_Rx;
	UART1_Rx = 0;
	return c;
}
UARTvar uart1_getch(void)
{
	return uart1_read();
}
UARTvar* uart1_gets(void)
{
	return rx1buff.raw(&rx1buff.par);
}
void uart1_rxflush(void)
{
	rx1buff.flush(&rx1buff.par);
	UART1_LastRxError = 0;
}
void uart1_write(UARTvar data)
{
	uint16_t timeout;
	usart1_reg()->ucsr1b->var |= 1 << UDRIE1;
	usart1_reg()->udr1->var = data;
	for( timeout = 600; !USART1DataRegisterEmpty() && timeout; timeout-- ); // minimum -> +/- 450
	//for( ; !USART1DataRegisterEmpty(); ); // without timeout
}
void uart1_putch(UARTvar c)
{
	uart1_write(c);
}
void uart1_puts(UARTvar* s)
{
	char tmp;
	while(*s){
		tmp = *(s++);
		uart1_putch(tmp);
	}
}

/*** Interrupt ***/
SIGNAL(USART1_RX_vect)
{
	unsigned char bit9;
	unsigned char usr;
	
	usr  = USART1ReadErrors();
	bit9 = usart1_reg()->ucsr1b->var;
	bit9 = 0x01 & (bit9 >> 1);
 	   
	if(usr){ UART1_LastRxError = usr; }
	
	UART1_Rx = usart1_reg()->udr1->var;
	rx1buff.push(&rx1buff.par, UART1_Rx);
}

SIGNAL(USART1_UDRE_vect)
{
	usart1_reg()->ucsr1b->var &= ~(1 << UDRIE1);
}

/*** Complimentary function ***/
char* usart1_messageprint(USART1* uart, char* oneshot, char* msg, const char* endl)
{
	char* ptr;
	uint8_t length;
	uint8_t endlength = strlen(endl);
	if(uart1flag){ *oneshot = 0; uart1flag = 0; uart->rxflush();} // the matrix
	ptr = uart->gets();
	length = strlen(ptr);
	if(length >= endlength){
		if( !strcmp( ptr+(length-endlength), endl ) ){
			strcpy(oneshot, ptr); strcpy(msg, ptr); uart1flag = 0xFF;
		}
		// default
		//else if( !strcmp( ptr+(length-endlength), "\r" ) ){ strcpy(oneshot, ptr); strcpy(msg, ptr); uart1flag = 0xFF; }
		//else if( !strcmp( ptr+(length-endlength), "\n" ) ){ strcpy(oneshot, ptr); strcpy(msg, ptr); uart1flag = 0xFF; }
	}
	return ptr;
}

/*** Auxiliar ***/
uint8_t USART1ReceiveComplete(void)
{
	return (UCSR1A & (1 << RXC1));
}
uint8_t USART1TransmitComplete(void)
{
	return (UCSR1A & (1 << TXC1));
}
uint8_t USART1DataRegisterEmpty(void)
{
	return (UCSR1A & (1 << UDRE1));
}
uint8_t USART1FrameError(void)
{
	return (UCSR1A & (1 << FE1));
}
uint8_t USART1DataOverRun(void)
{
	return (UCSR1A & (1 << DOR1));
}
uint8_t USART1ParityError(void)
{
	return (UCSR1A & (1 << FE1));
}
uint8_t USART1ReadErrors(void)
{
	return get_reg_block(UCSR1A,3,2);
}
void USART1ClearErrors(void)
{
	set_reg_block(&UCSR1A,3,2,0);
}
void USART1DoubleTransmissionSpeed(void)
{
	set_reg_block(&UCSR1A,4,1,1);
}

/*** EOF ***/

