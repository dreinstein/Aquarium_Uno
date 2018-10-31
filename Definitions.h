#ifndef _DEFINITIONS
#define _DEFINITIONS

#include "Arduino.h"

// ARDUINO IN/OUT
#define RELAIS2       9     /// 6   //LIGHT  //OUT, gelb LED, graues Kabel
#define RELAIS3       12    /// 7    //PUMP  //OUT, rote LED , orange Kabel
#define RELAIS4       11    /// 8    //HEATER //OUT, blau LED. yellow Kabel,
#define TEMPSENSOR    8	    //TempSensor  //IN
#define SERVICEBUTTON 7     //ServiceButton  hight: Pump, TempSensor out//IN
#define ONOFFBUTTON   6    //ONOFFBUTTON +																														v     hight: Pump, TempSensor, Light out //IN
//#define LCD_RS		  12
//#define LCD_ENABLE	  13
//#define LCD_D0		  5
//#define LCD_D1		  4
//#define LCD_D2		  3
//#define LCD_D3		  2


// SDA PinA4
// SLC PinA5


// Belegung serieller Anschluss Relais
// Pin1  5V rot
// pin5  gnd sw
// pin6  light grau
// pin7 pump orange
// pin8 heater yellow


// Relais1 light
// Relais2 pump
// Relais3 heater

// Belegung serielle Schnittstelle
// 1 - 5V
// 5 - Ground
// 6,7,8,9 Daten


// LCD positions
#define CURSERPOSTEMPSTRING  0
#define CURSERPOSTEMPVALUE   8
#define CURSERPOSCSTRING     14
#define MAXSEC				 59
#define DISPLAYTOGGLETIME    20
#define TEMP_RESOLUTION      12

#define WATERTEMPERATUR_VALIDMAXVALUE  40
#define WATERTEMPERATUR_VALIDMINVALUE  10

// active and inavtive settings, can be changed for relais high active or low acive
#define ACTIVE          HIGH
#define INACTIVE        LOW

// value for actualising display  and light calculation 
#define REFRESHVARIABLE_MAX   80000
#define TOGGLE_TIME_DISPLAY   200
#define DELAYTIME_BASE		  		200
#define ACTUALISE_LIGHT_MULTiPLIER  20
#define ACTUALISE_TIME_MULTIPLIER   800
#define ACTUALISE_PUMP_MULTIPLIER   2000
//#define ACTUALISE_NTC_MULTIPLIER    500
#define ACTUALISE_NTC_MULTIPLIER    80000

// macro calculate when to actualise
#define TO_ACTUALISE(REFRESH,MULTIPLIER) (!((REFRESH*DELAYTIME_BASE)%MULTIPLIER))

#endif
