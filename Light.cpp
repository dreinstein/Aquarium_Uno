/*
 * Light.cpp
 *
 *  Created on: 28.05.2017
 *      Author: Udo
 */

#include "Light.h"

#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdlib.h>

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
		Serial.println("light on");
		setLightOn();
	}
	else if(isLightOn() == LIGHT_STATUS::LIGHT_OFF)
	{
		Serial.println("light off");
		setLightOff();
	}
	else //
	{
		// nothing to do
	}
}


void Light::setLightOn()
{
	Serial.println("Light On\n");
	digitalWrite(RELAIS2,ACTIVE);
}

void Light::setLightOff()
{
	Serial.println("Light Off\n");
	digitalWrite(RELAIS2,INACTIVE);
}

String Light::getStatus()
{
	if(isLightOn()== LIGHT_STATUS::LIGHT_ON)
	{
		return "on";
	}
	else
	{
		return "off";
	}

}



LIGHT_STATUS Light::isLightOn()
{

	long unixOnTime_first = 0;
	long unixOffTime_first = 0;
	long unixOnTime_second = 0;
	long unixOffTime_second = 0;
	char* timeLightOn_first;
	char* timeLightOff_first;
	char* timeLightOn_second;
	char* timeLightOff_second;


	if(isWeekend())
	{
		timeLightOn_first = (char*)TIMELIGHTON_FIRST_WEEKEND;
		timeLightOff_first = (char*)TIMELIGHTOFF_FIRST_WEEKEND;
		timeLightOn_second = (char*)TIMELIGHTON_SECOND_WEEKEND;
		timeLightOff_second = (char*)TIMELIGHTOFF_SECOND_WEEKEND;

		//		Serial.print("TimelineOff    ");
			//	Serial.println(timeLightOff);

	}
	else
	{
		timeLightOn_first = (char*)TIMELIGHTON_FIRST_OVERWEEK;
		timeLightOff_first = (char*)TIMELIGHTOFF_FIRST_OVERWEEK;
		timeLightOn_second = (char*)TIMELIGHTON_SECOND_OVERWEEK;
		timeLightOff_second = (char*)TIMELIGHTOFF_SECOND_OVERWEEK;
	}

	Time lightOn_first;
	lightOn_first.date = rtc->getTime().date;
	lightOn_first.year = rtc->getTime().year;
	lightOn_first.mon = rtc->getTime().mon;
	lightOn_first.dow = rtc->getTime().dow;
	lightOn_first.hour = atoi(timeLightOn_first);
	lightOn_first.min = atoi(timeLightOn_first+3);
	lightOn_first.sec = atoi(timeLightOn_first+6);
	unixOnTime_first = rtc->getUnixTime(lightOn_first);


	Time lightOff_first;
	lightOff_first.date = rtc->getTime().date;
	lightOff_first.year = rtc->getTime().year;
	lightOff_first.mon = rtc->getTime().mon;
	lightOff_first.dow = rtc->getTime().dow;
	lightOff_first.hour = atoi(timeLightOff_first);
	lightOff_first.min = atoi(timeLightOff_first+3);
	lightOff_first.sec = atoi(timeLightOff_first+6);
	unixOffTime_first= rtc->getUnixTime(lightOff_first);

	Time lightOn_second;
	lightOn_second.date = rtc->getTime().date;
	lightOn_second.year = rtc->getTime().year;
	lightOn_second.mon = rtc->getTime().mon;
	lightOn_second.dow = rtc->getTime().dow;
	lightOn_second.hour =  atoi(timeLightOn_second);
	lightOn_second.min = atoi(timeLightOn_second+3);
	lightOn_second.sec = atoi(timeLightOn_second+6);
	unixOnTime_second = rtc->getUnixTime(lightOn_second);


	Time lightOff_second;
	lightOff_second.date = rtc->getTime().date;
	lightOff_second.year = rtc->getTime().year;
	lightOff_second.mon = rtc->getTime().mon;
	lightOff_second.dow = rtc->getTime().dow;
	lightOff_second.hour = atoi(timeLightOff_second);
	lightOff_second.min = atoi(timeLightOff_second+3);
	lightOff_second.sec = atoi(timeLightOff_second+6);
	unixOffTime_second = rtc->getUnixTime(lightOff_second);


	long unixActualTime = rtc->getUnixTime(rtc->getTime());
	//Serial.println(rtc->getTimeStr(FORMAT_LONG));



	// before 0:00, set offtime to next day
/*	if((unixOnTime_first > unixOffTime_first ) && (unixActualTime > unixOnTime_first))
	{
		lightOff_first.date = rtc->getTime().date+1;
		lightOff_first.hour = intOffHour;
		lightOff_first.min = intOffMinute;
		lightOff_first.sec = intOffSecond;
		unixOffTime_first = rtc->getUnixTime(lightOff_first);
		Serial.print("unixoffTime + 1 Day   ");
		Serial.println(unixOffTime_first);
	}

	// if offtime next day
	//after 0:00, set ontime one day before
	if((unixOnTime_first > unixOffTime_first) && (unixActualTime < unixOffTime_first))
	{
		lightOn_first.date = rtc->getTime().date-1;
		lightOn_first.hour = intOnHour;
		lightOn_first.min = intOnMinute;
		lightOn_first.sec = intOnSecond;
		unixOnTime_first = rtc->getUnixTime(lightOn_first);
		Serial.print("unixonTime - 1 Day   ");
		Serial.println(unixOnTime_first);
	}*/

	if(unixActualTime > unixOffTime_second)
	{
		return LIGHT_STATUS::LIGHT_OFF;
	}
	else if(unixActualTime > unixOnTime_second)
	{
		return LIGHT_STATUS::LIGHT_ON;
	}

	else if(unixActualTime > unixOffTime_first)
	{
		return LIGHT_STATUS::LIGHT_OFF;
	}
	else if(unixActualTime > unixOnTime_first)
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


