#include <Servo.h>

Servo myservo;
const int SI = 3;
const int CLK = 4;
const int input = 0;
const int mid = 83 ;
const int servoPin = 9;
const int highPin = 11;  // Analog input pin that the potentiometer is attached to
const int lowPin = 10; 
void setup() {
  // put your setup code here, to run once:
  pinMode(SI, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(highPin, OUTPUT);
  pinMode(lowPin, OUTPUT);
  myservo.attach(servoPin);
  myservo.write(mid);

  Serial1.begin(9600);
  Serial.begin(9600);
  delay(3000);
}

int velocity = 60;
int data[128];
int filteredData[127];
int prevError;
double iError;
boolean start = false;

double pval = 1.0;
double ival = 0.01;
double dval = 5.0;
int currentState = 0;

void loop() {
  
  if (Serial1.available() > 0) {
    char data = Serial1.read();
    if (data == 'a' && start == false) {
      start = true;
    }
    if (data == 'a' && start == true) {
      start = false;
      prevError = 0;
      iError = 0;
    }
    // only at stop you can adjust PID vals
    if( start == false ) {
      Serial1.print(pval);
      Serial1.print(' ');
      Serial1.print(ival);
      Serial1.print(' ');
      Serial1.println(dval);
      switch(data) {
        case 'p':
          currentState = 1;
          break;
        case 'i':
          currentState = 2;
          break;
        case 'd':
          currentState = 3;
          break;
        case '1':
          adjustPID(0.01);
          break
        case '2':
          adjustPID(0.1);
          break;
        case '3';
          adjustPID(-0.01);
          break;
        case '4';
          adjustPID(-0.1);
          break;
        default:
          break;
      }
    }
  }
  if (start) {
    one_shot();
  
    medianFilter(data);
    gradientFilter(data, filteredData);
    int error = getError(filteredData);
    int angle = PID(error, pval,ival,dval);
    runServo(mid-angle);
  
    analogWrite(highPin,(int)(velocity-0.5*error));
    digitalWrite(lowPin, LOW);
  }
  else {
    myservo.write(mid);
    digitalWrite(highPin, LOW);
    digitalWrite(lowPin, HIGH);
  }
}

void adjustPID(double value) {
  if( currentState == 1 ) {
    pval = pval + value;
  } else if(currentState == 2) {
    ival = ival + value;
  } else if( currentState == 3) {
    dval = dval + value;
  }
}

void runServo(int degree) {
  myservo.write(degree);
}

double PID(int error, double kp, double ki, double kd) {
  int dError = error-prevError;
  iError = iError + error;
  prevError = error;
  double angle = kp*error+ki*iError+kd*dError;
  return angle;
}
void one_shot() {

  // clear out data
  digitalWrite(CLK, LOW);
  digitalWrite(SI, HIGH);
  digitalWrite(CLK, HIGH);
  digitalWrite(SI, LOW);
  digitalWrite(CLK, LOW);
  // clear out
  for(int i = 0; i < 128; i++) {
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
  
  // Saturation time
  delayMicroseconds(5000);
  
  // write data
  digitalWrite(SI, HIGH);
  digitalWrite(CLK, HIGH);
  digitalWrite(SI, LOW);
  digitalWrite(CLK, LOW);
  for(int i = 0; i < 128; i++) {
    delayMicroseconds(20);
    int pixel=analogRead(input);
    data[i] = pixel;
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
  for (int i = 0; i < 127; i++) {
    int newValue = median(oldValue, arr[i], arr[i+1]);
    oldValue = arr[i];
    arr[i] = newValue;
  }
  arr[127]=median(oldValue, arr[127], arr[127]);
}
int getError(int arr[]) {
  int maxIndex = 0;
  int minIndex = 0;
//  for (int i = 0; i < 127; i++) {
//    Serial.println(output[i]);
//  }
  
  for (int i = 0; i < 127; i++) {
    if (arr[i]>arr[maxIndex]) {
      maxIndex = i;
    }
    if (arr[i]<arr[minIndex]) {
      minIndex = i;
    }
  }
  int error = (maxIndex+minIndex)/2-64;
  return error;
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

  


