#include "sub.h"

void secondArm() {
  static int bathTowelState = 0;
  static int servoValue = 0;
  static bool isSolenoidPush = false;
  
  if (DS3.getStartClick()) {
    DS3.RightCountUpReset();
  }

  switch (bathTowelState) {
    case 0:
      servoValue = 0;
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;


  }

  //手動でバスタオルサーボ動かす
  if(DS3.getStartClick()){
    DS3.RightCountUpReset();
  }
  i2cServoBoard.setData(0, DS3.getRightCountUp()%3);
  i2csolenoidBoard.setBitData(0, 0, DS3.getLeft());

}
