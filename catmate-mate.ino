/*
 * An arduino sketch to dispense cat food in the CatMate C3000 
 * The hardware is a standard arduino or compatible with 
 * and Adafruit MotorShield 2.0 board to actuate the Catmate
 * and a DS1307 realtime clock. The DS1307 has a lot of time
 * drift so a chronodot woul dbe a better solution and should
 * work as a direct swap for the DS1307
 * 
 * The M1 terminals of the motorshield are conneted to the 
 * hobby motor inside the CateMat C3000 (grey and orange wires)
 * 
 * v1.0 - BRC 5/14/2022
 * 
 */
 
#include "RTClib.h"
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
RTC_DS1307 rtc;

void setup () {
  // Start the serial connection and show the filename.
  // I always include this so I can tell what program the board
  // is already running in case I find it in a drawer years later.
  
  Serial.begin(9600);
  Serial.print("This board is running: ");
  Serial.println(F(__FILE__));
  Serial.print("Compiled: ");
  Serial.println(F(__DATE__ " " __TIME__));
  delay(2000);

// start the clock
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

 // if the clock needs to be reset, this is a handy utility function 
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

// start the MotorShield v2
    if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }

}

void loop() {
  DateTime time = rtc.now();
  int hour = time.hour();
  int minute = time.minute();
  int second = time.second();

// print to the serial console for debugging
// also pulses the RX light which is a useful
// heartbeat for knowing the board hasn't hung

  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.println(second);

// Set the time to trigger the cat feeder
// Multiple trigger times can be set
// 5:00:00 am feed time:
  if (hour == 5 && minute == 0 && second == 0) {
    feed();
  }

// I usually avoid the delay() function but here
// it's useful for slowing things down and not calling
// feed() more than once per cycle  
  delay(1000);
}

void feed() {
  Serial.println("I'm feeding!");
// Full speed ahead!!
  myMotor->setSpeed(255);

// Start the motor
  myMotor->run(FORWARD);

// Set feed quantity by adjusting how long the motor runs.
// With the Catmate C3000 1/2 full of food:
// a 40-second delay dispenses about 1/3 cup of cat food
  delay(40000);
// a 30-second delay dispenses about 1/4 cup of cat food
// delay(30000);

// stop the motor
  myMotor->run(RELEASE);
}
