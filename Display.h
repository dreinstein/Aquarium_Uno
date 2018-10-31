/*
 * Temperature.h
 *
 *  Created on: 27.05.2017
 *      Author: Udo
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <DallasTemperature.h>
//#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <ds3231.h>


// stati for temperatur
enum class TEMPERATUR_DISPLAY_STATUS
{
	WATERTEMP_ON=0,
	WATERTEMP_OFF,
	WATERTEMP_NOCHANGE
};




class Display {
public:
	Display (DallasTemperature *_tempSensor,LiquidCrystal_I2C *_lcd, DS3231  *_rtc );
	//Display (DallasTemperature *_tempSensor,LiquidCrystal *_lcd, DS3231  *_rtc );
	Display();
	virtual ~Display();
	void setTemperature();
	float getWaterTemperature();
	void setTime();
private:
	bool isWeekend();
	void setAirTemp();
	void setWaterTemp(float temp);
	TEMPERATUR_DISPLAY_STATUS isSwitchTemperatureDisplay();

	TEMPERATUR_DISPLAY_STATUS displayStatus;
	DallasTemperature *tempSensors;
	LiquidCrystal_I2C *lcd;
	//LiquidCrystal *lcd;
	DS3231  *rtc;

	// strings for lcd
	const char*  stringTempValueWater =   "Wasser:  ";
	const char* stringTempValueAir =     "Luft";
};

#endif /* DISPLAY_H_ */
