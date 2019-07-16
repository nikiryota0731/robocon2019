#include "slaveReceiver.h"
#include "omni.h"
#include "motor.h"

const int M1pinA   = 3;
const int M1pinB   = 2;
const int M1pinPWM = 6;
const int M2pinA   = 5;
const int M2pinB   = 4;
const int M2pinPWM = 9;
const int M3pinA   = 8;
const int M3pinB   = 7;
const int M3pinPWM = 10;
const int M4pinA   = 13;
const int M4pinB   = 12;
const int M4pinPWM = 11;

const int ADDRESS = 8;
const int ALLWHEEL = 4;

slaveReceiver i2c(3);

omni omniDriver[ALLWHEEL] = {
  360 / ALLWHEEL * 1 - 45,
  360 / ALLWHEEL * 2 - 45,
  360 / ALLWHEEL * 3 - 45,
  360 / ALLWHEEL * 4 - 45
};

motor motorDriver[ALLWHEEL] = {
  motor(M1pinA, M1pinB, M1pinPWM),
  motor(M2pinA, M2pinB, M2pinPWM),
  motor(M3pinA, M3pinB, M3pinPWM),
  motor(M4pinA, M4pinB, M4pinPWM)
};

int Xpower, Ypower, turn;

void setup() {
  delay(2000);
  Serial.begin(115200);
  Wire.begin(ADDRESS);
  Wire.onReceive(receiveEvent);
}

void loop() {
  Xpower = map(i2c.getData(0), 0, 255, -255, 255);
  Ypower = map(i2c.getData(1), 0, 255, -255, 255);
  turn   = i2c.getData(2);
  
  for (int i = 0; i < ALLWHEEL; i++) {
    motorDriver[i].drive(-omniDriver[i].drive(getAngleDeg(0, 0, Xpower, Ypower), getDistance(0, 0, Xpower, Ypower), turn));
  }
  
  show();
}

int getAngleDeg(int nowX, int nowY, int moveX, int moveY) {
  double angle = atan2(moveY - nowY, moveX - nowX);
  if (angle < 0) {
    angle += 2 * PI;
  }
  angle = angle * 180 / PI;
  return (int)angle;
}

int getDistance(int nowX, int nowY, int moveX, int moveY) {
  int distance = sqrt( square(moveX - nowX) + square(moveY - nowY));
  return distance;
}

void show() {
  for (int i = 0; i < ALLWHEEL; i++)
    motorDriver[i].show();
//  i2c.show();
  Serial.println();
}

void receiveEvent(int howMany) {
  i2c.Update();
}
