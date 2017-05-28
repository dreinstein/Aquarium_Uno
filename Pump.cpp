/*
 * Pump.cpp
 *
 *  Created on: 28.05.2017
 *      Author: Udo
 */

#include "Pump.h"
#include "Definitions.h"

Pump::Pump() {
	// TODO Auto-generated constructor stub

}

Pump::~Pump() {
	// TODO Auto-generated destructor stub
}

void Pump::setPumpOn()
{
	digitalWrite(RELAIS3,ACTIVE);
}

void Pump::setPumpOff()
{
	digitalWrite(RELAIS3,INACTIVE);
}

