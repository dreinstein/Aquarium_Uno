

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
const long TOGGLE_TIME_DISPLAY  = 4000;

#define DELAYTIME_BASE		  		200
#define ACTUALISE_LIGHT_MULTiPLIER  20
#define ACTUALISE_TIME_MULTIPLIER   800
#define ACTUALISE_PUMP_MULTIPLIER   2000
long refreshVariable=0;


const char* stringBadTempValue = "Temperaturfehler";
const char* stringTempValueWater = "Wasser:  ";
const char* stringTempValueAir   = "Luft";
const char* saturday = "Sat";
const char* sunday = "Sun";


enum LIGHT_STATUS
{
	LIGHT_ON=0,
	LIGHT_OFF,
	LIGHT_NOCHANGE
};

enum TEMPERATUR_DISPLAY_STATUS
{
	WATERTEMP_ON=0,
	WATERTEMP_OFF,
	WATERTEMP_NOCHANGE
};
