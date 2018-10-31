/*
 * DateTime.cpp
 *
 *  Created on: 31.03.2018
 *      Author: Udo
 */
/*
//#include "Arduino.h"
#include <EthernetUdp.h>
#include <Ethernet.h>

#include "DateTime.h"

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
EthernetUDP Udp;
char timeServer[] = "pool.ntp.org";
//char timeServer[] = "time.nist.gov"; // time.nist.gov NTP server
unsigned int localPort = 8888;       // local port to listen for UDP packets


/*DateTime::DateTime() {
	summerWinterTimeArray[0][0] = 2018;
	summerWinterTimeArray[0][1] = 10;
	summerWinterTimeArray[0][2] = 28;

	summerWinterTimeArray[1][0] = 2019;
	summerWinterTimeArray[1][1] = 3;
	summerWinterTimeArray[1][2] = 31;

/*	summerWinterTimeArray[2][0] = 2019;
	summerWinterTimeArray[2][1] = 10;
	summerWinterTimeArray[2][2] = 27;

	summerWinterTimeArray[3][0] = 2020;
	summerWinterTimeArray[3][1] = 3;
	summerWinterTimeArray[3][2] = 29;

	summerWinterTimeArray[4][0] = 2020;
	summerWinterTimeArray[4][1] = 10;
	summerWinterTimeArray[4][2] = 25;


	hour=0;
	minute=0;
	second=0;
	year=0;
	month=0;
	day=0;

	// take care, Ethernet must be activated before
	// Ethernet begin
	Udp.begin(localPort);
}

DateTime::~DateTime() {
	// TODO Auto-generated destructor stub
}

void DateTime::sendNTPpacket(char* address)
{
	  memset(packetBuffer, 0, NTP_PACKET_SIZE);
	  // Initialize values needed to form NTP request
	  // (see URL above for details on the packets)
	  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
	  packetBuffer[1] = 0;     // Stratum, or type of clock
	  packetBuffer[2] = 6;     // Polling Interval
	  packetBuffer[3] = 0xEC;  // Peer Clock Precision
	  // 8 bytes of zero for Root Delay & Root Dispersion
	  packetBuffer[12]  = 49;
	  packetBuffer[13]  = 0x4E;
	  packetBuffer[14]  = 49;
	  packetBuffer[15]  = 52;
	  // all NTP fields have been given values, now
	  // you can send a packet requesting a timestamp:
	  Udp.beginPacket(address, 123); //NTP requests are to port 123
	  Udp.write(packetBuffer, NTP_PACKET_SIZE);
	  Udp.endPacket();
}


bool DateTime:: isNewSync()
{
	bool isSync = false;
	sendNTPpacket(timeServer); // send an NTP packet to a time server

	delay(100);
	Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

	// the timestamp starts at byte 40 of the received packet and is four bytes,
	// or two words, long. First, extract the two words:

	unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
	unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
	// combine the four bytes (two words) into a long integer
	// this is NTP time (seconds since Jan 1 1900):
	unsigned long secsSince1900 = highWord << 16 | lowWord;

	if(secsSince1900 > 0){


		Serial.print("Seconds since Jan 1 1900 = ");
		Serial.println(secsSince1900);

		// now convert NTP time into everyday time:
		Serial.print("Unix time = ");
		// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
		const unsigned long seventyYears = 2208988800UL;
		// subtract seventy years:
		unsigned long epoch = secsSince1900 - seventyYears;
		// print Unix time:
		Serial.println(epoch);


		// print the hour, minute and second:
		Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
		hour = ((epoch  % 86400L) / 3600);
		Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
		Serial.print(':');
		if (((epoch % 3600) / 60) < 10) {
				// In the first 10 minutes of each hour, we'll want a leading '0'
			Serial.print('0');
		}
		minute = ((epoch  % 3600) / 60);
		Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)

		Serial.print(':');
		if ((epoch % 60) < 10) {
		// In the first 10 seconds of each minute, we'll want a leading '0'
			Serial.print('0');
		 }
		second = epoch % 60;
		Serial.println(epoch % 60); // print the second
		isSync = true;
	}
		// wait ten seconds before asking for the time again
	delay(3000);
	Udp.parsePacket();
	Ethernet.maintain();
	return isSync;
}


int DateTime::getTimeDiff(Time time)
{
	// it is wintertime as default
	int timeDiff = 1;
	Serial.print("get to Function getTimeDiff month is: ");
	Serial.println(time.mon);
	// timechange every mach and octoer
	// other month not critical
	// between April and September it is summerTime, add two hours
	if((time.mon > MARCH) && (time.mon < OCTOBER))
	{
		Serial.println("after march and before october, no change of time ");
		return 2;
	}
	// between january and February and november and december it is wintertime add one hour
	else if ((time.mon < MARCH) && (time.mon > OCTOBER))
	{
		Serial.println("before march and after october, no change of time ");
		return 1;
	}

	// find array year
	uint16_t yearIndex = 0;
	bool summerTime = true;
	for(yearIndex=0;yearIndex<ARRAYYEAR_COUNT;++yearIndex)
	{
		// search year
		if(summerWinterTimeArray[yearIndex][0]==time.year)
		{
			Serial.println("it is the year ");
			// if it is october go one arry further, and it is wintertime
			if(time.mon  == OCTOBER)
			{
				Serial.println("it is october ");
				// second half of the year
				Serial.println("it is wintertime ");
				summerTime = false;
			}
			break;
		}
	}

	Serial.println(summerWinterTimeArray[yearIndex][2]);
	Serial.println(time.date);
	// it is either october or march, so get the day
	if(time.date == summerWinterTimeArray[yearIndex][2])
	{

		// summertime and after 2 oclock, go for two hours
		if(summerTime && (time.hour > CHANGEHOURE))
		{
			Serial.println("summerTime, timeDiff 2");
			timeDiff = 2;
		}
		// wintertime and after 2 oclock, go for one hours
		else if(!summerTime && (time.hour > CHANGEHOURE))
		{
			Serial.println("wintertime, timeDiff 1");
			timeDiff = 1;
		}
		// summertime and 2 oclock or before, go for two hours (it is still wintertime)
		else if(summerTime)
		{
			Serial.println("timeDiff 1");
			timeDiff = 1;
		}
		//
		else
		{
			Serial.println("else, timeDiff 2");
			timeDiff = 2;
		}
	}
	return timeDiff;
}*/


