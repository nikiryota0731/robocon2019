#include "sub.h"

void allUpdate() {
  DS3.update();
  isZoneRed = !i2ReceiveLCD.getBitData(0, 0);
  i2cOmni.update();
  i2cMotorBoard.update();
  i2cServoBoard.update();
  i2csolenoidBoard.update();
  enc.update();
  i2cLCD.update();
  i2ReceiveLCD.update();
  i2cSW.update();
  position.update(enc.getCount(1), enc.getCount(2), gyro.getData());
  for (int i = 0; i < 15; i++) {
    if (i < 8) limitSW[i].update(i2cSW.getBitData(0, i));
    else limitSW[i].update(i2cSW.getBitData(1, i - 8));
  }
  gyro.update();
  DS3RightHatX.update(abs(DS3.getRightHatX() - 127) > 10);
  for (int i = 0; i < 4; i++)
    LCDSW[i].update(i2ReceiveLCD.getBitData(0, i + 1));
  loopPeriodUs.update();
}
