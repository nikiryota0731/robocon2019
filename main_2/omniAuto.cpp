//#include "sub.h"
//
///*  ジャイロ */
//extern int gyroOffset;
//
//const int ROBOTWIDTH_X = 700;
//const int ROBOTWIDTH_Y = 700;
//
//
//int locationState = 0;
//bool isPause = false;
//bool isTargetLocation = false;
//
//bool getIsTargetLocation(int nowX, int nowY, int moveX, int moveY) {
//  return getDistance(nowX, nowY, moveX, moveY) < 20;
//}
//
//void omniAuto(int nowX, int nowY) {
//  static int locations[10][3] = {
//    {600, 1800, 40},
//    {600, 1800 + 2000, 40},
//    {600 + 1800, 1800 + 2000, 40},
//    {600 + 1800, 1800 + 2000 + 800, 20},
//    {600 + 1800 + 1500, 1800 + 2000 + 800, 20},
//    {600 + 1800 + 1500, 1800 + 2000 - 800, 20},
//    {600 + 1800, 1800 + 2000 - 800, 20},
//    {600 + 1800, 1800 + 2000, 20},
//    {600, 1800 + 2000, 40},
//    {600, 1800, 40}
//  };
//
//  int moveX = locations[locationState][0];
//  int moveY = locations[locationState][1];
//
//  omniXPid.update(moveX - nowX, 0, locations[locationState][2]);
//  omniYPid.update(moveY - nowY, 0, locations[locationState][2]);
//  i2cOmni.setData(0, map(-omniXPid.getPower(), -255, 255, 0, 255)); 
//  i2cOmni.setData(1, map(-omniYPid.getPower(), -255, 255, 0, 255));
//
//  gyroPid.update(gyro.getData(), 0);
//  i2cOmni.setData(2, map(gyroPid.getPower(), 255, -255, 0, 255));
//
//  if (locationState == 0) {
//    isStart = false;
//    if (limitSW[0].getClick(FALLING) || DS3.getCircleClick()) {
//      isStart = true;
//    }
//  }
//  isTargetLocation = getIsTargetLocation(nowX, nowY, moveX, moveY);
//
//  if (isStart) {
//    if (!isPause) {
//      //      if (isTargetLocation || DS3.getCircleClick()) {
//      if (DS3.getCircleClick()) {
//        locationState++;
//        isTargetLocation = false;
//        if (locationState >= 10)
//          locationState = 0;
//      }
//      if (DS3.getCrossClick()) {
//        locationState--;
//      }
//    }
//  }
//
//
//
//  setDisplay(1, 0, nowX);
//  setDisplay(1, 1, nowY);
//
//  setDisplay(1, 2, moveX);
//  setDisplay(1, 3, moveY);
//
//  setDisplay(2, 3, isTargetLocation * 88);
//
//  Serial.print(nowX);
//  Serial.print("\t");
//  Serial.print(nowY);
//  Serial.print("\t");
//  Serial.print(moveX);
//  Serial.print("\t");
//  Serial.print(moveY);
//  Serial.print("\t");
//  Serial.print(isTargetLocation);
//  Serial.print("\t");
//  Serial.print(locationState);
//  Serial.print("\t");
//
//
//}
