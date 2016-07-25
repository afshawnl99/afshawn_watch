#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <TimeLib.h>
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_CLK 13
#define STATUS_X 10
#define STATUS_Y 65


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void setup() {

  
  // clear the screen
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  Serial.begin(9600);
  //setSyncProvider( requestSync);  //set function to call when sync required
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  tft.println("Afshawn Watch 1.0");


  

  }


  
void loop(void) {

   if (Serial.available() > 1) { // wait for at least two characters
    digitalClockDisplay();
    }

 
  delay(1000);
  
    

 
}



 




void digitalClockDisplay() {
  // digital clock display of the time
  String time_new = String(Serial.readString());
  tft.fillRect(STATUS_X, STATUS_Y, 240, 80, ILI9341_BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(7);
  tft.print(time_new);


 // tft.setCursor(0, 70);
 // tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(7);
 // Serial.print(time_new);
 // tft.print(time_new);

}
//  String time_output = String("%d:%s:%s",hour(),printDigits(minute()),printDigits(second()));
//  tft.println(time_output);
  /* 
  Serial.print(" ");

  Serial.print(dayShortStr(weekday()));
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(monthShortStr(month()));
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
 
}


String printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10){
   
    String digits = String(digits) + "0";
    return digits;

  }
  else{
    String digits = String(digits);
    return digits;

  }
  
}



void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 - paul, perhaps we define in time.h?

   pctime = Serial.parseInt();
   if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
     setTime(pctime); // Sync Arduino clock to the time received on the serial port
   }
}

time_t requestSync() {
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}
*/ 

