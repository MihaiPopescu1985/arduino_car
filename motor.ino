#include <SoftwareSerial.h>

#define ENABLE_FWD_BWD 9
#define BWD 8
#define FWD 7

#define ENABLE_LEFT_RIGHT 6
#define RIGHT 5
#define LEFT 4

SoftwareSerial BTSerial(2, 3);
int state;
int carSpeed;

void setup() {
  pinMode(ENABLE_FWD_BWD, OUTPUT);
  pinMode(FWD, OUTPUT);
  pinMode(BWD, OUTPUT);

  pinMode(ENABLE_LEFT_RIGHT, OUTPUT);
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);

  Serial.begin(9600);
  BTSerial.begin(9600);
  state = 0;
}

void moveFwd() {
  analogWrite(ENABLE_LEFT_RIGHT, 0);
  analogWrite(ENABLE_FWD_BWD, 255);

  digitalWrite(BWD, LOW);
  digitalWrite(FWD, HIGH);
}

void moveBwd() {
  analogWrite(ENABLE_LEFT_RIGHT, 0);
  analogWrite(ENABLE_FWD_BWD, 255);

  digitalWrite(FWD, LOW);
  digitalWrite(BWD, HIGH);
}

void turnLeft() {
  analogWrite(ENABLE_LEFT_RIGHT, 255);

  digitalWrite(RIGHT, LOW);
  digitalWrite(LEFT, HIGH);
}

void turnRight() {
  analogWrite(ENABLE_LEFT_RIGHT, 255);

  digitalWrite(LEFT, LOW);
  digitalWrite(RIGHT, HIGH);
}

void stopMoving() {
  analogWrite(ENABLE_FWD_BWD, 0);
  analogWrite(ENABLE_LEFT_RIGHT, 0);
}

void loop() {
  if(BTSerial.available()) {
    state = BTSerial.read();
  }
  switch (state) {
    case '1' :
      moveFwd();
      break;
    case '2' :
      moveBwd();
      break;
    case '3' :
      turnLeft();
      break;
    case '4' :
      turnRight();
      break;
    case '5' :
      state = '1';
      break;
    case '6' :
      state = '2';
      break;
    case '7' :
      state = '3';
      break;
    case '8' :
      state = '4';
      break;
    default :
      stopMoving();
      break;
  }
}














