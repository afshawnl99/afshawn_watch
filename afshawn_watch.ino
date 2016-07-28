#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "TimeLib.h"
#include "Timer.h"

Timer t;

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
int selectorState;
int optionState = 0;
int current_volume = 5;
void setup() {

  
  // clear the screen
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  Serial.begin(9600);
  setSyncProvider( requestSync);  //set function to call when sync required
  tft.setCursor(10, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(2);
  tft.println("Afshawn Watch 1.0");

  begginingOptions();

  //Button for sellecting items
  pinMode(selectorPin, INPUT);


  

  }


  
void loop() {
 

 selectorState = digitalRead(selectorPin);


   if(home_load == true){

   tft.setCursor(10, 190);
   tft.setTextColor(ILI9341_GREEN);
   tft.setTextSize(2);

   if (selectorState == HIGH) {
    if(optionState==1){
    launchSSH();

    }
    if(optionState==2){
    Serial.println("ssh-command sudo shutdown -h now");

    }

    if(optionState==3){
    Serial.println("ssh-command sudo shutdown -r now");

    }

    if(optionState==4){
    Serial.println("ssh-command sudo shutdown -s now ");

    }

    if(optionState==5){
    current_volume = current_volume + 1;
    if(current_volume>10){
      current_volume=10;
    }
    Serial.println("ssh-command sudo osascript -e 'set Volume " + String(current_volume) + "'");

    }

    if(optionState==6){
     current_volume = current_volume - 1;
    if(current_volume<0){
      current_volume=0;
    }
    Serial.println("ssh-command sudo osascript -e 'set Volume " + String(current_volume) + "'");

    }
   }
   potVal = analogRead(0);
   if(potVal<=170 && optionState!= 1){
    optionState=1;
     tft.fillRect(10, 190, 300, 20, ILI9341_BLACK);

     tft.print("> Launch SSH Client");

   }
   if(potVal>=170 && potVal<=340 && optionState!= 2){
     optionState=2;

     tft.fillRect(10, 190, 300, 20, ILI9341_BLACK);

     tft.print("> Shutdown");
   }
   if(potVal>=340 && potVal<=510 && optionState!= 3){
     optionState=3;

     tft.fillRect(10, 190, 300, 20, ILI9341_BLACK);

     tft.print("> Restart");
   }
   if(potVal>=510 && potVal<=680 && optionState!= 4){
     optionState=4;

     tft.fillRect(10, 190, 300, 20, ILI9341_BLACK);

     tft.print("> Sleep");
   }
    if(potVal>=680 && potVal<=850 && optionState!= 5){
     optionState=5;

     tft.fillRect(10, 190, 300, 20, ILI9341_BLACK);

     tft.print("> Volume Up");
   }
    if(potVal>=850 && potVal<=1023 && optionState!= 6){
     optionState=6;

     tft.fillRect(10, 190, 300, 20, ILI9341_BLACK);

     tft.print("> Volume Down");
   }

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
  home_load = false;
  tft.fillScreen(ILI9341_BLACK);
  //define home
  String current_path = "~/Desktop";
  String current_user = "ssh";



  String header = current_path + " " + current_user + "$";

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
  char *filen = strtok(file, ",");
  tft.print(filen);



  for(int(x)=1; x<7; x++){ 
  


   row = row + 110;
  if(String(filen).length() != 0){
   }

   filen = strtok(NULL, ",");
  if(x == reset_num){
    reset_num = reset_num + 3;
    column =  column + 25;
    row = 10;
  }

  if(String(filen).length() != 0){
   tft.setCursor(row, column);
   
   tft.print(filen);
  }
  }


}



