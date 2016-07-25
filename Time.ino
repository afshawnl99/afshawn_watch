/* 
 * TimeSerialDateStrings.pde
 * example code illustrating Time library date strings
 *
 * This sketch adds date string functionality to TimeSerial sketch
 * Also shows how to handle different messages
 *
 * A message starting with a time header sets the time
 * A Processing example sketch to automatically send the messages is inclided in the download
 * On Linux, you can use "date +T%s\n > /dev/ttyACM0" (UTC time zone)
 *
 * A message starting with a format header sets the date format

 * send: Fs\n for short date format
 * send: Fl\n for long date format 
 */ 
 
#include <TimeLib.h>

// single character message tags
#define TIME_HEADER   'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7     // ASCII bell character requests a time sync message 






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
