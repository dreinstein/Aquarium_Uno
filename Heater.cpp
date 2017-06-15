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

}

Heater::~Heater() {
	// TODO Auto-generated destructor stub
}

void Heater::setHeaterOnOff(float temperature)
{
	if(temperature > WATERTEMP_HEATEROFF)
	{
		setHeaterOff();
	}
	else
	{
		setHeaterOn();
	}
}

void Heater::setHeaterOn()
{
	Serial.println("Heater On");
	digitalWrite(RELAIS4,ACTIVE);
}

void Heater::setHeaterOff()
{
	Serial.println("Heater Off");
	digitalWrite(RELAIS4,INACTIVE);
}

