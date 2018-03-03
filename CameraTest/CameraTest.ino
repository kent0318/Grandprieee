#include <Servo.h>

Servo myservo;
const int SI = 3;
const int CLK = 4;
const int input = 0;
int pos = 90;
const int mid = 64;
void setup() {
  // put your setup code here, to run once:
  pinMode(SI, OUTPUT);
  pinMode(CLK, OUTPUT);
  myservo.attach(9);
  myservo.write(mid);

  Serial.begin(9600);
  delay(1000);
}
int data[128];
int output[127];
void loop() {
  // put your main code here, to run repeatedly:
  one_shot();
//  Serial.println("s");

  medianFilter(data);
  gradientFilter(data, output);
  int maxIndex = 0;
  int minIndex = 0;
//  for (int i = 0; i < 127; i++) {
//    Serial.println(output[i]);
//  }
  
  for (int i = 0; i < 127; i++) {
    if (output[i]>output[maxIndex]) {
      maxIndex = i;
    }
    if (output[i]<output[minIndex]) {
      minIndex = i;
    }
  }
  int error = (maxIndex+minIndex)/2-mid;
  runServo(error + mid);
}

void runServo(int degree) {
  myservo.write(degree);
  Serial.println(degree);
}

void one_shot() {

  // clear out data
  digitalWrite(CLK, LOW);
  digitalWrite(SI, HIGH);
  digitalWrite(CLK, HIGH);
  digitalWrite(SI, LOW);
  digitalWrite(CLK, LOW);
  for(int i = 0; i < 128; i++) {
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
    delayMicroseconds(30);

  }
  // output data
  digitalWrite(SI, HIGH);
  digitalWrite(CLK, HIGH);
  digitalWrite(SI, LOW);
  digitalWrite(CLK, LOW);
  for(int i = 0; i < 128; i++) {
    delayMicroseconds(20);
    data[i]=analogRead(input);
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
}
void gradientFilter(int arr[], int newArr[]) {
  for (int i = 0; i < 127; i++) {
    newArr[i] = arr[i+1]-arr[i];
  }
  
}
void medianFilter(int arr[]) {
  int oldValue = arr[0];
  for (int i = 1; i < 127; i++) {
    int newValue = median(oldValue, arr[i], arr[i+1]);
    oldValue = arr[i];
    arr[i] = newValue;
  }
}
int median(int a, int b, int c) {
  int x = max(a,b);
  int y = max(a,c);
  int z = max(b,c);
  if(x==y) {
    return z;
  }
  else if(x==z) {
    return y;
  }
  else {
    return x;
  }
}
void continuous() {
     digitalWrite(SI, HIGH);
  digitalWrite(CLK, HIGH);
  digitalWrite(SI, LOW);
  digitalWrite(CLK, LOW);
  for(int i = 0; i < 128; i++) {
    delayMicroseconds(10);
    Serial.println(analogRead(input));
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  } 
}
  


