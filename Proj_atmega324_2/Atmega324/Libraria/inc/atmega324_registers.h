/************************************************************************
	ATMEGA 324 REGISTERS
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega324 by ETT ET-BASE
Date:     04/07/2025
************************************************************************/
#ifndef _ATMEGA324_REGISTERS_H_
	#define _ATMEGA324_REGISTERS_H_
	
/*** Compiler ***/
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*** Gloabl Library ***/
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

/*** Base Typedef ***/
typedef union {
	struct { 
		uint8_t bit0:1,bit1:1,bit2:1,bit3:1,bit4:1,bit5:1,bit6:1,bit7:1; 
	} par;
	uint8_t var;
} U_byte;

typedef union {
	struct{
		U_byte l, h;
	}par;
	uint16_t var;
} U_word;

/*****************************/
/****      REGISTERS      ****/
/*****************************/
// PINA 0x20 (U_byte)
// DDRA 0x21 (U_byte)
// PORTA 0x22 (U_byte)
// PINB 0x23 (U_byte)
// DDRB 0x24 (U_byte)
// PORTB 0x25 (U_byte)
// PINC 0x26 (U_byte)
// DDRC 0x27 (U_byte)
// PORTC 0x28 (U_byte)
// PIND 0x29 (U_byte)
// DDRD 0x2A (U_byte)
// PORTD 0x2B (U_byte)
// Reserved 0x2C
// Reserved 0x2D
// Reserved 0x2E
// Reserved 0x2F
// Reserved 0x30
// Reserved 0x31
// Reserved 0x32
// Reserved 0x33
// Reserved 0x34
typedef	volatile union {
	struct{
		uint8_t tov0 : 1, ocf0a : 1, ocf0b : 1, fill0 : 5;
	}par;
	uint8_t var;
} TIFR0_Typedef; // 0x35
typedef	volatile union {
	struct{
		uint8_t tov1 : 1, ocf1a : 1, ocf1b : 1, fill0 : 2, icf1 : 1, fill1 : 2;
	}par;
	uint8_t var;
} TIFR1_Typedef; // 0x36
typedef	volatile union {
	struct{
		uint8_t tov2 : 1, ocf2a : 1, ocf2b : 1, fill0 : 5;
	}par;
	uint8_t var;
} TIFR2_Typedef; // 0x37
typedef	volatile union {
	struct{
		uint8_t tov3 : 1, ocf3a : 1, ocf3b : 1, fill0 : 2, icf3 : 1, fill1 : 2;
	}par;
	uint8_t var;
} TIFR3_Typedef; // 0x38
// Reserved 0x39
// Reserved 0x3A
typedef union {
	struct{
		uint8_t pcif0 : 1, pcif1 : 1, pcif2 : 1, pcif3 : 1, fill0 : 4;
	}par;
	uint8_t var;
} PCIFR_TypeDef; // 0x3B
typedef union {
	struct{
		uint8_t intf0 : 1, intf1 : 1, intf2 : 1, fill0 : 5;
	}par;
	uint8_t var;
} EIFR_TypeDef; // 0x3C
typedef union {
	struct{
		uint8_t int0 : 1, int1 : 1, int2 : 1, fill0 : 5;
	}par;
	uint8_t var;
} EIMSK_TypeDef; // 0x3D
// _GPIOR0 0x3E (U_byte)
typedef union {
	struct{
		uint8_t eere : 1, eepe : 1, eempe : 1, eerie : 1, eepm0 : 1, eepm1 : 1, fill0 : 2;
	}par;
	uint8_t var;
} EECR_TypeDef; // 0x3F
// EEDR 0x40 (U_byte)
// EEARL EEARH 0x41 0x42 (U_word)
typedef union {
	struct{
		uint8_t psr5sync : 1, psrasy : 1, fill0 : 5, tsm : 1;
	}par;
	uint8_t var;
} GTCCR_TypeDef; // 0x43
typedef union {
	struct{
		uint8_t wgm00 : 1, wgm01 : 1, fill0 : 2, com0b0 : 1, com0b1 : 1, com0a0 : 1, com0a1 : 1;
	}par;
	uint8_t var;
} TCCR0A_TypeDef; // 0x44
typedef union {
	struct{
		uint8_t cs00 : 1, cs01 : 1, cs02 : 1, wgm02 : 1, fill0 : 2, foc0b : 1, foc0a : 1;
	}par;
	uint8_t var;
} TCCR0B_TypeDef; // 0x45
// TCNT0 0x46 (U_byte)
// OCR0A 0x47 (U_byte)
// OCR0B 0x48 (U_byte)
// Reserved 0x49
// GPIOR1 0x4A (U_byte)
// GPIOR2 0x4B (U_byte)
typedef union {
	struct{
		uint8_t spr00 : 1, spr01 : 1, cpha0 : 1, cpol0 : 1, mstr0 : 1, dord0 : 1, spe0 : 1, spie0 : 1;
	}par;
	uint8_t var;
} SPCR_TypeDef; // 0x4C
typedef union {
	struct{
		uint8_t spi2x0 : 1, fill0 : 5, wcol0 : 1, spif0 : 1;
	}par;
	uint8_t var;
} SPSR_TypeDef; // 0x4D
// SPDR 0x4E (U_byte)
// Reserved 0x4F
typedef union {
	struct{
		uint8_t acis0 : 1, acis1 : 1, acic : 1, acie : 1, aci : 1, aco : 1, acbg : 1, acd : 1;
	}par;
	uint8_t var;
} ACSR_TypeDef; // 0x50
// OCDR 0x51 (U_byte)
// Reserved 0x52
typedef union {
	struct{
		uint8_t se : 1, sm0 : 1, sm1 : 1, sm2 : 1, fill0 : 4;
	}par;
	uint8_t var;
} SMCR_TypeDef; // 0x53
typedef union {
	struct{
		uint8_t porf : 1, extrf : 1, borf : 1, wdrf : 1, jtrf : 1, fill0 : 3;
	}par;
	uint8_t var;
} MCUSR_TypeDef; // 0x54
typedef union {
	struct{
		uint8_t ivce : 1, ivsel : 1, fill0 : 2, pud : 1, bodse : 1, bods : 1, jtd : 1;
	}par;
	uint8_t var;
} MCUCR_TypeDef; // 0x55
// Reserved 0x56
typedef union {
	struct{
		uint8_t spmen : 1, pgers : 1, pgwrt : 1, blbset : 1, rwwsre : 1, sigrd : 1, rwwsb : 1, spmie : 1;
	}par;
	uint8_t var;
} SPMCSR_TypeDef; // 0x57
// Reserved 0x58
// Reserved 0x59
// Reserved 0x5A
typedef union {
	struct{
		uint8_t rampz0 : 1, fill0 : 7;
	}par;
	uint8_t var;
} RAMPZ_TypeDef; // 0x5B
// Reserved 0x5C
// SPL SPH 0x5D 0x5E (U_word)
typedef union {
	struct{
		uint8_t c : 1, z : 1, n : 1, v : 1, s : 1, h : 1, t : 1, i : 1;
	}par;
	uint8_t var;
} SREG_TypeDef; // 0x5F
typedef union {
	struct{
		uint8_t wdp0 : 1, wdp1 : 1, wdp2 : 1, wde : 1, wdce : 1, wdp3 : 1, wdie : 1, wdif : 1;
	}par;
	uint8_t var;
} WDTCSR_TypeDef; // 0x60
typedef union {
	struct{
		uint8_t clkps0 : 1, clkps1 : 1, clkps2 : 1, clkps3 : 1, fill0 : 3, clkpce : 1;
	}par;
	uint8_t var;
} CLKPR_TypeDef; // 0x61
// Reserved 0x62
// Reserved 0x63
typedef union {
	struct{
		uint8_t pradc : 1, prusart0 : 1, prspi : 1, prtim1 : 1, prusart1 : 1, prtim0 : 1, prtim2 : 1, prtwi : 1;
	}par;
	uint8_t var;
} PRR_TypeDef; // 0x64
// Reserved 0x65
// OSCAL 0x66 (U_byte)
// Reserved 0x67
typedef union {
	struct{
		uint8_t pcie0 : 1, pcie1 : 1, pcie2 : 1, pcie3 : 1, fill0 : 4;
	}par;
	uint8_t var;
} PCICR_TypeDef; // 0x68
typedef union {
	struct{
		uint8_t isc00 : 1, isc01 : 1, isc10 : 1, isc11 : 1, isc20 : 1, isc21 : 1, fill0 : 2;
	}par;
	uint8_t var;
} EICRA_TypeDef; // 0x69
// Reserved 0x6A
typedef union {
	struct{
		uint8_t pcint0 : 1, pcint1 : 1, pcint2 : 1, pcint3 : 1, pcint4 : 1, pcint5 : 1, pcint6 : 1, pcint7 : 1;
	}par;
	uint8_t var;
} PCMSK0_TypeDef; // 0x6B
typedef union {
	struct{
		uint8_t pcint8 : 1, pcint9 : 1, pcint10 : 1, pcint11 : 1, pcint12 : 1, pcint13 : 1, pcint14 : 1, pcint15 : 1;
	}par;
	uint8_t var;
} PCMSK1_TypeDef; // 0x6C
typedef union {
	struct{
		uint8_t pcint16 : 1, pcint17 : 1, pcint18 : 1, pcint19 : 1, pcint20 : 1, pcint21 : 1, pcint22 : 1, pcint23 : 1;
	}par;
	uint8_t var;
} PCMSK2_TypeDef; // 0x6D
typedef union {
	struct{
		uint8_t toie0 : 1, ocie0a : 1, ocie0b : 1, fill0 : 5;
	}par;
	uint8_t var;
} TIMSK0_TypeDef; // 0x6E
typedef union {
	struct{
		uint8_t toie1 : 1, ocie1a : 1, ocie1b : 1, fill0 : 2, icie1 : 1, fill1 : 2;
	}par;
	uint8_t var;
} TIMSK1_TypeDef; // 0x6F
typedef union {
	struct{
		uint8_t toie2 : 1, ocie2a : 1, ocie2b : 1, fill0 : 5;
	}par;
	uint8_t var;
} TIMSK2_TypeDef; // 0x70
typedef union {
	struct{
		uint8_t toie3 : 1, ocie3a : 1, ocie3b : 1, fill0 : 2, icie3 : 1, fill1 : 2;
	}par;
	uint8_t var;
} TIMSK3_TypeDef; // 0x71
// Reserved 0x72
typedef union {
	struct{
		uint8_t pcint24 : 1, pcint25 : 1, pcint26 : 1, pcint27 : 1, pcint28 : 1, pcint29 : 1, pcint30 : 1, pcint31 : 1;
	}par;
	uint8_t var;
} PCMSK3_TypeDef; // 0x73
// Reserved 0x74
// Reserved 0x75
// Reserved 0x76
// Reserved 0x77
// ADCL ADCH 0x78 0x79 (U_word)
typedef union {
	struct{
		uint8_t adps0 : 1, adps1 : 1, adps2 : 1, adie : 1, adif : 1, adate : 1, adsc : 1, aden : 1;
	}par;
	uint8_t var;
} ADCSRA_TypeDef; // 0x7A
typedef union {
	struct{
		uint8_t adts0 : 1, adts1 : 1, adts2 : 1, fill0 : 3, acme : 1, fill1 : 1;
	}par;
	uint8_t var;
} ADCSRB_TypeDef; // 0x7B
typedef union {
	struct{
		uint8_t mux0 : 1, mux1 : 1, mux2 : 1, mux3 : 1, mux4 : 1, adlar : 1, refs0 : 1, refs1 : 1;
	}par;
	uint8_t var;
} ADMUX_TypeDef; // 0x7C
// Reserved 0x7D
typedef union {
	struct{
		uint8_t adc0d : 1, adc1d : 1, adc2d : 1, adc3d : 1, adc4d : 1, adc5d : 1, adc6d : 1, adc7d : 1;
	}par;
	uint8_t var;
} DIDR0_TypeDef; // 0x7E
typedef union {
	struct{
		uint8_t ain0d : 1, ain1d : 1, fill0 : 6;
	}par;
	uint8_t var;
} DIDR1_TypeDef; // 0x7F
typedef union {
	struct{
		uint8_t wgm10 : 1, wgm11 : 1, fill0 : 2, com1b0 : 1, com1b1 : 1, com1a0 : 1, com1a1 : 1;
	}par;
	uint8_t var;
} TCCR1A_TypeDef; // 0x80
typedef union {
	struct{
		uint8_t cs10 : 1, cs11 : 1, cs12 : 1, wgm12 : 1, wgm13 : 1, fill0 : 1, ices1 : 1, icnc1 : 1;
	}par;
	uint8_t var;
} TCCR1B_TypeDef; // 0x81
typedef union {
	struct{
		uint8_t fill0 : 6, foc1b : 1, foc1a : 1;
	}par;
	uint8_t var;
} TCCR1C_TypeDef; // 0x82
// Reserved 0x83
// TCNT1L TCNT1H 0x84 0x85 (U_word)
// ICR1L ICR1H 0x86 0x87 (U_word)
// OCR1AL OCR1AH 0x88 0x89 (U_word)
// OCR1BL OCR1BH 0x8A 0x8B (U_word)
// Reserved 0x8C
// Reserved 0x8D
// Reserved 0x8E
// Reserved 0x8F
typedef union {
	struct{
		uint8_t wgm30 : 1, wgm31 : 1, fill0 : 2, com3b0 : 1, com3b1 : 1, com3a0 : 1, com3a1 : 1;
	}par;
	uint8_t var;
} TCCR3A_TypeDef; // 0x90
typedef union {
	struct{
		uint8_t cs30 : 1, cs31 : 1, cs32 : 1, wgm32 : 1, wgm33 : 1, fill0 : 1, ices3 : 1, icnc3 : 1;
	}par;
	uint8_t var;
} TCCR3B_TypeDef; // 0x91
typedef union {
	struct{
		uint8_t fill0 : 6, foc3b : 1, foc3a : 1;
	}par;
	uint8_t var;
} TCCR3C_TypeDef; // 0x92
// Reserved 0x93
// TCNT3L TCNT3H 0x94 0x95 (U_word)
// ICR3L ICR3H 0x96 0x97 (U_word)
// OCR3AL OCR3AH 0x98 0x99 (U_word)
// OCR3BL OCR3BH 0x9A 0x9B (U_word)
// Reserved 0x9C
// Reserved 0x9D
// Reserved 0x9E
// Reserved 0x9F
// Reserved 0xA0
// Reserved 0xA1
// Reserved 0xA2
// Reserved 0xA3
// Reserved 0xA4
// Reserved 0xA5
// Reserved 0xA6
// Reserved 0xA7
// Reserved 0xA8
// Reserved 0xA9
// Reserved 0xAA
// Reserved 0xAB
// Reserved 0xAC
// Reserved 0xAD
// Reserved 0xAE
// Reserved 0xAF
typedef union {
	struct{
		uint8_t wgm20 : 1, wgm21 : 1, fill0 : 2, com2b0 : 1, com2b1 : 1, com2a0 : 1, com2a1 : 1;
	}par;
	uint8_t var;
} TCCR2A_TypeDef; // 0xB0
typedef union {
	struct{
		uint8_t cs20 : 1, cs21 : 1, cs22 : 1, wgm22 : 1, fill0 : 2, foc2b : 1, foc2a : 1;
	}par;
	uint8_t var;
} TCCR2B_TypeDef; // 0xB1
// TCNT2 0xB2 (U_byte)
// OCR2A 0xB3 (U_byte)
// OCR2B 0xB4 (U_byte)
// Reserved 0xB5
typedef union {
	struct{
		uint8_t tcr2bub : 1, tcr2aub : 1, ocr2bub : 1, ocr2aub : 1, tcn2ub : 1, as2 : 1, exclk : 1, fill0 : 1;
	}par;
	uint8_t var;
} ASSR_TypeDef; // 0xB6
// Reserved 0xB7
// TWBR 0xB8 (U_byte)
typedef union {
	struct{
		uint8_t twps : 2, fill0 : 1, tws3 : 1, tws4 : 1, tws5 : 1, tws6 : 1, tws7 : 1;
	}par;
	uint8_t var;
} TWSR_TypeDef; // 0xB9
typedef union {
	struct{
		uint8_t twgce : 1, twa : 7;
	}par;
	uint8_t var;
} TWAR_TypeDef; // 0xBA
// TWDR 0xBB (U_byte)
typedef union {
	struct{
		uint8_t twie : 1, fill0 : 1, twen : 1, twwc : 1, twsto : 1, twsta : 1, twea : 1, twint : 1;
	}par;
	uint8_t var;
} TWCR_TypeDef; // 0xBC
typedef union {
	struct{
		uint8_t fill0 : 1, twam0 : 1, twam1 : 1, twam2 : 1, twam3 : 1, twam4 : 1, twam5 : 1, twam6 : 1;
	}par;
	uint8_t var;
} TWAMR_TypeDef; // 0xBD
// Reserved 0xBE
// Reserved 0xBF
typedef union {
	struct{
		uint8_t mpcm0 : 1, u2x0 : 1, upe0 : 1, dor0 : 1, fe0 : 1, udre0 : 1, txc0 : 1, rxc0 : 1;
	}par;
	uint8_t var;
} UCSR0A_TypeDef; // 0xC0
typedef union {
	struct{
		uint8_t txb80 : 1, rxb80 : 1, ucsz02 : 1, txen0 : 1, rxen0 : 1, udrie0 : 1, txcie0 : 1, rxcie0 : 1;
	}par;
	uint8_t var;
} UCSR0B_TypeDef; // 0xC1
typedef union {
	struct{
		uint8_t ucpol0 : 1, ucpha0 : 1, udord0 : 1, fill0 : 3, umsel00 : 1, umsel01 : 1;
	}par;
	uint8_t var;
} UCSR0C_TypeDef; // 0xC2
// Reserved 0xC3
// UBRR0L UBRR0H 0xC4 0xC5 (U_word)
// UDR0 0xC6 (U_byte)
// Reserved 0xC7
typedef union {
	struct{
		uint8_t mpcm1 : 1, u2x1 : 1, upe1 : 1, dor1 : 1, fe1 : 1, udre1 : 1, txc1 : 1, rxc1 : 1;
	}par;
	uint8_t var;
} UCSR1A_TypeDef; // 0xC8
typedef union {
	struct{
		uint8_t txb81 : 1, rxb81 : 1, ucsz12 : 1, txen1 : 1, rxen1 : 1, udrie1 : 1, txcie1 : 1, rxcie1 : 1;
	}par;
	uint8_t var;
} UCSR1B_TypeDef; // 0xC9
typedef union {
	struct{
		uint8_t ucpol1 : 1, ucpha1 : 1, udord1 : 1, fill0 : 3, umsel10 : 1, umsel11 : 1;
	}par;
	uint8_t var;
} UCSR1C_TypeDef; // 0xCA
// Reserved 0xCB
// UBRR1L UBRR1H 0xCC 0xCD (U_word)
// UDR1 0xCE (U_byte)
// Reserved 0xCF
// Reserved 0xD0
// Reserved 0xD1
// Reserved 0xD2
// Reserved 0xD3
// Reserved 0xD4
// Reserved 0xD5
// Reserved 0xD6
// Reserved 0xD7
// Reserved 0xD8
// Reserved 0xD9
// Reserved 0xDA
// Reserved 0xDB
// Reserved 0xDC
// Reserved 0xDD
// Reserved 0xDE
// Reserved 0xDF
// Reserved 0xE0
// Reserved 0xE1
// Reserved 0xE2
// Reserved 0xE3
// Reserved 0xE4
// Reserved 0xE5
// Reserved 0xE6
// Reserved 0xE7
// Reserved 0xE8
// Reserved 0xE9
// Reserved 0xEA
// Reserved 0xEB
// Reserved 0xEC
// Reserved 0xED
// Reserved 0xEE
// Reserved 0xEF
// Reserved 0xF0
// Reserved 0xF1
// Reserved 0xF2
// Reserved 0xF3
// Reserved 0xF4
// Reserved 0xF5
// Reserved 0xF6
// Reserved 0xF7
// Reserved 0xF8
// Reserved 0xF9
// Reserved 0xFA
// Reserved 0xFB
// Reserved 0xFC
// Reserved 0xFD
// Reserved 0xFE
// Reserved 0xFF

#endif
/*** EOF ***/

