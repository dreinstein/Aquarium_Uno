/*
 * Light.cpp
 *
 *  Created on: 28.05.2017
 *      Author: Udo
 */

#include "Light.h"
#include "Arduino.h"
#include "Definitions.h"


Light::Light(DS3231  *_rtc) {
	// TODO Auto-generated constructor stub
	rtc = _rtc;

}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

void Light::setLighOnOff()
{
	if(isLightOn() == LIGHT_STATUS::LIGHT_ON)
	{
		setLightOn();
	}
	else if(isLightOn() == LIGHT_STATUS::LIGHT_OFF)
	{
		setLightOff();
	}
	else //
	{
		// nothing to do
	}
}


void Light::setLightOn()
{
	Serial.print("Light On\n");
	digitalWrite(RELAIS2,ACTIVE);
}

void Light::setLightOff()
{
	Serial.print("Light Off\n");
	digitalWrite(RELAIS2,INACTIVE);
}


LIGHT_STATUS Light::isLightOn()
{

	long unixOnTime = 0;
	long unixOffTime = 0;
	char* timeLightOn;
	char* timeLightOff;

	if(isWeekend())
	{
		timeLightOn = (char*)TIMELIGHTON_WEEKEND;
		timeLightOff = (char*)TIMELIGHTOFF_WEEKEND;
		//		Serial.print("TimelineOff    ");
			//	Serial.println(timeLightOff);

	}
	else
	{
		timeLightOn = (char*)TIMELIGHTON_OVERWEEK;
		timeLightOff = (char*)TIMELIGHTOFF_OVERWEEK;
	}

	char *onhour;
	char *onmin;
	char *onsec;
	char *offhour;
	char *offmin;
	char *offsec;

	onhour = timeLightOn;
	offhour = timeLightOff;
	onmin = timeLightOn+3;
	offmin = timeLightOff+3;
	onsec = timeLightOn+6;
	offsec = timeLightOff+6;
	uint8_t intOnHour = atoi(onhour);
	uint8_t intOffHour = atoi(offhour);
	uint8_t intOnMinute = atoi(onmin);
	uint8_t intOffMinute = atoi(offmin);
	uint8_t intOnSecond = atoi(onsec);
	uint8_t intOffSecond = atoi(offsec);

	Time lightOn;
	lightOn.date = rtc->getTime().date;
	lightOn.year = rtc->getTime().year;
	lightOn.mon = rtc->getTime().mon;
	lightOn.dow = rtc->getTime().dow;
	lightOn.hour = intOnHour;
	lightOn.min = intOnMinute;
	lightOn.sec = intOnSecond;

	unixOnTime = rtc->getUnixTime(lightOn);
	Serial.print("unixOnTime:  ");
	Serial.println(unixOnTime);

	Time lightOff;
	lightOff.date = rtc->getTime().date;
	lightOff.year = rtc->getTime().year;
	lightOff.mon = rtc->getTime().mon;
	lightOff.dow = rtc->getTime().dow;
	lightOff.hour = intOffHour;
	lightOff.min = intOffMinute;
	lightOff.sec = intOffSecond;

	unixOffTime= rtc->getUnixTime(lightOff);
	Serial.print("unixOffTime:  ");
	Serial.println(unixOffTime);

	long unixActualTime = rtc->getUnixTime(rtc->getTime());

	// before 0:00, set offtime to next day
	if((unixOnTime > unixOffTime ) && (unixActualTime > unixOnTime))
	{
		lightOff.date = rtc->getTime().date+1;
		lightOff.hour = intOffHour;
		lightOff.min = intOffMinute;
		lightOff.sec = intOffSecond;
		unixOffTime = rtc->getUnixTime(lightOff);
		Serial.print("unixoffTime + 1 Day   ");
		Serial.println(unixOffTime);
	}

	// if offtime next day
	//after 0:00, set ontime one day before
	if((unixOnTime > unixOffTime) && (unixActualTime < unixOffTime))
	{
		lightOn.date = rtc->getTime().date-1;
		lightOn.hour = intOnHour;
		lightOn.min = intOnMinute;
		lightOn.sec = intOnSecond;
		unixOnTime = rtc->getUnixTime(lightOn);
		Serial.print("unixonTime - 1 Day   ");
		Serial.println(unixOnTime);
	}



	if(unixActualTime > unixOffTime)
	{
		return LIGHT_STATUS::LIGHT_OFF;
	}
	else if(unixActualTime > unixOnTime)
	{
		return LIGHT_STATUS::LIGHT_ON;
	}

	return LIGHT_STATUS::LIGHT_OFF;
}




bool Light::isWeekend()
{
	char* dayOfWeek = rtc->getDOWStr(FORMAT_SHORT);
	if((dayOfWeek == saturday) || (dayOfWeek == sunday))
	{
		return true;
	}
	return false;
}


