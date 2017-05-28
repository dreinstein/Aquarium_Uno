/*
 * Heater.h
 *
 *  Created on: 28.05.2017
 *      Author: Udo
 */

#ifndef HEATER_H_
#define HEATER_H_


#define WATERTEMP_HEATEROFF    25
#define WATERTEMP_HEATERON     20




class Heater {
public:
	Heater();
	virtual ~Heater();
	void setHeaterOnOff(float temperature);
	void setHeaterOn();
	void setHeaterOff();
};

#endif /* HEATER_H_ */
