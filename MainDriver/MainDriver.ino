#include <Servo.h>

Servo myservo;
int mid = 90;
int pos = 90;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  myservo.attach(9);
  myservo.write(mid);
  delay(2000);
}
int increment = 3;
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available()>0) {
    signed char a = Serial1.read();
    int error = a;
//    if (pos >= 180){
//      increment = -3;
//    }
//    else if(pos <= 0) {
//      increment = 3;
//    }
//    pos = pos + increment;
    pos = mid+error;
    myservo.write(pos);
    Serial.println(pos);
  }


}
