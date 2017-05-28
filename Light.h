/*
 * Light.h
 *
 *  Created on: 28.05.2017
 *      Author: Udo
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <ds3231.h>

// fixed Timesettings for overweek and weekend
#define TIMELIGHTON_OVERWEEK   "23:58:10"
#define TIMELIGHTOFF_OVERWEEK  "00:00:40"
#define TIMELIGHTON_WEEKEND    "09:35:40"
#define TIMELIGHTOFF_WEEKEND   "19:35:50"


// stati for light
enum class LIGHT_STATUS
{
	LIGHT_ON=0,
	LIGHT_OFF,
	LIGHT_NOCHANGE
};


class Light {
public:
	Light(DS3231  *_rtc);
	virtual ~Light();
	void setLighOnOff();
	void setLightOn();
	void setLightOff();
private:
	LIGHT_STATUS isLightOn();
	bool isWeekend();
	DS3231  *rtc;

	const char* saturday = "Sat";
	const char*  sunday =  "Sun";
};

#endif /* LIGHT_H_ */
