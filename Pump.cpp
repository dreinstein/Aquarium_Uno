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

}

Pump::~Pump() {
	// TODO Auto-generated destructor stub
}

void Pump::setPumpOn()
{
	digitalWrite(RELAIS3,ACTIVE);
//	Serial.println("Pump On");

}

void Pump::setPumpOff()
{
	digitalWrite(RELAIS3,INACTIVE);
//	Serial.println("Pump Off");
}

