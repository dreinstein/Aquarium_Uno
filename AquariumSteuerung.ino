#include "Arduino.h"
#include <LiquidCrystal.h> //LCD-Bibliothek laden
#include <OneWire.h>
#include <ds3231.h>

#include "DallasTemperature\DallasTemperature.h"

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

//The setup function is called once at startup of the sketch


// IN/OUT
#define RELAIS2       9     //LIGHT  //OUT
#define RELAIS3       10     //PUMP  //OUT
#define RELAIS4       11     //HEATER //OUT
#define TEMPSENSOR    8	    //TempSensor  //IN
#define SERVICEBUTTON 7     //ServiceButton  //IN
#define ONOFFBUTTON   6    //ONOFFBUTTON     //IN


#define CURSERPOSTEMPSTRING  0
#define CURSERPOSTEMPVALUE   8
#define CURSERPOSCSTRING     14
#define MAXSEC				 59
#define DISPLAYTOGGLETIME    20
#define TEMP_RESOLUTION      12

#define TIMELIGHTON_OVERWEEK   "23:58:10";
#define TIMELIGHTOFF_OVERWEEK  "23:59:03";
#define TIMELIGHTON_WEEKEND    "09:35:40";
#define TIMELIGHTOFF_WEEKEND   "19:35:50";

#define WATERTEMP_HEATEROFF    25
#define WATERTEMP_HEATERON     20


#define WATERTEMPERATUR_VALIDMAXVALUE  40
#define WATERTEMPERATUR_VALIDMINVALUE  10


#define ACTIVE          HIGH
#define INACTIVE        LOW

const long REFRESHVARIABLE_MAX  = 80000;

#define DELAYTIME_BASE		  		200
#define ACTUALISE_LIGHT_MULTiPLIER  20
#define ACTUALISE_TIME_MULTIPLIER   400
#define ACTUALISE_PUMP_MULTIPLIER   2000
long refreshVariable=0;


const char* stringBadTempValue = "Temperaturfehler";
const char* stringTempValueWater = "Wasser:  ";
const char* stringTempValueAir   = "Luft";
const char* saturday = "Sat";
const char* sunday = "Sun";

bool waterTempDisplayActive = false;
bool secOverflowFlag = false;

long unixOnTime;
long unixOffTime;

enum LIGHSTATUS
{
	ON=0,
	OFF,
	NOCHANGE
};


OneWire  ds(TEMPSENSOR);
DallasTemperature sensors(&ds);
LiquidCrystal lcd(12, 13, 5, 4, 3, 2);

Time timeToggleTempDisplay;


// functionDeclaration
bool isWeekend();
void setDisplayToggleValues();
void setAirTemp();
void setWaterTemp(float temp);
bool isSwitchTemperatureDisplay();
void setTemperature();
void setTime();
void setLighOnOff();
int isLightOn();
bool setServiceMode();
bool setOff();
void setHeaterOnOff();
float getWaterTemperature();
void setPumpOn();


void setup()
{
// Add your initialization code here
	pinMode(RELAIS2,OUTPUT);
	pinMode(RELAIS3,OUTPUT);
	pinMode(RELAIS4,OUTPUT);
	pinMode(SERVICEBUTTON,INPUT);
	pinMode(ONOFFBUTTON,INPUT);

	lcd.begin(16, 2);
	rtc.begin();
	sensors.begin();
	sensors.setResolution(TEMP_RESOLUTION);
	Serial.begin(9600);

	setAirTemp();

	digitalWrite(SERVICEBUTTON,LOW);
	digitalWrite(ONOFFBUTTON,LOW);

	rtc.setDate(25,04,2017);
	rtc.setDOW(2);
	rtc.setTime(23,57,50);
	refreshVariable = 0;

}

// The loop function is called in an endless loop
void loop()
{
	setTime();
	delay(DELAYTIME_BASE);
	setTemperature();
	if(!setOff())
	{
		if(!setServiceMode())
		{
			setHeaterOnOff();
			setPumpOn();
		}
		setLighOnOff();
	}
	refreshVariable = refreshVariable+1;

	if(refreshVariable > REFRESHVARIABLE_MAX)
	{
		refreshVariable = 0;
	}
}

bool isSwitchTemperatureDisplay()
{
	Time actTime = rtc.getTime();

	if(secOverflowFlag && actTime.sec > DISPLAYTOGGLETIME)
	{
		return false;
	}

	if(actTime.sec >= timeToggleTempDisplay.sec)
	{
		return true;
	}
	return false;
}


void setTemperature()
{

	  float celsius = getWaterTemperature();
	  if(!waterTempDisplayActive && isSwitchTemperatureDisplay())
	  {
		  waterTempDisplayActive = true;
		  if((celsius > WATERTEMPERATUR_VALIDMINVALUE) && (celsius < WATERTEMPERATUR_VALIDMAXVALUE))
		  {
			  setWaterTemp(celsius);
		  }
	  }
	  else if(waterTempDisplayActive && isSwitchTemperatureDisplay())
	  {
		  waterTempDisplayActive = false;
		  setAirTemp();
	  }
}

float getWaterTemperature()
{
	sensors.requestTemperatures();
//	float airtemp = rtc.getTemp();
//	Serial.print("air temp is: ");
//	Serial.print(airtemp);
	Serial.print("     Temperature is: ");
	float celsius=sensors.getTempCByIndex(0);
	Serial.println(celsius);
	return celsius;
}


void setTime()
{
	lcd.setCursor(0, 1);
	lcd.print(rtc.getDOWStr(FORMAT_SHORT));
	lcd.setCursor(8, 1);
	lcd.print(rtc.getTimeStr());
//	Serial.print("Time:   ");
//	Serial.print(rtc.getTimeStr());
//	Serial.print("\n");
}

void setLighOnOff()
{
	if(isLightOn() == LIGHSTATUS::ON)
	{
		Serial.print("Light On\n");
		digitalWrite(RELAIS2,ACTIVE);
	}
	else if(isLightOn() == LIGHSTATUS::OFF)
	{
		Serial.print("Light off\n");
		digitalWrite(RELAIS2,INACTIVE);
	}

}



int isLightOn()
{

	if(((refreshVariable*DELAYTIME_BASE) % ACTUALISE_LIGHT_MULTiPLIER) != 0 )
	{
		return LIGHSTATUS::NOCHANGE;
	}


	char* timeLightOn;
	char* timeLightOff;

	if(isWeekend())
	{
		timeLightOn = (char*)TIMELIGHTON_WEEKEND;
		timeLightOff = (char*)TIMELIGHTOFF_WEEKEND;
		//		Serial.print("TimelineOff    ");
			//	Serial.println(timeLightOff);

	}
	else
	{
		timeLightOn = (char*)TIMELIGHTON_OVERWEEK;
		timeLightOff = (char*)TIMELIGHTOFF_OVERWEEK;
	}

	char *onhour;
	char *onmin;
	char *onsec;
	char *offhour;
	char *offmin;
	char *offsec;

	onhour = timeLightOn;
	offhour = timeLightOff;
	onmin = timeLightOn+3;
	offmin = timeLightOff+3;
	onsec = timeLightOn+6;
	offsec = timeLightOff+6;
	uint8_t intOnHour = atoi(onhour);
	uint8_t intOffHour = atoi(offhour);
	uint8_t intOnMinute = atoi(onmin);
	uint8_t intOffMinute = atoi(offmin);
	uint8_t intOnSecond = atoi(onsec);
	uint8_t intOffSecond = atoi(offsec);

	Time lightOn;
	lightOn.date = rtc.getTime().date;
	lightOn.year = rtc.getTime().year;
	lightOn.mon = rtc.getTime().mon;
	lightOn.dow = rtc.getTime().dow;
	lightOn.hour = intOnHour;
	lightOn.min = intOnMinute;
	lightOn.sec = intOnSecond;

	unixOnTime = rtc.getUnixTime(lightOn);
	Serial.print("unixOnTime:  ");
	Serial.println(unixOnTime);

	Time lightOff;
	lightOff.date = rtc.getTime().date;
	lightOff.year = rtc.getTime().year;
	lightOff.mon = rtc.getTime().mon;
	lightOff.dow = rtc.getTime().dow;
	lightOff.hour = intOffHour;
	lightOff.min = intOffMinute;
	lightOff.sec = intOffSecond;

	unixOffTime= rtc.getUnixTime(lightOff);
	Serial.print("unixOffTime:  ");
	Serial.println(unixOffTime);

	long unixActualTime = rtc.getUnixTime(rtc.getTime());

	// before 0:00, set offtime to next day
	if((unixOnTime > unixOffTime ) && (unixActualTime > unixOnTime))
	{
		lightOff.date = rtc.getTime().date+1;
		lightOff.hour = intOffHour;
		lightOff.min = intOffMinute;
		lightOff.sec = intOffSecond;
		unixOffTime = rtc.getUnixTime(lightOff);
		Serial.print("unixoffTime + 1 Day   ");
		Serial.println(unixOffTime);
	}

	// if offtime next day
	//after 0:00, set ontime one day before
	if((unixOnTime > unixOffTime) && (unixActualTime < unixOffTime))
	{
		lightOn.date = rtc.getTime().date-1;
		lightOn.hour = intOnHour;
		lightOn.min = intOnMinute;
		lightOn.sec = intOnSecond;
		unixOnTime = rtc.getUnixTime(lightOn);
		Serial.print("unixonTime - 1 Day   ");
		Serial.println(unixOnTime);
	}



	if(unixActualTime > unixOffTime)
	{
		return LIGHSTATUS::OFF;
	}
	else if(unixActualTime > unixOnTime)
	{
		return LIGHSTATUS::ON;
	}

	return LIGHSTATUS::OFF;
}






void setAirTemp()
{
	lcd.setCursor(CURSERPOSTEMPSTRING,0);
	lcd.clear();
	lcd.print(stringTempValueAir);
	lcd.setCursor(CURSERPOSTEMPVALUE,0);
	lcd.print(rtc.getTemp());
	lcd.setCursor(CURSERPOSCSTRING, 0);
	lcd.print("C");
}


void setWaterTemp(float temp)
{
	lcd.setCursor(CURSERPOSTEMPSTRING,0);
	lcd.print(stringTempValueWater);
	lcd.setCursor(CURSERPOSTEMPVALUE,0);
	lcd.print(temp);
	lcd.setCursor(CURSERPOSCSTRING, 0);
	lcd.print("C");
}


bool isWeekend()
{
	char* dayOfWeek = rtc.getDOWStr(FORMAT_SHORT);
	if((dayOfWeek == saturday) || (dayOfWeek == sunday))
	{
		return true;
	}
	return false;
}


bool setServiceMode()
{
	int val = digitalRead(SERVICEBUTTON);
	bool retVal=false;
	if(val==ACTIVE)  //switch on
	{
		if(isLightOn())
		{
			digitalWrite(RELAIS2,ACTIVE);  // Light ON
		}
		digitalWrite(RELAIS3,INACTIVE); //Pump out
		digitalWrite( RELAIS4,INACTIVE); // Heater out
		retVal=true;
	}
	else
	{
		//digitalWrite(RELAIS2,ACTIVE);  // Light ON
		//digitalWrite(RELAIS3,ACTIVE); //Pump ON
		//digitalWrite( RELAIS4,ACTIVE); // Heater ON
	}
	return retVal;
}

bool setOff()
{
	int val = digitalRead(ONOFFBUTTON);
	bool retVal = false;
	if(val==ACTIVE) // Switch on
	{
		digitalWrite(RELAIS2,INACTIVE);  // Light off
		digitalWrite(RELAIS3,INACTIVE); //Pump out
		digitalWrite( RELAIS4,INACTIVE); // Heater out
		retVal=true;
	}
	else
	{
		//digitalWrite(RELAIS2,ACTIVE);  // Light out
		//digitalWrite(RELAIS3,ACTIVE); //Pump out
		//digitalWrite( RELAIS4,ACTIVE); // Heater out
	}
	return retVal;
}

void setHeaterOnOff()
{
	float celsius = getWaterTemperature();
	if((celsius >WATERTEMPERATUR_VALIDMAXVALUE) || (celsius < WATERTEMPERATUR_VALIDMINVALUE))
	{
		return;
	}

	if(celsius > WATERTEMP_HEATEROFF)
	{
		digitalWrite(RELAIS4,INACTIVE);
		//Serial.print("Heater offn\n");
	}
	else if(celsius <= WATERTEMP_HEATERON)
	{
		digitalWrite(RELAIS4,ACTIVE);
		//Serial.print("Heater on\n");
	}
	else
	{
		digitalWrite(RELAIS4,ACTIVE);
		//Serial.print("Heater on (else)\n");
	}
}

void setPumpOn()
{
	digitalWrite(RELAIS3,ACTIVE);
//	Serial.print("Pump is on\n");
}




