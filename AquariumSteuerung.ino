

#include "Arduino.h"
#include <LiquidCrystal.h> //LCD-Bibliothek laden
#include <OneWire.h>
#include <ds3231.h>
#include "DallasTemperature\DallasTemperature.h"
#include "Definitions.h"
#include "Display.h"
#include "Light.h"
#include "Heater.h"
#include "Pump.h"

long refresh=0;


// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
OneWire  ds(TEMPSENSOR);
DallasTemperature sensors(&ds);
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D0, LCD_D1, LCD_D2, LCD_D3);

// functionDeclaration
bool setServiceMode();
bool setOff();

class Display *display;
class Light *light;
class Heater *heater;
class Pump *pump;


void setup()
{
// Add your initialization code here

	display = new Display(&sensors,&lcd,&rtc);
	light = new Light(&rtc);
	heater = new Heater();
	pump = new Pump();


	pinMode(RELAIS2,OUTPUT);
	pinMode(RELAIS3,OUTPUT);
	pinMode(RELAIS4,OUTPUT);
	pinMode(SERVICEBUTTON,INPUT);
	pinMode(ONOFFBUTTON,INPUT);

	lcd.begin(16, 2);
	rtc.begin();
	sensors.begin();
	sensors.setResolution(TEMP_RESOLUTION);
	Serial.begin(9600);
	refresh = 0;

	// for Test
	digitalWrite(SERVICEBUTTON,LOW);
	digitalWrite(ONOFFBUTTON,LOW);
	rtc.setDate(25,04,2017);
	rtc.setDOW(2);
	rtc.setTime(23,57,50);

}


// The loop function is called in an endless loop
void loop()
{
	display->setTime();
	delay(DELAYTIME_BASE);
	if(TO_ACTUALISE(refresh,TOGGLE_TIME_DISPLAY))
	{
		Serial.print("toggle Temperatur");
		display->setTemperature();
	}
	if(!setOff())
	{
		if(!setServiceMode())
		{
			float celsius = display->getWaterTemperature();
			heater->setHeaterOnOff(celsius);
			pump->setPumpOn();
		}
		if(TO_ACTUALISE(refresh,ACTUALISE_LIGHT_MULTiPLIER))
		{
			light->setLighOnOff();
		}
	}
	refresh = refresh+1;

	if(refresh> REFRESHVARIABLE_MAX)
	{
		refresh = 0;
	}
	//lcd.setCursor(0,0);
	//lcd.print("123456787899000");

}


bool setServiceMode()
{
	bool retVal=false;
	if(digitalRead(SERVICEBUTTON)==ACTIVE)  //switch on
	{
		light->setLighOnOff();
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




