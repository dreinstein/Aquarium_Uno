

#include "Arduino.h"
#include <LiquidCrystal.h> //LCD-Bibliothek laden
#include <OneWire.h>
#include <ds3231.h>
#include "DallasTemperature\DallasTemperature.h"
#include "LiquidCrystal_I2C-1.1.2\LiquidCrystal_I2C.h"
#include "Definitions.h"
#include "Display.h"
#include "Light.h"
#include "Heater.h"
#include "Pump.h"

long refresh=0;


DS3231  rtc(SDA, SCL);
OneWire  ds(TEMPSENSOR);
DallasTemperature sensors(&ds);
LiquidCrystal_I2C lcd(0x27, 16, 2);


bool setServiceMode();
bool setOff();

class Display *display;
class Light *light;
class Heater *heater;
class Pump *pump;


void setup()
{
// Add your initialization code here

	Serial.println("Setup\n");
	display = new Display(&sensors,&lcd,&rtc);
	light = new Light(&rtc);
	heater = new Heater();
	pump = new Pump();


	pinMode(RELAIS2,OUTPUT);
	pinMode(RELAIS3,OUTPUT);
	pinMode(RELAIS4,OUTPUT);


	pinMode(SERVICEBUTTON,INPUT);
	pinMode(ONOFFBUTTON,INPUT);
	pinMode(TEMPSENSOR,INPUT);


	lcd.begin(16, 2);
	rtc.begin();
	sensors.begin();
	sensors.setResolution(TEMP_RESOLUTION);
	Serial.begin(9600);
	refresh = 0;

	//rtc.setDate(14,01,2018);
	//rtc.setDOW(7);
	//rtc.setTime(19,49,00);

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




