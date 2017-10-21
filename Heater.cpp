/*
 * Heater.cpp
 *
 *  Created on: 28.05.2017
 *      Author: Udo
 */

#include "Heater.h"
#include "Arduino.h"
#include "Definitions.h"

Heater::Heater() {
	// TODO Auto-generated constructor stub
	setHeaterOn();

}

Heater::~Heater() {
	// TODO Auto-generated destructor stub
}

void Heater::setHeaterOnOff(float temperature)
{
	if(heaterStatus == HEATER_STATUS::HEATER_OFF)
	{
		if(temperature < WATERTEMP_HEATERON)
		{
			setHeaterOn();
		}
	}
	else if(heaterStatus == HEATER_STATUS::HEATER_ON)
	{
		if(temperature >= WATERTEMP_HEATEROFF)
		{
			setHeaterOff();
		}
	}
}

void Heater::setHeaterOn()
{
	Serial.println("Heater On");
	heaterStatus = HEATER_STATUS::HEATER_ON;
	digitalWrite(RELAIS4,ACTIVE);
}

void Heater::setHeaterOff()
{
	Serial.println("Heater Off");
	heaterStatus = HEATER_STATUS::HEATER_OFF;
	digitalWrite(RELAIS4,INACTIVE);
}

