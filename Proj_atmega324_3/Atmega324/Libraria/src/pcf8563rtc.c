/***************************************************************************************************
	PCF8563RTC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: PCF8563
Date:     29112022
 **************************************************************************************************/
/*** Library ***/
#include "pcf8563rtc.h"
#if defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__)
	#include "atmega128mapping.h"
	TWI i2c;
#elif defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
	#include "atmega328mapping.h"
	TWI i2c;
#elif defined(__AVR_ATmega324A__)
	#include "atmega324_twi.h"
	TWI0 i2c;
#else
	#error "MCU Lib not available"
#endif

/*** Procedure and Funtion declaration ***/
void PCF8563RTC_Init(void);
void PCF8563RTC_SetTime(uint8_t var_hour_u8, uint8_t var_min_u8, uint8_t var_sec_u8);
void PCF8563RTC_SetHour(uint8_t var_hour_u8);
void PCF8563RTC_SetMinute(uint8_t var_min_u8);
void PCF8563RTC_SetSecond(uint8_t var_sec_u8);
void PCF8563RTC_SetClkOut(uint8_t onoff, uint8_t freq);
void PCF8563RTC_SetDate(uint8_t var_day_u8, uint8_t var_weekday_u8, uint8_t var_month_u8, uint8_t var_year_u8);
void PCF8563RTC_SetDay(uint8_t var_day_u8);
void PCF8563RTC_SetWeekday(uint8_t var_weekday_u8);
void PCF8563RTC_SetMonth(uint8_t var_month_u8);
void PCF8563RTC_SetYear(uint8_t var_year_u8);
struct time PCF8563RTC_GetTime(void);
struct date PCF8563RTC_GetDate(void);
uint8_t PCF8563RTC_bcd2dec(uint8_t num);
uint8_t PCF8563RTC_bintobcd(uint8_t bin);

/*** Handler ***/
PCF8563RTC pcf8563rtc_enable(uint8_t prescaler)
{
	PCF8563RTC pcf_setup;
	#if defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__)
		i2c = TWI_enable('A', prescaler);
	#elif defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
		i2c = TWI_enable('A', prescaler);
	#elif defined(__AVR_ATmega324A__)
		twi_enable('A', prescaler);
	#endif
	// V-table
	pcf_setup.SetTime = PCF8563RTC_SetTime;
	pcf_setup.SetHour = PCF8563RTC_SetHour;
	pcf_setup.SetMinute = PCF8563RTC_SetMinute;
	pcf_setup.SetSecond = PCF8563RTC_SetSecond;
	pcf_setup.SetClkOut = PCF8563RTC_SetClkOut;
	pcf_setup.SetDate = PCF8563RTC_SetDate;
	pcf_setup.SetDay = PCF8563RTC_SetDay;
	pcf_setup.SetWeekday = PCF8563RTC_SetWeekday;
	pcf_setup.SetMonth = PCF8563RTC_SetMonth;
	pcf_setup.SetYear = PCF8563RTC_SetYear;
	pcf_setup.GetTime = PCF8563RTC_GetTime;
	pcf_setup.GetDate = PCF8563RTC_GetDate;
	pcf_setup.bcd2dec = PCF8563RTC_bcd2dec;
	pcf_setup.bintobcd = PCF8563RTC_bintobcd;
	
	PCF8563RTC_Init();
	
	return pcf_setup;
}
/*** Procedure and Funtion definition ***/
void PCF8563RTC_Init(void)
{
	i2c.start();									// Start I2C communication
	i2c.connect(PCF8563, TWI_WRITE);				// Connect to PCF8563 by sending its ID on I2c Bus
	i2c.master_write(PCF8563ControlRegAddress_U8);	// Select the PCF8563 ControlRegister to configure PCF8563
	i2c.master_write(0x00);							// Write 0x00 to Control register to disable SQW-Out
	i2c.stop();										// Stop I2C communication after initializing PCF8563
}
void PCF8563RTC_SetTime(uint8_t var_hour_u8, uint8_t var_min_u8, uint8_t var_sec_u8)
{
	i2c.start();									// Start I2C communication
	i2c.connect(PCF8563, TWI_WRITE);				// connect to PCF8563 by sending its ID on I2c Bus
	i2c.master_write(PCF8563SecondRegAddress_U8);	// Select the SEC RAM address
	i2c.master_write(var_sec_u8);			        // Write sec from RAM address 02H
	i2c.master_write(var_min_u8);			        // Write min from RAM address 03H
	i2c.master_write(var_hour_u8);			        // Write hour from RAM address 04H
	i2c.stop();           							// Stop I2C communication after Setting the Time
}
void PCF8563RTC_SetHour(uint8_t var_hour_u8)
{
	i2c.start();									// Start I2C communication
	i2c.connect(PCF8563, TWI_WRITE);				// connect to PCF8563 by sending its ID on I2c Bus
	i2c.master_write(PCF8563HourRegAddress_U8);		// Select the SEC RAM address
	i2c.master_write(var_hour_u8);			        // Write hour from RAM address 04H
	i2c.stop();           							// Stop I2C communication after Setting the Time
}
void PCF8563RTC_SetMinute(uint8_t var_min_u8)
{
	i2c.start();									// Start I2C communication
	i2c.connect(PCF8563, TWI_WRITE);				// connect to PCF8563 by sending its ID on I2c Bus
	i2c.master_write(PCF8563MinuteRegAddress_U8);	// Select the SEC RAM address
	i2c.master_write(var_min_u8);			        // Write min from RAM address 03H
	i2c.stop();           							// Stop I2C communication after Setting the Time
}
void PCF8563RTC_SetSecond(uint8_t var_sec_u8)
{
	i2c.start();									// Start I2C communication
	i2c.connect(PCF8563, TWI_WRITE);				// connect to PCF8563 by sending its ID on I2c Bus
	i2c.master_write(PCF8563SecondRegAddress_U8);	// Select the SEC RAM address
	i2c.master_write(var_sec_u8);			        // Write sec from RAM address 02H
	i2c.stop();           							// Stop I2C communication after Setting the Time
}
void PCF8563RTC_SetClkOut(uint8_t onoff, uint8_t freq)
{
	uint8_t word = 0;
	if(onoff)
		word = 0x80 | (freq & 0x03);
	i2c.start();								// Start I2C communication
	i2c.connect(PCF8563, TWI_WRITE);			// connect to PCF8563 by sending its ID on I2c Bus
	i2c.master_write(PCF8563CLKOUT_control_U8);	// Select the CLKOUT RAM address
	i2c.master_write(word);						// Write Clock from RAM address 0DH						
	i2c.stop();           						// Stop I2C communication after Setting the Time
}
void PCF8563RTC_SetDate(uint8_t var_day_u8, uint8_t var_weekday_u8, uint8_t var_month_u8, uint8_t var_year_u8)
{
	i2c.start();								// Start I2C communication
	i2c.connect(PCF8563, TWI_WRITE);			// connect to PCF8563 by sending its ID on I2c Bus
	i2c.master_write(PCF8563DayRegAddress_U8);  // Request DAY RAM address at 05H
	i2c.master_write(var_day_u8);				// Write date on RAM address 05H
	i2c.master_write(var_weekday_u8);			// Write date on RAM address 06H
	i2c.master_write(var_month_u8);				// Write month on RAM address 07H
	i2c.master_write(var_year_u8);				// Write year on RAM address 08h
	i2c.stop();									// Stop I2C communication after Setting the Date
}
void PCF8563RTC_SetYear(uint8_t var_year_u8)
{
	i2c.start();								// Start I2C communication
	i2c.connect(PCF8563, TWI_WRITE);			// connect to PCF8563 by sending its ID on I2c Bus
	i2c.master_write(PCF8563YearRegAddress_U8);	// Request DAY RAM address at 08H
	i2c.master_write(var_year_u8);			    // Write year on RAM address 08h
	i2c.stop();									// Stop I2C communication after Setting the Date
}
void PCF8563RTC_SetMonth(uint8_t var_month_u8)
{
	i2c.start();									// Start I2C communication
	i2c.connect(PCF8563, TWI_WRITE);				// connect to PCF8563 by sending its ID on I2c Bus
	i2c.master_write(PCF8563MonthRegAddress_U8);	// Request DAY RAM address at 07H
	i2c.master_write(var_month_u8);					// Write month on RAM address 07H
	i2c.stop();										// Stop I2C communication after Setting the Date
}
void PCF8563RTC_SetWeekday(uint8_t var_weekday_u8)
{
	i2c.start();									// Start I2C communication
	i2c.connect(PCF8563, TWI_WRITE);				// connect to PCF8563 by sending its ID on I2c Bus
	i2c.master_write(PCF8563WeekdayRegAddress_U8);  // Request DAY RAM address at 06H
	i2c.master_write(var_weekday_u8);               // Write date on RAM address 06H
	i2c.stop();										// Stop I2C communication after Setting the Date
}
void PCF8563RTC_SetDay(uint8_t var_day_u8)
{
	i2c.start();								// Start I2C communication
	i2c.connect(PCF8563, TWI_WRITE);			// connect to PCF8563 by sending its ID on I2c Bus
	i2c.master_write(PCF8563DayRegAddress_U8);  // Request DAY RAM address at 05H
	i2c.master_write(var_day_u8);			    // Write date on RAM address 05H
	i2c.stop();									// Stop I2C communication after Setting the Date
}
struct time PCF8563RTC_GetTime(void)
{
	struct time result;
	i2c.start();											// Start I2C communication
	i2c.connect(PCF8563, TWI_WRITE);						// connect to PCF8563 by sending its ID on I2c Bus
	i2c.master_write(PCF8563SecondRegAddress_U8);			// Request Sec RAM address at 00H
	i2c.stop();												// Stop I2C communication after selecting Sec Register
	i2c.start();											// Start I2C communication
	i2c.connect(PCF8563, TWI_READ);							// connect to PCF8563(Read mode) by sending its ID
	result.VL_seconds = i2c.master_read(TWI_ACK) & ~0x80;	// read second and return Positive ACK
	result.minutes = i2c.master_read(TWI_ACK) & ~0x80;		// read minute and return Positive ACK
	result.hours = i2c.master_read(TWI_NACK) & ~0xC0;		// read hour and return Negative/No ACK
	i2c.stop();												// Stop I2C communication after reading the Time
	return result;
}
struct date PCF8563RTC_GetDate(void)
{
	struct date result;
	i2c.start();												// Start I2C communication
	i2c.connect(PCF8563, TWI_WRITE);							// connect to PCF8563 by sending its ID on I2c Bus
	i2c.master_write(PCF8563DayRegAddress_U8);					// Request DAY RAM address at 04H
	i2c.stop();													// Stop I2C communication after selecting DAY Register
	i2c.start();												// Start I2C communication
	i2c.connect(PCF8563, TWI_READ);								// connect to PCF8563 (Read mode) by sending its ID
	result.days = i2c.master_read(TWI_ACK) & ~0xC0;				// read Day and return Positive ACK
	result.weekdays = i2c.master_read(TWI_ACK) & ~0xF8;			// read Month and return Positive ACK
	result.century_months = i2c.master_read(TWI_ACK) & ~0xE0;
	result.years = i2c.master_read(TWI_NACK);				    // read Year and return Negative/No ACK
	i2c.stop();													// Stop I2C communication after reading the Date
	return result;
}
// uint8_t PCF8563RTC_bcd2dec(uint8_t num)
uint8_t PCF8563RTC_bcd2dec(uint8_t num)
{
	return ((num / 16 * 10) + (num % 16));
}
// uint8_t PCF8563RTC_bintobcd(uint8_t bin)
uint8_t PCF8563RTC_bintobcd(uint8_t bin)
{
	return (((bin) / 10) << 4) + ((bin) % 10);
}

/*** EOF ***/

