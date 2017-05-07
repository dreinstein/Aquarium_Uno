#include "Arduino.h"
#include <LiquidCrystal.h> //LCD-Bibliothek laden
#include <OneWire.h>
#include <ds3231.h>
#include "DallasTemperature\DallasTemperature.h"

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

//The setup function is called once at startup of the sketch


// IN/OUT
#define RELAIS2       9     //LIGHT
#define RELAIS3       10     //PUMP
#define RELAIS4       11     //HEATER
#define TEMPSENSOR    8	    //TempSensor
#define SERVICEBUTTON 7     //ServiceButton
#define ONOFFBUTTON   12    //ONOFFBUTTON


#define CURSERPOSTEMPSTRING  0
#define CURSERPOSTEMPVALUE   8
#define CURSERPOSCSTRING     14
#define MAXSEC				 59
#define DISPLAYTOGGLETIME    20
#define TEMP_RESOLUTION      12

#define TIMELIGHTON_OVERWEEK   "07:30:00";
#define TIMELIGHTOFF_OVERWEEK  "22:00:00";
#define TIMELIGHTON_WEEKEND    "19:35:40";
#define TIMELIGHTOFF_WEEKEND   "19:35:50";


const char* stringBadTempValue = "Temperaturfehler";
const char* stringTempValueWater = "Wasser:  ";
const char* stringTempValueAir   = "Luft";
const char* saturday = "Sat";
const char* sunday = "Sun";

bool waterTempDisplayActive = false;
bool secOverflowFlag = false;


OneWire  ds(TEMPSENSOR);
DallasTemperature sensors(&ds);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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
bool isLightOn();
void setServiceMode();
bool setOff();



void setup()
{
// Add your initialization code here
	//pinMode(relais1,OUTPUT);
	pinMode(RELAIS2,OUTPUT);
	pinMode(RELAIS3,OUTPUT);
	pinMode(RELAIS4,OUTPUT);
	pinMode(SERVICEBUTTON,INPUT);
	pinMode(ONOFFBUTTON,INPUT);

	lcd.begin(16, 2);
	rtc.begin();
	sensors.begin();
	sensors.setResolution(TEMP_RESOLUTION);

	void setOff();

	Serial.begin(9600);


	setAirTemp();
	setDisplayToggleValues();
	/*rtc.setDate(30,04,2017);
	rtc.setDOW(7);
	rtc.setTime(19,47,50);*/
}

// The loop function is called in an endless loop
void loop()
{
	setTime();
	delay(400);
	setTemperature();
	if(!setOff())
	{
		setLighOnOff();
		setServiceMode();
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

	  sensors.requestTemperatures();
	  float airtemp = rtc.getTemp();
	  Serial.print("air temp is: ");
	  Serial.print(airtemp);
	  Serial.print("     Temperature is: ");
	  float celsius=sensors.getTempCByIndex(0);
	  Serial.println(celsius);

	  if(!waterTempDisplayActive && isSwitchTemperatureDisplay())
	  {
		  setDisplayToggleValues();
		  waterTempDisplayActive = true;
		  if((celsius > 10) && (celsius < 40))
		  {
			  setWaterTemp(celsius);
		  }
	  }
	  else if(waterTempDisplayActive && isSwitchTemperatureDisplay())
	  {
		  setDisplayToggleValues();
		  waterTempDisplayActive = false;
		  setAirTemp();
	  }
}


void setTime()
{
	lcd.setCursor(0, 1);
	lcd.print(rtc.getDOWStr(FORMAT_SHORT));
	lcd.setCursor(8, 1);
	lcd.print(rtc.getTimeStr());
	Serial.print("Time:   ");
	Serial.print(rtc.getTimeStr());
	Serial.print("\n");
}

void setLighOnOff()
{
	if(isLightOn())
	{
		Serial.print("Light On\n");
		digitalWrite(RELAIS2,LOW);
	}
	else
	{
		Serial.print("Light off\n");
		digitalWrite(RELAIS2,HIGH);
	}
}



bool isLightOn()
{
	uint8_t hour = rtc.getTime().hour;
	uint8_t min  = rtc.getTime().min;
	uint8_t sec = rtc.getTime().sec;
	char* timeLightOn;
	char* timeLightOff;

	if(isWeekend())
	{
		timeLightOn = (char*)TIMELIGHTON_WEEKEND;
		timeLightOff = (char*)TIMELIGHTOFF_WEEKEND;
		Serial.print("TimelineOff    ");
		Serial.println(timeLightOff);

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

	Serial.print("offhour   ");
	Serial.println(offhour);

	onmin = timeLightOn+3;
	//onmin[1] = timeLightOn[4];
	offmin = timeLightOff+3;
	//offmin[1] = timeLightOff[4];

	Serial.print("offmin   ");
	Serial.println(offmin);

	onsec = timeLightOn+6;
	offsec = timeLightOff+6;

	Serial.print("offsec   ");
	Serial.println(offsec);


	uint8_t intOnHour = atoi(onhour);
	uint8_t intOffHour = atoi(offhour);
	uint8_t intOnMinute = atoi(onmin);
	uint8_t intOffMinute = atoi(offmin);
	uint8_t intOnSecond = atoi(onsec);
	uint8_t intOffSecond = atoi(offsec);

	Serial.print("integer offhour   ");
	Serial.println(intOffHour);
	Serial.print("integer offminute   ");
	Serial.println(intOffMinute);
	Serial.print("integer offsecond   ");
	Serial.println(intOffSecond);
	Serial.print("integer onhour   ");
	Serial.println(intOnHour);
	Serial.print("integer onminute   ");
	Serial.println(intOnMinute);
	Serial.print("integer onsecond   ");
	Serial.println(intOnSecond);



// 1) hour greater
	if(hour > intOnHour)
	{
		Serial.println("actual hour greater than spec. hour");
		if(hour < intOffHour)
		{
			Serial.println("Light on hour");
			return true;
		}
	}
	if((hour > intOnHour) && (hour == intOffHour)  && (min < intOffMinute))
	{
		Serial.println("actual min lowe than intminOff");
		return true;

	}

	if((hour > intOnHour) && (hour == intOffHour) &&  (min > intOnMinute) && (min == intOffMinute) && (sec < intOffSecond))
	{
		Serial.println("actual second lower than intminSecond");
		return true;

	}

// 2. min greater
	if((hour == intOnHour) && (min > intOnMinute))
	{
		Serial.println("hour equal min greater");
		if(min < intOffMinute)
		{
			Serial.println("Light on minute");
			return true;
		}
	}

	if((hour == intOnHour) && (min == intOffMinute)  && (sec > intOnSecond))
	{
		Serial.println("hour equal min equal sec greater ");
		if((sec < intOffSecond))
		{
			Serial.println("Light on second");
			return true;
		}
	}

	Serial.println("Light is off");
	return false;
}




void setDisplayToggleValues()
{
	timeToggleTempDisplay = rtc.getTime();
	uint8_t t  = timeToggleTempDisplay.sec + DISPLAYTOGGLETIME;
	if(t >= MAXSEC)
	{
		secOverflowFlag = true;
		t = t - MAXSEC;

	}
	else
	{
		secOverflowFlag = false;
	}

	timeToggleTempDisplay.sec = t;
	Serial.print("toggleTime    ");
	Serial.print(timeToggleTempDisplay.sec);
	Serial.print("     ");
//	Serial.print(t);
	Serial.print("\n");
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


void setServiceMode()
{
	int val = digitalRead(SERVICEBUTTON);
	if(val==HIGH)
	{
		digitalWrite(RELAIS2,LOW);  // Light ON
		digitalWrite(RELAIS3,HIGH); //Pump out
		digitalWrite( RELAIS4,HIGH); // Heater out
	}
	else
	{
		digitalWrite(RELAIS2,LOW);  // Light ON
		digitalWrite(RELAIS3,LOW); //Pump ON
		digitalWrite( RELAIS4,LOW); // Heater ON
	}

}

bool setOff()
{
	int val = digitalRead(ONOFFBUTTON);
	bool retVal = false;
	if(val==HIGH)
	{
		digitalWrite(RELAIS2,HIGH);  // Light out
		digitalWrite(RELAIS3,HIGH); //Pump out
		digitalWrite( RELAIS4,HIGH); // Heater out
		retVal=true;
	}
	else
	{
		digitalWrite(RELAIS2,LOW);  // Light out
		digitalWrite(RELAIS3,LOW); //Pump out
		digitalWrite( RELAIS4,LOW); // Heater out
	}
	return retVal;
}




