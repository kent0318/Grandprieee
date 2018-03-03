#include <Servo.h>

Servo myservo;
int pos = 90;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char error[1];
  Serial.readBytes(error, 1);
  analogWrite(13, abs(error[0]));
}
