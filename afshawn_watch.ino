#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Adafruit_STMPE610.h>

#include <TimeLib.h>
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_CLK 13




Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);


char buttonlabels[3][5] = {"File", "Auth", "Apps"};
uint16_t buttoncolors[3] = {ILI9341_DARKGREEN, ILI9341_DARKGREY, ILI9341_RED};
Adafruit_GFX_Button buttons[3];
void setup() {

  
  // clear the screen
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  Serial.begin(9600);
  setSyncProvider( requestSync);  //set function to call when sync required
  tft.setCursor(10, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  tft.println("Afshawn Watch 1.0");


  

  }


  
void loop() {


  if (Serial.available() > 1) { // wait for at least two characters
    char check_header = Serial.read();
    if( check_header == TIME_HEADER) {
      processSyncMessage();
    }

  }
  if (timeStatus()!= timeNotSet) {
    digitalClockDisplay();  
  }
  
  delay(1000);
 
}


void digitalClockDisplay() {
  String time_minute;
  int TimeText_X = 10;
  int TimeText_Y = 65;

  tft.fillRect(TimeText_X, TimeText_Y, 300, 60, ILI9341_RED);
  tft.setCursor(TimeText_X, TimeText_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(6);
  // digital clock display of the time
  String time_hour = String(hour());
  String time_minute_raw = String(second());
  if (int(time_minute_raw.length()) == 1){

    String time_minute = "0" + time_minute_raw;
    Serial.print(time_minute);
    String time_update = String(time_hour + ":" + time_minute);
    delay(100);
    tft.print(time_update);


  }
  else{
    String time_update = String(time_hour + ":" + time_minute_raw);
    delay(100);
    tft.print(time_update);
  }
  



  int DateText_X = 10;
  int DateText_Y = 130;

  tft.fillRect(DateText_X, DateText_Y, 300, 20, ILI9341_RED);
  tft.setCursor(DateText_X, DateText_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Wed, Jul 19, 2015");

}


