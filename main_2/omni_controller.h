#pragma once
#include "sub.h"

#define AUTO 0
#define MANUAL 1

class omniController {
  private:
    int nowX, nowY;
    int moveX, moveY;
    bool isRunning = false;
    int locationState = 0;
    PidController *omniXPid, *omniYPid, *gyroPid; //足PIDオブジェクト
    I2CMasterWriter *i2cOmni;
    int locations[10][3] = {
      {600, 1800, 40},
      {600, 1800 + 2000, 40},
      {600 + 1800, 1800 + 2000, 40},
      {600 + 1800, 1800 + 2000 + 800, 20},
      {600 + 1800 + 1500, 1800 + 2000 + 800, 20},
      {600 + 1800 + 1500, 1800 + 2000 - 800, 20},
      {600 + 1800, 1800 + 2000 - 800, 20},
      {600 + 1800, 1800 + 2000, 20},
      {600, 1800 + 2000, 40},
      {600, 1800, 40}
    };
    int getDistance(int nowX, int nowY, int moveX, int moveY) {
      int distance = sqrt( square(moveX - nowX) + square(moveY - nowY));
      return distance;
    }
    bool getIsTargetLocation(int nowX, int nowY, int moveX, int moveY) {
      return getDistance(nowX, nowY, moveX, moveY) < 20;
    }
  public:
    omniController(unsigned long loopPeriodUs, int address) {
      omniXPid = new PidController(0.9 , 0.00, 0.255, loopPeriodUs, 300.0);
      omniYPid = new PidController(0.9 , 0.00, 0.255, loopPeriodUs, 300.0);
      gyroPid = new PidController(8.5, 0.0, 0.85, loopPeriodUs, 300.0);
      i2cOmni = new I2CMasterWriter(address, 3);
    }

    void start() {
      isRunning = true;
    }
    void stop() {
      isRunning = false;
    }

    void run(int mode, int nowXData, int nowYData, double gyro) {
      moveX = locations[locationState][0];
      moveY = locations[locationState][1];
      nowX = nowXData;
      nowY = nowYData;
      if (mode == AUTO) {
        moveX = locations[locationState][0];
        moveY = locations[locationState][1];
        omniXPid->update(moveX - nowX, 0, locations[locationState][2]);
        omniYPid->update(moveY - nowY, 0, locations[locationState][2]);
        i2cOmni->setData(0, map(-omniXPid->getPower(), -255, 255, 0, 255));
        i2cOmni->setData(1, map(-omniYPid->getPower(), -255, 255, 0, 255));

        gyroPid->update(gyro, 0);
        i2cOmni->setData(2, map(gyroPid->getPower(), 255, -255, 0, 255));
        if (isRunning) {
          if (getIsTargetLocation(nowX, nowY, moveX, moveY)) {
            locationState++;
            if (locationState >= 10) {
              locationState = 0;
              stop();
            }
          }
        }
      }
    }
    
    int getMoveX(){return moveX;}
    int getMoveY(){return moveY;}
    int getSendData(int arrayNum){return i2cOmni->getSendData(arrayNum);}
    
    void update() {
      i2cOmni->update();
    }
    void show() {
      Serial.print("isRunning : "); Serial.print(isRunning);
      Serial.print("\t");
      Serial.print("locationState : "); Serial.print(locationState);
      Serial.print("\t");
      i2cOmni->show();
    }

};
