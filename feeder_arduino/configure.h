//Access Point Settings
String AP_Name = "FEEDER_01";
String AP_Password = "feed1234";

String jsonString; //Variable to store json string which contain time settings
StaticJsonDocument<1024> doc; //Allocates memory on the stack

char currentTime[32]; //Buffer to store current time
RTC_DS3231 rtc; //Creates an rtc instant

AsyncWebServer server(80); //Create AsyncWebServer object on port 80

//VARIABLES TO STORE TIMINGS THAT GOT BY PARSING THE JSON STRING.
int feedTimeArray[10];  //Stores the hours to be feed
int feedDurationArray[10];  //Stores the duration of feeding for respective feed hours
int pumpOnDuration, pumpOffDuration;  //Pump ON and OFF durations
int aerationOnTime, aerationOffTime;  //When to start aerator and when to off
bool settings_useSystemTime;  //Wheteher system time or custom time is selected on the web page
String settings_customTime; //Time in string form which is uploaded from the web page. (eg: 14:15)
int set_hour, set_minute; //Hour and Minute got by parsing the settings_customTime string from the web page.

//VARIABLES TO STORE THE TIMINGS IN MILLIS FOR COMPARING WITH millis()
unsigned long int feedDurationMillis;
unsigned long int pumpOnDurationMillis;
unsigned long int pumpOffDurationMillis;

unsigned long int feedTimeStartMillis; // Millis at which feeding starts. Used for feed duration calculation
unsigned long previousPumpMillis = 0; // Millis at which last state change of pump occured
bool pumpState = true; //Whether the pump is ON or OFF

//DEFINING GPIO PINS FOR RELAY DRIVING
int feederPin = D5 , airPin = D7, pumpPin = D0;

bool feedTimeStart = 0; //This flag is set to 1 when feeding is started. Used to start feedDurationMillis Count.
