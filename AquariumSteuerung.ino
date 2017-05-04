#include "Arduino.h"
#include <LiquidCrystal.h> //LCD-Bibliothek laden
#include <OneWire.h>
#include <ds3231.h>
#include "DallasTemperature\DallasTemperature.h"

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);


//The setup function is called once at startup of the sketch

const char* stringBadTempValue = "Temperaturfehler";
const char* stringTempValue = "Temp:  ";

const int relais2 = 9;
const int relais3 = 10;
const int relais4 = 11;
const int tempSensor = 8;

OneWire  ds(tempSensor);
DallasTemperature sensors(&ds);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup()
{
// Add your initialization code here
	//pinMode(relais1,OUTPUT);
	pinMode(relais2,OUTPUT);
	pinMode(relais3,OUTPUT);
	pinMode(relais4,OUTPUT);

	lcd.begin(16, 2);
	rtc.begin();
	sensors.begin();


	//digitalWrite(relais1,LOW);
	digitalWrite(relais2,LOW);
	digitalWrite(relais3,LOW);
	digitalWrite(relais4,LOW);
	Serial.begin(9600);
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
	//delay(1000);
}

void setTemperature()
{
	// Send the command to get temperatures
	  sensors.requestTemperatures();
	  Serial.print("Temperature is: ");
	  float celsius=sensors.getTempCByIndex(0);
	  Serial.println(celsius); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire

	  //Update value every 1 sec.
	  if((celsius > 10) && (celsius < 40))
	  {
		  lcd.setCursor(0,0);
	  	  lcd.print(stringTempValue);
	  	  lcd.setCursor(6,0);
	  	  lcd.print(celsius);
	  	  lcd.setCursor(12, 0);
	      lcd.print("C");
         // delay(500);
	  }
}


void setTime()
{
	lcd.setCursor(0, 1);
	lcd.print(rtc.getDOWStr());
	//Serial.print(rtc.getDOWStr());
	//Serial.print(" ");

	// Send date
	//Serial.print(rtc.getDateStr());
	//Serial.print(" -- ");

	// Send time
	//Serial.println(rtc.getTimeStr());
	lcd.setCursor(8, 1);
	lcd.print(rtc.getTimeStr());
	//delay(1000);
}
