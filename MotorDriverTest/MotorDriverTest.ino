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

// These constants won't change. They're used to give names to the pins used:
const int highPin = 11;  // Analog input pin that the potentiometer is attached to
const int lowPin = 10; // Analog output pin that the LED is attached to



void setup() {
  // initialize serial communications at 9600 bps:
  pinMode(highPin, OUTPUT);
  pinMode(lowPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  analogWrite(highPin, 255);
  digitalWrite(lowPin, LOW);
  delay(5000);
  analogWrite(highPin, 128);
  delay(5000);
  digitalWrite(highPin, LOW);
  digitalWrite(lowPin, HIGH);


  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(5000);
}
