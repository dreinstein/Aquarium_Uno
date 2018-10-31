/*
 * Heater.h
 *
 *  Created on: 28.05.2017
 *      Author: Udo
 */

#include <ds3231.h>

#ifndef HEATER_H_
#define HEATER_H_

#define WATERTEMP_HEATEROFF    31
#define WATERTEMP_HEATERON     29

// stati for light
enum class HEATER_STATUS
{
	HEATER_ON=0,
	HEATER_OFF
};


class Heater {
private:
	HEATER_STATUS heaterStatus;
public:
	Heater();
	virtual ~Heater();
	void setHeaterOnOff(float temperature);
	void setHeaterOn();
	void setHeaterOff();
	String getStatus();
};

#endif /* HEATER_H_ */
