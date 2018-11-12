#include <SoftwareSerial.h>

#define ENABLE_LEFT 9
#define FWD_LEFT 8
#define BWD_LEFT 7

#define ENABLE_RIGHT 6
#define FWD_RIGHT 5
#define BWD_RIGHT 4

SoftwareSerial BTSerial(2, 3);
int state;
int carSpeed;

void carStop(){
  digitalWrite(FWD_LEFT, LOW);
  digitalWrite(FWD_RIGHT, LOW);
  digitalWrite(BWD_LEFT, LOW);
  digitalWrite(BWD_RIGHT, LOW);
}

void moveFwd(int speed) {
  analogWrite(ENABLE_LEFT, speed);
  analogWrite(ENABLE_RIGHT, speed);

  digitalWrite(FWD_LEFT, LOW);
  digitalWrite(FWD_RIGHT, LOW);
  digitalWrite(BWD_LEFT, HIGH);
  digitalWrite(BWD_RIGHT, HIGH);
}

void moveBwd(int speed) {
  analogWrite(ENABLE_LEFT, speed);
  analogWrite(ENABLE_RIGHT, speed);

  digitalWrite(BWD_LEFT, LOW);
  digitalWrite(BWD_RIGHT, LOW);
  digitalWrite(FWD_LEFT, HIGH);
  digitalWrite(FWD_RIGHT, HIGH);
}

void moveLeft(){
  analogWrite(ENABLE_RIGHT, 255);
  analogWrite(ENABLE_LEFT, 255);
  
  digitalWrite(FWD_RIGHT, LOW);
  digitalWrite(BWD_RIGHT, HIGH);
  digitalWrite(FWD_LEFT, HIGH);
  digitalWrite(BWD_LEFT, LOW);
  
  delay(500);
  disable();
}

void moveRight(){
  analogWrite(ENABLE_LEFT, 255);
  analogWrite(ENABLE_RIGHT, 255);
  
  digitalWrite(BWD_LEFT, HIGH);
  digitalWrite(FWD_RIGHT, HIGH);
  digitalWrite(FWD_LEFT, LOW);
  digitalWrite(BWD_RIGHT, LOW);
  
  delay(500);
  disable();
}

void disable() {
  analogWrite(ENABLE_LEFT, 0);
  digitalWrite(FWD_LEFT, LOW);
  digitalWrite(BWD_LEFT, LOW);
  analogWrite(ENABLE_RIGHT, 0);
  digitalWrite(FWD_RIGHT, LOW);
  digitalWrite(BWD_RIGHT, LOW);
}

void setup() {
  pinMode(ENABLE_LEFT, OUTPUT);
  pinMode(FWD_LEFT, OUTPUT);
  pinMode(BWD_LEFT, OUTPUT);

  pinMode(ENABLE_RIGHT, OUTPUT);
  pinMode(FWD_RIGHT, OUTPUT);
  pinMode(BWD_RIGHT, OUTPUT);

  Serial.begin(9600);
  BTSerial.begin(9600);
  state = 0;
}

void loop() {
  if(BTSerial.available()){
    state = BTSerial.read();
    Serial.write(state);
  }
  
  switch(state){
    case '1':
      moveFwd(200);
      break;
    case '2':
      moveBwd(200);
      break;
    case '3':
      moveLeft();
      state = '0';
      break;
    case '4':
      moveRight();
      state = '0';
      break;
    case '5':
      moveFwd(250);
      break;
    case '6':
      moveBwd(250);
      break;
    case '7':
      state = '3';
      break;
    case '8':
      state = '4';
      break;
    case '0':
      carStop();
      break;
  }
}
