#include "sub.h"

void secondArm() {

  if(DS3.getStartClick()){
    DS3.RightCountUpReset();
  }

  i2cServoBoard.setData(0, DS3.getRightCountUp()%3);
  i2csolenoidBoard.setBitData(0, 0, DS3.getLeft());

}
