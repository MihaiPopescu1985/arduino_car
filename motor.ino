/*
 * The protocol used to communicate :
 * '1' - the car is moving forward in low speed
 * '2' - the car is moving backward in low speed
 * '3' - front weels are turning left
 * '4' - front weels are turning right
 * '5' - the care is moving forward in high speed
 * '6' - the car is moving backward in high speed
 * '7' - front weels are turning left
 * '8' - front weels are turning right
 * 'a' - front LEDs are turning on
 * 'b' - front LEDs are turning off
 * 'c' - the buzzer is turning on for 1 second
 */


#include <SoftwareSerial.h>

#define ENABLE_FWD_BWD 9
#define BWD 8
#define FWD 7

#define ENABLE_LEFT_RIGHT 6
#define RIGHT 5
#define LEFT 4

#define LED 10
#define BUZZER 11

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

  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
  BTSerial.begin(9600);
  state = 0;
}

void moveFwd() {
  analogWrite(ENABLE_LEFT_RIGHT, 0);
  analogWrite(ENABLE_FWD_BWD, carSpeed);

  digitalWrite(BWD, LOW);
  digitalWrite(FWD, HIGH);
}

void moveBwd() {
  analogWrite(ENABLE_LEFT_RIGHT, 0);
  analogWrite(ENABLE_FWD_BWD, carSpeed);

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

  if(Serial.available()) {
    state = Serial.read();
    Serial.write(state);
  }
  
  switch (state) {
    case '1' :
      carSpeed = 100;
      moveFwd();
      break;
    case '2' :
      carSpeed = 100;
      moveBwd();
      break;
    case '3' :
      turnLeft();
      break;
    case '4' :
      turnRight();
      break;
    case '5' :
      carSpeed = 255;
      moveFwd();
      break;
    case '6' :
      carSpeed = 255;
      moveBwd();
      break;
    case '7' :
      state = '3';
      break;
    case '8' :
      state = '4';
      break;
    case 'a' :
      digitalWrite(LED, HIGH);
      break;
    case 'b' :
      digitalWrite(LED, LOW);
      break;
    case 'c' :
      digitalWrite(BUZZER, HIGH);
      delay(1000);
      digitalWrite(BUZZER, LOW);
      break;
    default :
      stopMoving();
      break;
  }
}
