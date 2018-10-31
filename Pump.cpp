/*
 * Pump.cpp
 *
 *  Created on: 28.05.2017
 *      Author: Udo
 */

#include "Pump.h"
#include "Definitions.h"
#include "arduino.h"

Pump::Pump() {
	// TODO Auto-generated constructor stub
	status = PUMP_STATUS::PUMP_OFF;
}

Pump::~Pump() {
	// TODO Auto-generated destructor stub
}

void Pump::setPumpOn()
{
	digitalWrite(RELAIS3,ACTIVE);
	status = PUMP_STATUS::PUMP_ON;
	Serial.println("Pump On");

}

void Pump::setPumpOff()
{
	digitalWrite(RELAIS3,INACTIVE);
	status = PUMP_STATUS::PUMP_OFF;
	Serial.println("Pump Off");
}

String Pump::getStatus()
{
	if(status == PUMP_STATUS::PUMP_ON)
	{
		return "on";
	}
	else
	{
		return "off";
	}

}

