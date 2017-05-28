/*
 * Display.cpp
 *
 *  Created on: 27.05.2017
 *      Author: Udo
 */

#include "Display.h"
#include "Definitions.h"
#include "Arduino.h"



Display::Display(DallasTemperature *_tempSensor, LiquidCrystal  *_lcd, DS3231  *_rtc)
{
	tempSensors = _tempSensor;
	lcd = _lcd;
	rtc = _rtc;
	displayStatus = TEMPERATUR_DISPLAY_STATUS::WATERTEMP_OFF;
}

Display::~Display()
{

}

void Display::setTemperature()
{
	TEMPERATUR_DISPLAY_STATUS displayValue = isSwitchTemperatureDisplay();
	if(displayValue == TEMPERATUR_DISPLAY_STATUS::WATERTEMP_ON)
	{
		float celsius = getWaterTemperature();
		if((celsius > WATERTEMPERATUR_VALIDMINVALUE) && (celsius < WATERTEMPERATUR_VALIDMAXVALUE))
		{
			Serial.println("Temperatur Status on");
			setWaterTemp(celsius);
		}
		else
		{
			Serial.println("read temperature error");
		}
	}
	else if(displayValue == TEMPERATUR_DISPLAY_STATUS::WATERTEMP_OFF)
	{
		Serial.println("Temperatur Status off");
		setAirTemp();
	}
}


void Display::setWaterTemp(float temp)
{
	lcd->setCursor(CURSERPOSTEMPSTRING,0);
	lcd->print(stringTempValueWater);
	lcd->setCursor(CURSERPOSTEMPVALUE,0);
	lcd->print(temp);
	lcd->setCursor(CURSERPOSCSTRING, 0);
	lcd->print("C");
}


void Display::setTime()
{
	lcd->setCursor(0, 1);
	lcd->print(rtc->getDOWStr(FORMAT_SHORT));
	lcd->setCursor(8, 1);
	lcd->print(rtc->getTimeStr());
//	Serial.print("Time:   ");
//	Serial.print(rtc.getTimeStr());
//	Serial.print("\n");
}



TEMPERATUR_DISPLAY_STATUS Display::isSwitchTemperatureDisplay()
{
	if(displayStatus==TEMPERATUR_DISPLAY_STATUS::WATERTEMP_OFF)
	{
		displayStatus = TEMPERATUR_DISPLAY_STATUS::WATERTEMP_ON;
		return displayStatus;
	}
	else
	{
		Serial.println("switch to AirTemp");
		displayStatus = TEMPERATUR_DISPLAY_STATUS::WATERTEMP_OFF;
		return displayStatus;
	}
	return  TEMPERATUR_DISPLAY_STATUS::WATERTEMP_NOCHANGE;
}



float Display::getWaterTemperature()
{
	tempSensors->requestTemperatures();
	Serial.print("     Temperature is: ");
	float celsius=tempSensors->getTempCByIndex(0);
	Serial.println(celsius);
	return celsius;
}


void Display::setAirTemp()
{
	lcd->setCursor(CURSERPOSTEMPSTRING,0);
	lcd->clear();
	lcd->print(stringTempValueAir);
	lcd->setCursor(CURSERPOSTEMPVALUE,0);
	lcd->print(rtc->getTemp());
	lcd->setCursor(CURSERPOSCSTRING, 0);
	lcd->print("C");
}


