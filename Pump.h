/*
 * Pump.h
 *
 *  Created on: 28.05.2017
 *      Author: Udo
 */

#ifndef PUMP_H_
#define PUMP_H_

#include <ds3231.h>

enum class PUMP_STATUS
{
	PUMP_OFF = 0,
	PUMP_ON  = 1
};

class Pump {
private:
	PUMP_STATUS status;
public:
	Pump();
	virtual ~Pump();
	void setPumpOn();
	void setPumpOff();
	String getStatus();
};

#endif /* PUMP_H_ */
