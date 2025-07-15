/***********************************************************************
	ATMEGA 324
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega324 by ETT ET-BASE
Date:     04/07/2025
***********************************************************************/
#ifndef _ATMEGA324_H_
	#define _ATMEGA324_H_

/*** Compiler ***/
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*** Working Frequency ***/
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

/*** Library ***/
#include <avr/io.h>
#include <avr/boot.h>
#include <avr/fuse.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "atmega324_registers.h"

/*** Constant & Macro ***/
#define TWO 2
#define NIBBLE_BITS 4
#define BYTE_BITS 8
#define WORD_BITS 16
#define DWORD_BITS 32
#define QWORD_BITS 64
#define SRAMSTART 0x0100
#define SRAMEND 0x08FF
// Macros for common operations
#define SET_REG(REG, HBITS)		(REG |= HBITS)
#define CLEAR_REG(REG, HBITS)	(REG &= ~HBITS)
#define READ_BIT(REG, BIT)		((REG >> BIT) & 1)
#define TOGGLE_REG(REG, HBITS)	(REG ^= HBITS)

/*****************************/
/**** MAIN HARDWARE LAYER ****/
/*****************************/
// GPWR
typedef volatile struct {
	uint8_t r0; // 0x0000
	uint8_t r1; // 0x0001
	uint8_t r2; // 0x0002
	uint8_t r3; // 0x0003
	uint8_t r4; // 0x0004
	uint8_t r5; // 0x0005
	uint8_t r6; // 0x0006
	uint8_t r7; // 0x0007
	uint8_t r8; // 0x0008
	uint8_t r9; // 0x0009
	uint8_t r10; // 0x000A
	uint8_t r11; // 0x000B
	uint8_t r12; // 0x000C
	uint8_t r13; // 0x000D
	uint8_t r14; // 0x000E
	uint8_t r15; // 0x000F
	uint8_t r16; // 0x0010
	uint8_t r17; // 0x0011
	uint8_t r18; // 0x0012
	uint8_t r19; // 0x0013
	uint8_t r20; // 0x0014
	uint8_t r21; // 0x0015
	uint8_t r22; // 0x0016
	uint8_t r23; // 0x0017
	uint8_t r24; // 0x0018
	uint8_t r25; // 0x0019
	uint16_t x; // 0x001A 0x001B
	uint16_t y; // 0x001C 0x001D
	uint16_t z; // 0x001E 0x001F
} GPW_TypeDef;

// Analog Comparator (AC)
typedef volatile struct {
	ACSR_TypeDef* acsr; // 0x0050
	ADCSRB_TypeDef* adcsrb; // 0x007B
	DIDR1_TypeDef* didr1; // 0x007F
} Atmega324AnalogComparator_TypeDef;

Atmega324AnalogComparator_TypeDef* ac_reg(void);

// Analog to Digital Converter (ADC)
typedef volatile struct {
	U_word* adc; // 0x0078 0x0079
	ADCSRA_TypeDef* adcsra; // 0x007A
	ADCSRB_TypeDef* adcsrb; // 0c007B
	ADMUX_TypeDef* admux; // 0x007C
	DIDR0_TypeDef* didr0; // 0x007E
} Atmega324AnalogToDigitalConverter_TypeDef;

Atmega324AnalogToDigitalConverter_TypeDef* adc_reg(void);

// Boot loader (BOOT_LOAD)
typedef volatile struct {
	SPMCSR_TypeDef* spmcsr; // 0x0057
} Atmega324BootLoader_TypeDef;

Atmega324BootLoader_TypeDef* boot_reg(void);

// CPU Register (CPU)
typedef volatile struct {
	U_byte* gpior0; // 0x003E
	U_byte* gpior1; // 0x004A
	U_byte* gpior2; // 0x004B
	SMCR_TypeDef* smcr; // 0x0053
	MCUSR_TypeDef* mcusr; // 0x0054
	MCUCR_TypeDef* mcucr; // 0x0055
	U_word* sp; // 0x005D 0x005E
	SREG_TypeDef* sreg; // 0x005F
	CLKPR_TypeDef* clkpr; // 0x0061
	PRR_TypeDef* prr0; // 0x0064
	U_byte* osccal; // 0x0066
} Atmega324CPURegister_TypeDef;

Atmega324CPURegister_TypeDef* cpu_reg(void);

// EEPROM (EEPROM)
typedef volatile struct {
	EECR_TypeDef* eecr; // 0x003F
	U_byte* eedr; // 0x0040
	U_word* eear; // 0x0041 0x0042
} Atmega324Eeprom_TypeDef;

Atmega324Eeprom_TypeDef* eeprom_reg(void);

// External Interrupts (EXINT)
typedef volatile struct {
	PCIFR_TypeDef* pcifr; // 0x003B
	EIFR_TypeDef* eifr; // 0x003C
	EIMSK_TypeDef* eimsk; // 0x003D
	PCICR_TypeDef* pcicr; // 0x0068
	EICRA_TypeDef* eicra; // 0x0069
	PCMSK0_TypeDef* pcmsk0; // 0x006B
	PCMSK1_TypeDef* pcmsk1; // 0x006C
	PCMSK2_TypeDef* pcmsk2; // 0x006D
	PCMSK3_TypeDef* pcmsk3; // 0x0073
} Atmega324ExternalInterrupts_TypeDef;

Atmega324ExternalInterrupts_TypeDef* exint_reg(void);

// I/O Port (PORTA)
typedef volatile struct {
	U_byte* pin; // 0x0020
	U_byte* ddr; // 0x0021
	U_byte* port; // 0x0022
} GPIOA_TypeDef;

GPIOA_TypeDef* gpioa_reg(void);

// I/O Port (PORTB)
typedef volatile struct {
	U_byte* pin; // 0x0023
	U_byte* ddr; // 0x0024
	U_byte* port; // 0x0025
} GPIOB_TypeDef;

GPIOB_TypeDef* gpiob_reg(void);

// I/O Port (PORTC)
typedef volatile struct {
	U_byte* pin; // 0x0026
	U_byte* ddr; // 0x0027
	U_byte* port; // 0x0028
} GPIOC_TypeDef;

GPIOC_TypeDef* gpioc_reg(void);

// I/O Port (PORTD)
typedef volatile struct {
	U_byte* pin; // 0x0029
	U_byte* ddr; // 0x002A
	U_byte* port; // 0x002B
} GPIOD_TypeDef;

GPIOD_TypeDef* gpiod_reg(void);

// JTAG Interface (JTAG)
typedef volatile struct {
	U_byte* ocdr; // 0x0051
	MCUSR_TypeDef* mcusr; // 0x0054
	MCUCR_TypeDef* mcucr; // 0x0055
} Atmega324JtagInterface_TypeDef;

Atmega324JtagInterface_TypeDef* jtag_reg(void);

// Serial Peripheral Interface (SPI)
typedef volatile struct {
	SPCR_TypeDef* spcr0; // 0x004C
	SPSR_TypeDef* spsr0; // 0x004D
	U_byte* spdr0; // 0x004E
} Atmega324SerialPeripherialInterface_TypeDef;

Atmega324SerialPeripherialInterface_TypeDef* spi_reg(void);

// Timer/Counter, 16-bit (TC1)
typedef volatile struct {
	TIFR1_TypeDef* tifr1; // 0x0036
	TIMSK1_TypeDef* timsk1; // 0x006F
	TCCR1A_TypeDef* tccr1a; // 0x0080
	TCCR1B_TypeDef* tccr1b; // 0x0081
	TCCR1C_TypeDef* tccr1c; // 0x0082
	U_word* tcnt1; // 0x0084 0x0085
	U_word* icr1; // 0x0086 0x0087
	U_word* ocr1a; // 0x0088 0x0089
	U_word* ocr1b; // 0x008A 0x008B
} Atmega324TimerCounter1_TypeDef;

Atmega324TimerCounter1_TypeDef* tc1_reg(void);

// Timer/Counter, 16-bit (TC3)
typedef volatile struct {
	TIFR3_TypeDef* tifr3; // 0x0036
	TIMSK3_TypeDef* timsk3; // 0x006F
	TCCR3A_TypeDef* tccr3a; // 0x0080
	TCCR3B_TypeDef* tccr3b; // 0x0081
	TCCR3C_TypeDef* tccr3c; // 0x0082
	U_word* tcnt3; // 0x0084 0x0085
	U_word* icr3; // 0x0086 0x0087
	U_word* ocr3a; // 0x0088 0x0089
	U_word* ocr3b; // 0x008A 0x008B
} Atmega324TimerCounter3_TypeDef;

Atmega324TimerCounter3_TypeDef* tc3_reg(void);

// Timer/Counter, 8-bit (TC0)
typedef volatile struct {
	TIFR0_TypeDef* tifr0; // 0x0035
	TCCR0A_TypeDef* tccr0a; // 0x0044
	TCCR0B_TypeDef* tccr0b; // 0x0045
	U_byte* tcnt0; // 0x0046
	U_byte* ocr0a; // 0x0047
	U_byte* ocr0b; // 0x0048
	TIMSK0_TypeDef* timsk0; // 0x006E	
} Atmega324TimerCounter0_TypeDef;

Atmega324TimerCounter0_TypeDef* tc0_reg(void);

// Timer/Counter, 8-bit Async (TC2)
typedef volatile struct {
	TIFR2_TypeDef* tifr2; // 0x0037
	GTCCR_TypeDef* gtccr; // 0x0043
	TIMSK2_TypeDef* timsk2; // 0x0070
	TCCR2A_TypeDef* tccr2a; // 0x00B0
	TCCR2B_TypeDef* tccr2b; // 0x00B1
	U_byte* tcnt2; // 0x00B2
	U_byte* ocr2a; // 0x00B3
	U_byte* ocr2b; // 0x00B4
	ASSR_TypeDef* assr; // 0x00B6
} Atmega324TimerCounter2_TypeDef;

Atmega324TimerCounter2_TypeDef* tc2_reg(void);

// Two Wire Serial Interface (TWI)
typedef volatile struct {
	U_byte* twbr; // 0x00B8
	TWSR_TypeDef* twsr; // 0x00B9
	TWAR_TypeDef* twar; // 0x00BA
	U_byte* twdr; // 0x00BB
	TWCR_TypeDef* twcr; // 0x00BC
	TWAMR_TypeDef* twamr; // 0x00BD
} Atmega324TwoWireSerialInterface_TypeDef;

Atmega324TwoWireSerialInterface_TypeDef* twi_reg(void);

// USART (USART0)
typedef volatile struct {
	UCSR0A_TypeDef* ucsr0a; // 0x00C0
	UCSR0B_TypeDef* ucsr0b; // 0x00C1
	UCSR0C_TypeDef* ucsr0c; // 0x00C2
	U_word* ubrr0; // 0x00C4–0x00C5 (UBRR0H: 0x00C4, UBRR0L: 0x00C5)
	U_byte* udr0; // 0x00C6
} Atmega324Usart0_TypeDef;

Atmega324Usart0_TypeDef* usart0_reg(void);

// USART (USART1)
typedef volatile struct {
	UCSR1A_TypeDef* ucsr1a; // 0x00C8
	UCSR1B_TypeDef* ucsr1b; // 0x00C9
	UCSR1C_TypeDef* ucsr1c; // 0x00CA
	U_word* ubrr1; // 0x00CC–0x00CD (UBRR1H: 0x00CC, UBRR1L: 0x00CD)
	U_byte* udr1; // 0x00CE
} Atmega324Usart1_TypeDef;

Atmega324Usart1_TypeDef* usart1_reg(void);

// Watchdog Timer (WDT)
typedef volatile struct {
	WDTCSR_TypeDef* wdtcsr; // 0x0060
} Atmega324WatchdogTimer_TypeDef;

Atmega324WatchdogTimer_TypeDef* wdt_reg(void);

/*********************************************************************/
/*************** Procedure and Function declaration ******************/
/*********************************************************************/
uint16_t swapbyte(uint16_t num);
uint16_t BAUDRATEnormal(uint32_t BAUD);
uint16_t BAUDRATEdouble(uint32_t BAUD);
uint16_t BAUDRATEsynchronous(uint32_t BAUD);

/*** Procedure and Function ToolSet ***/
void set_reg(volatile uint8_t* reg, uint8_t hbits);
void clear_reg(volatile uint8_t* reg, uint8_t hbits);
uint8_t get_reg_block(uint8_t reg, uint8_t size_block, uint8_t bit_n);
void write_reg_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n, uint8_t data);
void set_reg_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n, uint8_t data);
uint8_t get_bit_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n);
void set_bit_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n, uint8_t data);

#endif
/*** EOF ***/

