/*************************************************************************
	ATCOMMANDS
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ALL
Date: 24042023
*************************************************************************/
/*** File Library ***/
#include "atcommands.h"
#include <string.h>

/*** File Variable ***/
char ATstr[72];

/*** Procedure & Function definition ***/
char* BT05ATcmd(uint16_t num){
	switch(num)
	{
		case 1:
			strcpy(ATstr, "AT\r\n");
		break;
		case 2:
			strcpy(ATstr, "AT+VERSION\r\n");
		break;
		case 3:
			strcpy(ATstr, "AT+NAME\r\n"); // Param ? module Bluetooth name Default: MLT-BT05 longest ? 18 byte
		break;
		case 4:
			strcpy(ATstr, "AT+PIN\r\n"); // Param ? 6 byte bit pairing password default “? 123456”
		break;
		case 5: // Very usefull
			strcpy(ATstr, "AT+GETSTAT\r\n"); // Param ? 0-1 , 0——not connected, 1——connected
		break;
		case 10:
			strcpy(ATstr, "AT+ROLE\r\n"); // Param ?? 0-4 ?0 ——slave mode?, 1 ——master mode?, 2 ——sensor mode, 3 ——iBeacon mode, 4 ——WeChat mode, default ? 0
		break;
		case 101:
			strcpy(ATstr, "AT+ROLE0\r\n"); // 0 ——slave mode
		break;
		case 102:
			strcpy(ATstr, "AT+ROLE1\r\n"); // 1 ——master mode
		break;
		case 103:
			strcpy(ATstr, "AT+ROLE2\r\n"); // 2 ——sensor mode
		break;
		case 104:
			strcpy(ATstr, "AT+ROLE3\r\n"); // 3 ——iBeacon mode
		break;
		case 105:
			strcpy(ATstr, "AT+ROLE4\r\n"); // 4 ——WeChat mode
		case 11:
			strcpy(ATstr, "AT+LADDR\r\n");
		break;
		case 12:
			strcpy(ATstr, "AT+ADVI\r\n"); // 0 ——100ms,1 ——500ms,2 ——7500ms,3 ——1000ms,4 ——2000ms,5 ——4000ms,6 ——8000ms
		break;
		case 121:
			strcpy(ATstr, "AT+ADVI0\r\n"); // 0 ——100ms
		break;
		case 122:
			strcpy(ATstr, "AT+ADVI1\r\n"); // 1 ——500ms
		break;
		case 123:
			strcpy(ATstr, "AT+ADVI2\r\n"); // 2 ——7500ms
		break;
		case 124:
			strcpy(ATstr, "AT+ADVI3\r\n"); // 3 ——1000ms
		break;
		case 125:
			strcpy(ATstr, "AT+ADVI4\r\n"); // 4 ——2000ms
		break;
		case 126:
			strcpy(ATstr, "AT+ADVI5\r\n"); // 5 ——4000ms
		break;
		case 127:
			strcpy(ATstr, "AT+ADVI6\r\n"); // 6 ——8000ms
		break;
		case 13:
			strcpy(ATstr, "AT+TYPE\r\n"); // 0——no password,1——password pairing,2——password pairing and binding, default ? 0
		break;
		case 131:
			strcpy(ATstr, "AT+TYPE0\r\n"); // 0——no password
		break;
		case 132:
			strcpy(ATstr, "AT+TYPE1\r\n"); // 1——password pairing
		break;
		case 133:
			strcpy(ATstr, "AT+TYPE2\r\n"); // 2——password pairing and binding
		break;
		case 14:
			strcpy(ATstr, "AT+BAUD\r\n"); // 0 ——115200,1 ——57600,2 ——38400,3 ——19200,4 —— 9600, default ? 0
		break;
		case 141: // zs-040: works. 1200 hidden
			//strcpy(ATstr, "AT+BAUD1\r\n");
		break;
		case 142: // zs-040: works. 2400 hidden
			//strcpy(ATstr, "AT+BAUD2\r\n");
		break;
		case 143: // zs-040: works. 4800 hidden
			//strcpy(ATstr, "AT+BAUD3\r\n");
		break;
		case 144: // zs-040: works. 9600 hidden
			//strcpy(ATstr, "AT+BAUD4\r\n");
		break;
		case 145: // zs-040: works. 19200 hidden
			//strcpy(ATstr, "AT+BAUD5\r\n");
		break;
		case 146: // zs-040: works. 38400 hidden
			strcpy(ATstr, "AT+BAUD6\r\n");
		break;
		case 147: // zs-040: works. 57600 hidden
			//strcpy(ATstr, "AT+BAUD7\r\n");
		break;
		case 148: // zs-040: works. 115200 hidden
			//strcpy(ATstr, "AT+BAUD8\r\n");
		break;
		case 15:
			strcpy(ATstr, "AT+UUID\r\n"); // Param: 0x0001~0xFFFE, default ? 0xFFE0
		break;
		case 16:
			strcpy(ATstr, "AT+CHAR\r\n"); // Param:0x0001~0xFFFE, default ? 0xFFE1
		break;
		case 17:
			strcpy(ATstr, "AT+IBSUUID\r\n"); // Param ?FDA50693A4E24FB1AFCFC6EB07647825
		break;
		case 18:
			strcpy(ATstr, "AT+MAJOR\r\n"); // Param : 0x0001~0xFFFE, default ? 0x0007
		break;
		case 19:
			strcpy(ATstr, "AT+MINOR\r\n"); // Param: 0x0001~0xFFFE, default ? 0x000A
		break;
		case 20:
			strcpy(ATstr, "AT+SLEEP\r\n"); // when PM=1.
		break;
		case 21:
			strcpy(ATstr, "AT+INQ\r\n"); // Param ? 1-0, 1: start scanning, 0: stop scanning
		break;
		case 211:
			strcpy(ATstr, "AT+INQ0\r\n"); // 0: stop scanning
		break;
		case 212:
			strcpy(ATstr, "AT+INQ1\r\n"); // 1: start scanning
		break;
		case 22:
			//strcpy(ATstr, "AT+CONN<Param>\r\n"); // Param ? 0-7
		break;
		case 23:
			//strcpy(ATstr, "AT+RSLV< Param >\r\n"); // Param ? ( 0-7 )
		break;
		case 24:
			strcpy(ATstr, "AT+BAND\r\n"); // Param ? MAC address
		break;
		case 25:
			strcpy(ATstr, "AT+CLRBAND\r\n"); // no
		break;
		case 26:
			//strcpy(ATstr, "AT+GETDCN<Param>\r\n"); // Param ?? 1-8 ?
		break;
		case 27:
			strcpy(ATstr, "AT+DISC\r\n"); // Disconnect no
		break;
		case 28:
			//strcpy(ATstr, "AT+AT_WXSWH<Param>\r\n"); // Param ?? 0-1), 0 ? H5 communication, 1 ? factory server, Default: 0
		break;
		case 29:
			strcpy(ATstr, "AT+RESET\r\n");
		break;
		case 30: // hiden
			//strcpy(ATstr, "AT+DEFAULT\r\n"); // 4dbm, 9600bps (115200bps), 200ms, PM=0, Onboard LED 2:1, External indicator led1: 2
		break;
		case 31:
			strcpy(ATstr, "AT+HELP\r\n"); // Lists commands
		break;
		case 801:
			strcpy(ATstr, "AT+PIN123456\r\n");
		break;
		case 802:
			strcpy(ATstr, "AT+PIN654321\r\n");
		break;
		case 803:
			strcpy(ATstr, "AT+PIN916919\r\n");
		break;
		case 901:
			strcpy(ATstr, "AT+NAMEBT05\r\n"); // Param ? module Bluetooth name Default: BT05 longest ? 18 byte
		break;
		case 902:
			strcpy(ATstr, "AT+NAMEHome1\r\n"); // Param ? module Bluetooth name Default: BT05 longest ? 18 byte
		break;
		case 903:
			strcpy(ATstr, "AT+NAMEHome2\r\n"); // Param ? module Bluetooth name Default: BT05 longest ? 18 byte
		break;
		case 904:
			strcpy(ATstr, "AT+NAMEHome3\r\n"); // Param ? module Bluetooth name Default: BT05 longest ? 18 byte
		break;
		case 905:
			strcpy(ATstr, "AT+NAMEHome4\r\n"); // Param ? module Bluetooth name Default: BT05 longest ? 18 byte
		break;
		/******/
		default:
			strcpy(ATstr, "AT\r\n");
		break;
	};
	return ATstr;
}

char* HC42ATcmd(uint16_t num){
	switch(num)
	{
		case 1: // zs-040: works.
			strcpy(ATstr, "AT\r\n");
		break;
		case 2: // zs-040: works.
			strcpy(ATstr, "AT+VERSION\r\n");
		break;
		case 3: // zs-040 works
			strcpy(ATstr, "AT+NAME=HC42\r\n");
		break;
		case 4:
			strcpy(ATstr, "AT+RFPM=4\r\n"); // 4dBm (4, 3, 0, -4, -8, -12, -16, -20, -40)
		break;
		case 5:
			strcpy(ATstr, "AT+UART=9600\r\n"); // ( 1200,2400,4800,9600,19200,38400, 57600,115200,230400 )
		break;
		case 6:
			strcpy(ATstr, "AT+UART=38400\r\n"); // ( 1200,2400,4800,9600,19200,38400, 57600,115200,230400 )
		break;
		case 7:
			strcpy(ATstr, "AT+PM\r\n");
		break;
		case 8:
			strcpy(ATstr, "AT+PM=0\r\n"); // power consumption 0 or 1.
		break;
		case 9: // zs-040 works
			strcpy(ATstr, "AT+SLEEP\r\n"); // when PM=1.
		break;
		case 10:
			strcpy(ATstr, "AT+PD\r\n"); // shutdown command
		break;
		case 11:
			strcpy(ATstr, "AT+LEDnM\r\n"); // (1-off, 2-depends power consumption, 3-on)
		break;
		case 12:
			strcpy(ATstr, "AT+LEDnM=2\r\n"); // research choices ? (1-off, 2-depends power consumption, 3-on)
		break;
		case 13: // zs-040 works
			strcpy(ATstr, "AT+DEFAULT\r\n"); // 4dbm, 9600bps (115200bps), 200ms, PM=0, Onboard LED 2:1, External indicator led1: 2
		break;
		case 14: // zs-040 works
			strcpy(ATstr, "AT+ROLE\r\n"); // S or P, M or C
		break;
		case 15:
			strcpy(ATstr, "AT+ROLE=S\r\n"); // S or P, M or C (slave or master)
		break;
		case 16: // zs-040 works
			strcpy(ATstr, "AT+RESET\r\n");
		break;
		case 17:
			strcpy(ATstr, "AT+IBEN\r\n"); // 0?OFF)
		break;
		case 18:
			strcpy(ATstr, "AT+IBEN=0\r\n"); // 0?OFF) 1 (on)
		break;
		case 19:
			strcpy(ATstr, "AT+IBUUID\r\n"); // inquire.
		break;
		case 20:
			strcpy(ATstr, "AT+IBUUID=FDA50693-A4E2-4FB1-AFCF-C6EB07647825\r\n"); // example: FDA50693-A4E2-4FB1-AFCF-C6EB07647825
		break;
		case 21:
			strcpy(ATstr, "AT+IBRSSI\r\n"); // 0xC3
		break;
		case 22:
			strcpy(ATstr, "AT+IBRSSI=0xC3\r\n"); // 0xC3
		break;
		case 23:
			strcpy(ATstr, "AT+IBMAJ\r\n"); // 0x27C6
		break;
		case 24:
			strcpy(ATstr, "AT+IBMAJ=0x27C6\r\n"); // 0x27C6 (default)
		break;
		case 25:
			strcpy(ATstr, "AT+IBMIN\r\n"); // 0x8B06
		break;
		case 26:
			strcpy(ATstr, "AT+IBMIN=1234\r\n"); // 0x8B06 (default)
		break;
		case 27:
			strcpy(ATstr, "AT+AINT\r\n"); // 200ms
		break;
		case 28:
			strcpy(ATstr, "AT+AINT=200\r\n"); // 20ms-10000ms
		break;
		case 29:
			strcpy(ATstr, "AT+HELP\r\n"); // Lists commands
		break;
		/******/
		default:
			strcpy(ATstr, "AT\r\n");
		break;
	};
	return ATstr;
}

char* HC05ATcmd(uint16_t num){
	switch(num)
	{
		case 1: // zs-040: works.
			strcpy(ATstr, "AT\r\n");
		break;
		case 2: // zs-040: works.
			strcpy(ATstr, "AT+VERSION?\r\n");
		break;
		case 3:
			strcpy(ATstr, "AT+ORGL\r\n");
		break;
		case 4:
			strcpy(ATstr, "AT+ADDR?\r\n");
		break;
		case 5: // zs-040: works
			strcpy(ATstr, "AT+NAME=HC05\r\n");
		break;
		case 6: //This clears name if ends with '?'.
			strcpy(ATstr, "AT+NAME?\r\n");
		break;
		case 7:
			strcpy(ATstr, "AT+RNAME?0002,72,od2224\r\n");
		break;
		case 8: // ZS-040 WORKS
			strcpy(ATstr, "AT+ROLE0\r\n");
		break;
		case 9:
			strcpy(ATstr, "AT+ROLE?\r\n"); // 0 -> Slave, 1 -> Master, 2 -> Slave-Loop
		break;
		case 10:
			strcpy(ATstr, "AT+CLASS=Param1\r\n");
		break;
		case 11:
			strcpy(ATstr, "AT+CLASS?\r\n");
		break;
		case 12:
			strcpy(ATstr, "AT+IAC=9e8b3f\r\n");
		break;
		case 13:
			strcpy(ATstr, "AT+IAC?\r\n");
		break;
		case 14:
			strcpy(ATstr, "AT+INQM=1,9,48\r\n");
		break;
		case 15:
			strcpy(ATstr, "AT+INQM\r\n");
		break;
		case 16: // zs-040: not work
			strcpy(ATstr, "AT+PWD:1234\r\n");
		break;
		case 17: // zs-040: not work
			strcpy(ATstr, "AT+PSWD?\r\n");
		break;
		case 18: // zs-040: not work
			strcpy(ATstr, "AT+UART=9600,0,0,\r\n");
		break;
		case 19:
			strcpy(ATstr, "AT+UART?\r\n");
		break;
		case 20:
			strcpy(ATstr, "AT+CMODE=2\r\n");
		break;
		case 21:
			strcpy(ATstr, "AT+CMODE?\r\n");
		break;
		case 22:
			strcpy(ATstr, "AT+BIND=1234,56,abcdef\r\n");
		break;
		case 23:
			strcpy(ATstr, "AT+BIND?\r\n");
		break;
		case 24:
			strcpy(ATstr, "AT+POLAR=0,1\r\n");
		break;
		case 25:
			strcpy(ATstr, "AT+POLAR?\r\n");
		break;
		case 26:
			strcpy(ATstr, "AT+PI0=10,1\r\n");
		break;
		case 27:
			strcpy(ATstr, "AT+PI0=10,0\r\n");
		break;
		case 28:
			strcpy(ATstr, "AT+MPI0=404\r\n");
		break;
		case 29:
			strcpy(ATstr, "AT+PI0=004\r\n");
		break;
		case 30:
			strcpy(ATstr, "AT+PI0=400\r\n");
		break;
		case 31:
			strcpy(ATstr, "AT+MPI0=0\r\n");
		break;
		case 32:
			strcpy(ATstr, "AT+MPIO?\r\n");
		break;
		case 33:
			strcpy(ATstr, "AT+IPSCAN=1234,500,1200,250\r\n");
		break;
		case 34:
			strcpy(ATstr, "AT+IPSCAN?\r\n");
		break;
		case 35:
			strcpy(ATstr, "AT+SNIFF=Param1,Param2,Param3,Param4");
		break;
		case 36:
			strcpy(ATstr, "AT+SNIFF?\r\n");
		break;
		case 37:
			strcpy(ATstr, "AT+SENM=Param1,Param2\r\n");
		break;
		case 38:
			strcpy(ATstr, "AT+SENM?\r\n");
		break;
		case 39:
			strcpy(ATstr, "AT+RMSAD=1234,56,abcdef\r\n");
		break;
		case 40:
			strcpy(ATstr, "AT+RMAAD\r\n");
		break;
		case 41:
			strcpy(ATstr, "AT+FSAD=1234,56,abcdef\r\n");
		break;
		case 42:
			strcpy(ATstr, "AT+ADCN?\r\n");
		break;
		case 43:
			strcpy(ATstr, "AT+MRAD?\r\n");
		break;
		case 44:
			strcpy(ATstr, "AT+STATE?\r\n");
		break;
		case 45:
			strcpy(ATstr, "AT+INIT\r\n");
		break;
		case 46:
			strcpy(ATstr, "AT+IAC=9e8b33\r\n");
		break;
		case 47:
			strcpy(ATstr, "AT+CLASS=0\r\n");
		break;
		case 48:
			strcpy(ATstr, "AT+INQM=1,3,48\r\n");
		break;
		case 49: // vs-040: works
			strcpy(ATstr, "AT+INQ\r\n");
		break;
		case 50:
			strcpy(ATstr, "AT+PAIR=1234,56,abcdef,20\r\n");
		break;
		case 51:
			strcpy(ATstr, "AT+FSAD=1234,56,abcdef\r\n");
		break;
		case 52:
			strcpy(ATstr, "AT+LINK=1234,56,abcdef\r\n");
		break;
		case 53:
			strcpy(ATstr, "AT+DISC\r\n");
		break;
		case 54:
			strcpy(ATstr, "AT+ENSNIFF=Param1\r\n");
		break;
		case 55:
			strcpy(ATstr, "AT+EXSNIFF=Param1");
		break;
		case 56: // zs-040: works.
			strcpy(ATstr, "AT+RESET\r\n");
		break;
		case 57:
			strcpy(ATstr, "AT+HELP\r\n"); // Lists commands
		break;
		default:
			strcpy(ATstr, "AT\r\n");
		break;
	};
	return ATstr;
}

char* ESP8266cmd(uint16_t num)
{
	switch(num)
	{
		case 1:
			strcpy(ATstr, "AT\r\n");
		break;
		
		
		
		case 99:
			strcpy(ATstr, "AT+RST\r\n");
		break;
		default:
			strcpy(ATstr, "AT\r\n");
		break;
	};
	
	/***
	Firmware version AT+GMR AT+GMR 0018000902 OK
	
	List Access Points AT+CWLAP AT+CWLAP +CWLAP:(4,"RochefortSurLac",-
	38,"70:62:b8:6f:6d:58",1)
	+CWLAP:(4,"LiliPad2.4",-83,"f8:7b:8c:1e:7c:6d",1)
	OK
	
	Join Access Point AT+CWJAP?
	AT+CWJAP="SSID","Password"
	Query AT+CWJAP? +CWJAP:"RochefortSurLac" OK
	
	Quit Access Point AT+CWQAP=?
	AT+CWQAP
	Query
	OK
	
	Get IP Address AT+CIFSR AT+CIFSR 192.168.0.105
	OK
	
	Set Parameters of
	Access Point
	AT+ CWSAP?
	AT+ CWSAP= <ssid>,<pwd>,<chl>, <ecn>
	Query
	ssid, pwd
	chl = channel, ecn = encryption
	
	WiFi Mode AT+CWMODE?
	AT+CWMODE=1
	AT+CWMODE=2
	AT+CWMODE=3
	Query
	STA
	AP
	BOTH
	
	Set up TCP or UDP
	connection
	AT+CIPSTART=?
	(CIPMUX=0) AT+CIPSTART =
	<type>,<addr>,<port>
	(CIPMUX=1) AT+CIPSTART=
	<id><type>,<addr>, <port>
	Query
	id = 0-4, type = TCP/UDP, addr = IP address, port= port
	
	TCP/UDP
	Connections
	AT+ CIPMUX?
	AT+ CIPMUX=0
	AT+ CIPMUX=1
	Query
	Single
	Multiple
	
	Check join devices' IP AT+CWLIF
	
	TCP/IP Connection
	Status
	AT+CIPSTATUS AT+CIPSTATUS? no this fun
	
	Send TCP/IP data (CIPMUX=0) AT+CIPSEND=<length>;
	(CIPMUX=1) AT+CIPSEND= <id>,<length>
	
	Close TCP / UDP
	connection
	AT+CIPCLOSE=<id> or AT+CIPCLOSE
	
	Set as server AT+ CIPSERVER= <mode>[,<port>] mode 0 to close server mode; mode 1 to open; port = port
	
	Set the server
	timeout
	AT+CIPSTO?
	AT+CIPSTO=<time>
	Query
	<time>0~28800 in seconds
	
	Baud Rate* AT+CIOBAUD?
	Supported: 9600, 19200, 38400, 74880,
	115200, 230400, 460800, 921600
	Query AT+CIOBAUD? +CIOBAUD:9600 OK
	
	Check IP address AT+CIFSR AT+CIFSR 192.168.0.106
	OK
	
	Firmware Upgrade
	(from Cloud)
	AT+CIUPDATE 1. +CIPUPDATE:1 found server
	2. +CIPUPDATE:2 connect server
	3. +CIPUPDATE:3 got edition
	4. +CIPUPDATE:4 start update
	
	Received data +IPD (CIPMUX=0): + IPD, <len>:
	(CIPMUX=1): + IPD, <id>, <len>: <data>
	
	Watchdog Enable* AT+CSYSWDTENABLE Watchdog, auto restart when program errors occur: enable
	
	Watchdog Disable* AT+CSYSWDTDISABLE Watchdog, auto restart when program errors occur: disable
	***/
	
	return NULL;
}

/*** EOF ***/

