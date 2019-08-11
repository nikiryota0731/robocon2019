//#include "sub.h"
//
//int omniTest() {
//  static int turnValue = 0;
//  if (DS3.getLeftClick())
//    turnValue += 5;
//  else if (DS3.getRightClick())
//    turnValue -= 5;
//  if (DS3.getStartClick())
//    turnValue = 0;
//  return turnValue;
//
//}
//
//void omniManual(int moveX, int moveY, int turn) {
//  moveX = map(moveX, 0, 255, 127 - 50, 127 + 50);
//  moveY = map(moveY, 255, 0, 127 - 50, 127 + 50);
//  if (abs(moveX - 127) < 5)
//    moveX = 127;
//  if (abs(moveY - 127) < 5)
//    moveY = 127;
//  i2cOmni.setData(0, moveX);
//  i2cOmni.setData(1, moveY);
//  if (DS3RightHatX.getClick(FALLING)) {
//    gyro.setOffset();
//  }
//
//  if (!DS3RightHatX.getData()) {
//    gyroPid.update(gyro.getData(), 0);
//    i2cOmni.setData(2, map(gyroPid.getPower(), 255, -255, 0, 255));
//  } else
//    i2cOmni.setData(2, map(DS3.getRightHatX(), 255, 0, 127 - 30, 127 + 30) );
//  //  Serial.write((angleDeg >> 8) & 0x00ff);
//  //  Serial.write(angleDeg & 0x00ff);
//  //  Serial.write(!DS3RightHatX.getData());
//
//}
