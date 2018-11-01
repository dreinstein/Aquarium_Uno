

#include "Arduino.h"
//#include "LiquidCrystal\LiquidCrystal.h" //LCD-Bibliothek laden
//#include <LiquidCrystal.h> //LCD-Bibliothek laden

#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#include <ds3231.h>
#include <Ethernet.h>
#include <SPI.h>
#include <DallasTemperature.h>
#include <EthernetUdp.h>

#include "Definitions.h"
#include "Display.h"
#include "Light.h"
#include "Heater.h"
#include "Pump.h"
#include "DateTime.h"


/*const String WINTER  = "winter";
const String SOMMER = "sommer";
const String SYNC = "sync";
const String SERVICE = "service";
const String TEMP = "temperature";
const String NORMAL = "normal";
//const String NO = "no";
const String DPIN1 = "pin1";
const String DPIN2 = "pin2";
const String DPIN3 = "pin3";
const String DPIN4 = "pin4";
const String DPIN5 = "pin5";
const String DPIN6 = "pin6";
const String DPIN7 = "pin7";     // Service
const String DPIN8 = "pin8";     // onOff
const String DPIN9 = "pin9";     //Light
const String DPIN10 = "pin10";   // Pump
const String DPIN11 = "pin11";   // Heater
const String DPIN12 = "pin12";
*/

long refresh=0;
bool serviceModeOn = false;


// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
OneWire  ds(TEMPSENSOR);
DallasTemperature sensors(&ds);
/// Belegung SDA, SCL
/// Arduino SDA = PinAnalog 4
///         SLC = Pin Analog 5

LiquidCrystal_I2C lcd(0x27,16,2);

// functionDeclaration
bool setServiceMode();
bool setOff();
bool connected;

class Display *display;
class Light *light;
class Heater *heater;
class Pump *pump;
class DateTime* dateTime;

bool synchronise();
//void sentToWebServer();

// assign a MAC address for the Ethernet controller.
// fill in your address here:


byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
// assign an IP address for the controller:
IPAddress ip(192, 168, 0, 22);
//IPAddress server(10, 0, 2, 15);
EthernetClient client;
EthernetServer eserver(23);
IPAddress server(184, 188, 16, 158);
IPAddress webServer(192, 168, 0, 2);
//void getCharFromEthernet();
String remoteString;



void setup()
{
// Add your initialization code here
	Serial.begin(9600);
	while (!Serial) {
		    ; // wait for serial port to connect. Needed for native USB port only
		  }
	Serial.println("Setup\n");
	lcd.init();
	rtc.begin();
	lcd.begin(16,2);
	lcd.backlight();
	connected = false;

	Serial.println("ready setup");
	rtc.begin();
	sensors.begin();
	sensors.setResolution(TEMP_RESOLUTION);


	refresh = 0;
	Serial.println("initialised");

	// start the Ethernet connection and the server:

	Ethernet.begin(mac, ip);
	Serial.begin(9600);
	while(!Serial)
	{;
	}
	delay(1000);
	eserver.begin();
/*	if (client.connect(server, 10002)) {
	    Serial.println("connected");
	}
	else
	{
		Serial.println("connection failed");
	}*/
	//client.connect(server,23);

	pinMode(RELAIS2,OUTPUT);
	pinMode(RELAIS3,OUTPUT);
	pinMode(RELAIS4,OUTPUT);

	pinMode(SERVICEBUTTON,INPUT_PULLUP);
	pinMode(ONOFFBUTTON,INPUT_PULLUP);
	pinMode(TEMPSENSOR,INPUT);


	display = new Display(&sensors,&lcd,&rtc);
	light = new Light(&rtc);
	heater = new Heater();
	pump = new Pump();
//	dateTime = new DateTime();

	//rtc.setDate(28,10,2018);
	//rtc.setDOW(6);
//	rtc.setTime(18,5,00);

	delay(1000);

	Serial.println("synchronise");
//	synchronise();
}


// The loop function is called in an endless loop
void loop()
{

	Serial.println("loop begin");
	//lcd.clear();
	//lcd.print(rtc.getTemp());
	delay(1000);
	//rtc.getDateStr();
//	Serial.print(rtc.getDateStr());

	display->setTime();
	display->setTemperature();


	delay(DELAYTIME_BASE);
//	Serial.println("loop begin");

	if(TO_ACTUALISE(refresh,TOGGLE_TIME_DISPLAY))
	{
		display->setTemperature();
	}

	if(!setOff())
	{
		if(!setServiceMode())
		{
		//	Serial.println("ServiceModeOff");

			float celsius = display->getWaterTemperature();
			//Serial.println("celsius");
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


/*	if(TO_ACTUALISE(refresh,ACTUALISE_NTC_MULTIPLIER))
	{
		synchronise();
	}*/

	//Serial.println("before reading char from telnet");


//	getCharFromEthernet();
//	sentToWebServer();
}

/*void sentToWebServer()
{
	client.connect(webServer, 80);
	if(client.connected()){
		Serial.println("WebClient connected");
		client.print("GET http://192.168.0.2/index.php?Time=");
		client.print(rtc.getTimeStr());
		Serial.println(rtc.getTimeStr());
	    client.print("&Temperatur=");
	    client.print(display->getWaterTemperature());
	    client.print("&Licht=");
	    client.print(light->getStatus());
	    client.print("&Pumpe=");
	    client.print(pump->getStatus());
	    client.print("&Heizung=");
	    client.print(heater->getStatus());
		client.println(" HTTP/1.0");
		client.println("Host: http://192.168.0.2");
		client.println();
	}
	client.stop();
}*/


/*void getCharFromEthernet()
{
	 client = eserver.available();
	 if (client.available()) {
		 Serial.println("client availible");
		    if (!connected) {
		      client.flush();
		      connected = true;
		    }

	    char c = client.read();
	    remoteString +=c;
	    remoteAction(remoteString);
	  }
	 else
	 {
		 Serial.println("client not availible");
	 }
	  // if the server's disconnected, stop the client:
	  if (!client.connected()) {
	    Serial.println();
	    client.stop();
	    remoteString = "";
	  }
}*/



/*void remoteAction(String rString)
{
	/* Verbindung mit Telnet Server
	 * 	 * telnet
	 * open 192.168.0.22
	 * warten
	 * winter - Winterzeit -1h
	 * sommer - Sommerzeit +1 h
	 * sync - mit Timeserver sychronisieren
	 * service - Servicemode einstellen, temperatur und pumpe aus, Licht an
	 * normal  - Normalmode einstellen, d.h SErviceMode zurückstellen, tempertur, pumpe,licht an (abhängig Uhrzeit)
	 */

/*	Serial.println(rString);
	int hour = rtc.getTime().hour;
	if(rString == WINTER)
	{
		hour = hour -1;
		rtc.setTime(hour,rtc.getTime().min,rtc.getTime().sec);
		Serial.println("set Wintertime");
		remoteString = "";

	}
	else if (rString == SOMMER)
	{
		hour = hour +1;
		rtc.setTime(hour,rtc.getTime().min,rtc.getTime().sec);
		Serial.println("set Summertime");
		remoteString = "";
	}
	else if(rString == SYNC)
	{
		synchronise();
	}
	else if(rString == SERVICE)
	{
		serviceModeOn = true;
	}
	else if(rString == NORMAL)
	{
		serviceModeOn = false;
	}
	else if(rString == TEMP)
	{
		sendTemperaturToClient();
	}
	else if(rString == DPIN1)
	{
		sendoutputPinState(1);
	}
	else if(rString == DPIN2)
	{
		sendoutputPinState(2);
	}
	else if(rString == DPIN3)
	{
		sendoutputPinState(3);
	}
	else if(rString == DPIN4)
	{
		sendoutputPinState(4);
	}
	else if(rString == DPIN5)
	{
		sendoutputPinState(5);
	}
	else if(rString == DPIN6)
	{
		sendoutputPinState(6);
	}
	else if(rString == DPIN7)
	{
		sendoutputPinState(7);
	}
	else if(rString == DPIN8)
	{
		sendoutputPinState(8);
	}
	else if(rString == DPIN9)
	{
		sendoutputPinState(9);
	}
	else if(rString == DPIN10)
	{
		sendoutputPinState(10);
	}
	else if(rString == DPIN11)
	{
		sendoutputPinState(11);
	}
	else if(rString == DPIN12)
	{
		sendoutputPinState(12);
	}
}*/



bool setServiceMode()
{
	bool retVal=false;

	if((digitalRead(SERVICEBUTTON)==INACTIVE) || serviceModeOn)  //switch on
	{
		//Serial.println("ServiceMode set");
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
	if(digitalRead(ONOFFBUTTON)==INACTIVE) // Switch on
	{
		light->setLightOff();
		pump->setPumpOff();
		heater->setHeaterOff();
		retVal=true;
	}
	return retVal;
}

/*bool synchronise()
{
	bool sync = false;
	//Serial.print("actualise ");
	Serial.println(rtc.getTimeStr());

	int i = 0;
	while(i< 10)
	{
		if(sync)
			break;


		if(dateTime->isNewSync())
		{
			//Serial.print("Have new Synchronisation ");
			int hours = dateTime->getHours();
			int minutes = dateTime->getMinutes();
			int seconds = dateTime->getSeconds();
			int diff = dateTime->getTimeDiff(rtc.getTime());
			hours = hours + diff;
			//Serial.print("set the time ");
			rtc.setTime(hours,minutes,seconds);

			//Serial.print("The new received UTC time is ");
			//Serial.print(hours);
			//Serial.print(":");
			//Serial.print(minutes);
			//Serial.print(":");
			//Serial.println(seconds);
			//rtc.setTime(hours,minutes,seconds);
			sync = true;
		}
	delay(500);
	i = i+1;
	}
	return sync;
}*/

/*void sendoutputPinState(int pin)
{
//  client = eserver.available();
  client.print("digital pin ");
  client.print(pin);
  client.print(" is ");
  if (digitalRead(pin)) {
    client.println("HIGH");
  }
  else
    client.println("LOW");
}*/

/*void sendTemperaturToClient()
{
//  client = eserver.available();
  client.print("Temperatur");
  client.print(" is ");
  client.print( display->getWaterTemperature());
}*/





