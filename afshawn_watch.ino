#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "TimeLib.h"

#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

// Configuiring TFT Screen
#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_CLK 13
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

const int selectorPin = 2;     // the number of the pushbutton pin
bool home_load = true;
bool load_time = true;
int potVal;

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
  begginingOptions();
  //Button for sellecting items
  pinMode(selectorPin, INPUT);


  

  }


  
void loop() {
 

 int selectorState = digitalRead(selectorPin);
 if (selectorState == HIGH) {
    // turn LED on:
    launchSSH();
  } 
  potVal = analogRead(0);            // reads the value of the potentiometer (value between 0 and 1023)
  //Serial.println(potVal);

  if (Serial.available() > 1) { // wait for at least two characters
    char check_header = Serial.read();
    if( check_header == TIME_HEADER) {
      processSyncMessage();
    }

  }
  if (timeStatus()!= timeNotSet) {
    if (home_load == true){
    homeClockDisplay();  
    }
  }
  
  delay(100);

 
}


void homeClockDisplay() {
  
  if (second() == 0 || load_time == true){
    int TimeText_X = 10;
    int TimeText_Y = 65;
    tft.fillRect(TimeText_X, TimeText_Y, 300, 60, ILI9341_BLACK);

    tft.setCursor(TimeText_X, TimeText_Y);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(6);
    // digital clock display of the time
    String time_hour = String(hour());
    String time_minute_raw = String(minute());
    if (int(time_minute_raw.length()) == 1){

      String time_minute = "0" + time_minute_raw;
      String time_update = String(time_hour + ":" + time_minute);
      delay(100);
      tft.print(time_update);

  
    }
    else{
      String time_update = String(time_hour + ":" + time_minute_raw);
      delay(100);
      tft.print(time_update);
    }
  if (hour() == 12 && minute() == 0 || load_time == true){
   load_time = false;

   int DateText_X = 12;
   int DateText_Y = 125;
   tft.fillRect(DateText_X, DateText_Y, 300, 20, ILI9341_BLACK);
   tft.setCursor(DateText_X, DateText_Y);
   tft.setTextColor(ILI9341_WHITE);
   tft.setTextSize(2);
   String time_day = String(dayShortStr(weekday())) + String(", ") + String(monthShortStr(month())) + String(" ") + String(day()) + String(", ") + String(year());
   tft.print(time_day);
   }

  }
 int SSHText_X = 10;
 int SSHText_Y = 190;
  tft.setCursor(SSHText_X, SSHText_Y);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.print("> Launch SSH Client");

}


void begginingOptions(){
  clearScreen();


  String launch_feedback;

  
  while (launch_feedback != "stop"){
    Serial.println("launch-serial");
    launch_feedback = Serial.readString();

  }


    Serial.println("show-home");
 

  
}

void clearScreen(){
  tft.fillRect(10, 65, 300, 150, ILI9341_BLACK);




}

void launchSSH(){
  tft.fillScreen(ILI9341_BLACK);
  home_load = false;
  //define home
  String current_path = "/Users/audatica";
  String current_user = "ssh";



  String header = "~" + current_path + " " + current_user + "$";

  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(1);
  tft.setCursor(10, 10);

  tft.print(header);

  
  int reset_num = 3;
  int column = 30;
  int row = 10;
  tft.setCursor(row, column);
  Serial.println("ssh-command ls " + current_path);
  String file_string = Serial.readString();
  char file[3000];
  file_string.toCharArray(file, 1000);
 // char file[] = "README.md,Serial.py,Time.ino,afshawn.ino,Serial.py,Time.ino,afshawn.ino";

  tft.print(strtok(file, ","));
//  Serial.println("ssh-command whoami");



  for(int x=1; x<21; x++){ 


   row = row + 110;
   char *filen = strtok(NULL, ",");
   Serial.println(x);
  if(x == reset_num){
    reset_num = reset_num + 3;
    column =  column + 25;
    row = 10;
  }
   tft.setCursor(row, column);
 
   tft.print(filen);
  }
  



  

}

