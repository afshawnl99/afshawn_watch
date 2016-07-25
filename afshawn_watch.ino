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


#define BUTTON_X 50
#define BUTTON_Y 190
#define BUTTON_W 90
#define BUTTON_H 40
#define BUTTON_SPACING_X 20
#define BUTTON_SPACING_Y 20
#define BUTTON_TEXTSIZE 2

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
char buttonlabels[3][5] = {"Send", "Clr", "End"};
uint16_t buttoncolors[3] = {ILI9341_DARKGREEN, ILI9341_DARKGREY, ILI9341_RED};
Adafruit_GFX_Button buttons[3];
void setup() {

  
  // clear the screen
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  Serial.begin(9600);
  //setSyncProvider( requestSync);  //set function to call when sync required
  tft.setCursor(10, 0);
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
  int TimeText_X = 10;
  int TimeText_Y = 65;

  tft.fillRect(TimeText_X, TimeText_Y, 300, 60, ILI9341_RED);
  tft.setCursor(TimeText_X, TimeText_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(7);
  tft.print(time_new);

  int DateText_X = 10;
  int DateText_Y = 130;

  tft.fillRect(DateText_X, DateText_Y, 300, 20, ILI9341_RED);
  tft.setCursor(DateText_X, DateText_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Wed, Jul 19, 2015");

    // create buttons
  for (uint8_t row=0; row<5; row++) {
    for (uint8_t col=0; col<3; col++) {
      buttons[col + row*3].initButton(&tft, BUTTON_X+col*(BUTTON_W+BUTTON_SPACING_X), 
                 BUTTON_Y+row*(BUTTON_H+BUTTON_SPACING_Y),    // x, y, w, h, outline, fill, text
                  BUTTON_W, BUTTON_H, ILI9341_WHITE, buttoncolors[col+row*3], ILI9341_WHITE,
                  buttonlabels[col + row*3], BUTTON_TEXTSIZE); 
      buttons[col + row*3].drawButton();
    }
  }


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

