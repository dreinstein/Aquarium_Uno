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
	if((temperature >WATERTEMPERATUR_VALIDMAXVALUE) || (temperature < WATERTEMPERATUR_VALIDMINVALUE))
	{
		setHeaterOn();
		return;
	}

	if(temperature > WATERTEMP_HEATEROFF)
	{
		setHeaterOff();
	}
	else if(temperature <= WATERTEMP_HEATERON)
	{
		setHeaterOn();
	}
	else
	{
		setHeaterOn();
	}
}

void Heater::setHeaterOn()
{
	digitalWrite(RELAIS4,ACTIVE);
}

void Heater::setHeaterOff()
{
	digitalWrite(RELAIS4,INACTIVE);
}

