/*
  Analog input, analog output, serial output
  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/
#include <Servo.h>
 
// These constants won't change. They're used to give names to the pins used:
const int highPin = 11;  // Analog input pin that the potentiometer is attached to
const int lowPin = 10; // Analog output pin that the LED is attached to

Servo servo;


void setup() {
  // initialize serial communications at 9600 bps:
  servo.attach(9);
  servo.write(90);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
   if(Serial1.available() > 0)      // Send data only when you receive data:
   {
      char data = Serial1.read();        //Read the incoming data & store into data
      Serial.println(data);          //Print Value inside data in Serial monitor

   }


  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(10);
}
