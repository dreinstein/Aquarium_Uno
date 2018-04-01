

#include "Arduino.h"
//#include <LiquidCrystal.h> //LCD-Bibliothek laden

#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <ds3231.h>
#include <Ethernet.h>
#include <DallasTemperature.h>
#include <EthernetUdp.h>

#include "Definitions.h"
#include "Display.h"
#include "Light.h"
#include "Heater.h"
#include "Pump.h"
#include "DateTime.h"

long refresh=0;


// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
OneWire  ds(TEMPSENSOR);
DallasTemperature sensors(&ds);
//LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D0, LCD_D1, LCD_D2, LCD_D3);

/// Belegung SDA, SCL
/// Arduino SDA = PinAnalog 4
///         SLC = Pin Analog 5

LiquidCrystal_I2C lcd(0x27, 16,2);

// functionDeclaration
bool setServiceMode();
bool setOff();

class Display *display;
class Light *light;
class Heater *heater;
class Pump *pump;
class DateTime* dateTime;

// assign a MAC address for the Ethernet controller.
// fill in your address here:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
// assign an IP address for the controller:
IPAddress ip(192, 168, 0, 22);

//unsigned int localPort = 8888;       // local port to listen for UDP packets

//char timeServer[] = "tp.uni-regensburg.de";
//char timeServer[] = "time.nist.gov"; // time.nist.gov NTP server


//const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

//byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
//EthernetUDP Udp;



/*// send an NTP request to the time server at the given address
void sendNTPpacket(char* address) {
  // set all bytes in the buffer to 0
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
}*/



void setup()
{
// Add your initialization code here

	Serial.println("Setup\n");

	pinMode(RELAIS2,OUTPUT);
	pinMode(RELAIS3,OUTPUT);
	pinMode(RELAIS4,OUTPUT);


	pinMode(SERVICEBUTTON,INPUT);
	pinMode(ONOFFBUTTON,INPUT);
	pinMode(TEMPSENSOR,INPUT);

	EthernetServer server(80);
  // start the Ethernet connection and the server:
	Ethernet.begin(mac, ip);
	server.begin();

	display = new Display(&sensors,&lcd,&rtc);
	light = new Light(&rtc);
	heater = new Heater();
	pump = new Pump();
	dateTime = new DateTime();

	lcd.init();
	lcd.backlight();
	lcd.begin(16, 2);
	rtc.begin();
	sensors.begin();
	sensors.setResolution(TEMP_RESOLUTION);
	Serial.begin(9600);
	refresh = 0;

//	rtc.setDate(27,03,2018);

	rtc.setDate(06,03,2018);
	//	rtc.setDOW(2);
	rtc.setTime(18,5,00);

	Serial.println("initialised");

}


// The loop function is called in an endless loop
void loop()
{
	display->setTime();
//	display->setTemperature();
	delay(DELAYTIME_BASE);

	if(TO_ACTUALISE(refresh,TOGGLE_TIME_DISPLAY))
	{
		display->setTemperature();
	}

	if(!setOff())
	{
		if(!setServiceMode())
		{
			float celsius = display->getWaterTemperature();
			heater->setHeaterOnOff(celsius);

			if(TO_ACTUALISE(refresh,ACTUALISE_LIGHT_MULTiPLIER))
			{
				light->setLighOnOff();
				pump->setPumpOn();
			}
		}
	}
	refresh = refresh+1;

	if(refresh> REFRESHVARIABLE_MAX)
	{
		refresh = 0;
	}

	dateTime->getTimeDiff(rtc.getTime());

	if(TO_ACTUALISE(refresh,ACTUALISE_NTC_MULTIPLIER))
	{
		Serial.print("actualise ");
		Serial.println(rtc.getTimeStr());


		if(dateTime->isNewSync())
		{
			int hours = dateTime->getHours();
			int minutes = dateTime->getMinutes();
			int seconds = dateTime->getSeconds();

			Serial.print("The new received UTC time is ");
			Serial.print(hours);
			Serial.print(":");
			Serial.print(minutes);
			Serial.print(":");
			Serial.println(seconds);
			rtc.setTime(hours,minutes,seconds);
		}
	}



/*	sendNTPpacket(timeServer); // send an NTP packet to a time server

	delay(100);
	//  if (Udp.parsePacket()) {
	    // We've received a packet, read the data from it
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
	    Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
	    Serial.print(':');
	    if (((epoch % 3600) / 60) < 10) {
	      // In the first 10 minutes of each hour, we'll want a leading '0'
	      Serial.print('0');
	    }
	    Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
	    Serial.print(':');
	    if ((epoch % 60) < 10) {
	      // In the first 10 seconds of each minute, we'll want a leading '0'
	      Serial.print('0');
	    }
	    Serial.println(epoch % 60); // print the second
	    }
	//  }
	  // wait ten seconds before asking for the time again
	  delay(3000);
	  Udp.parsePacket();
	  Ethernet.maintain();*/
}


bool setServiceMode()
{
	bool retVal=false;

	if(digitalRead(SERVICEBUTTON)==ACTIVE)  //switch on
	{
		Serial.println("ServiceMode set");
		light->setLightOn();
		pump->setPumpOff();
		heater->setHeaterOff();
		retVal=true;
	}
	return retVal;
}

bool setOff()
{
	bool retVal = false;
	if(digitalRead(ONOFFBUTTON)==ACTIVE) // Switch on
	{
		light->setLightOff();
		pump->setPumpOff();
		heater->setHeaterOff();
		retVal=true;
	}
	return retVal;
}





