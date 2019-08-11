#include "sub.h"
void setDisplay(uint8_t dataPageNum, uint8_t dataNum, int SendData) {
  static int pageNum = 0;
  static int sendData[4][4];

  sendData[dataPageNum][dataNum] = SendData;

  for (int i = 3; i >= 0; i--) {
    if (LCDSW[i].getClick(RISING))
      pageNum = i;
  }

  for (int i = 0; i < 4; i++) {
    i2cLCD.setData(i * 2, (sendData[pageNum][i] >> 8) & 0x00ff);
    i2cLCD.setData(i * 2 + 1, sendData[pageNum][i] & 0x00ff);
  } 
  i2cLCD.setData(8, pageNum);
}
void display() {
  setDisplay(0, 0, position.getNowX());
  setDisplay(0, 1, position.getNowY());
  setDisplay(0, 2, gyro.getData() * 10);
  
  setDisplay(1, 0, position.getNowX());
  setDisplay(1, 1, position.getNowY());
  setDisplay(1, 2, omniDriver.getMoveX());
  setDisplay(1, 3, omniDriver.getMoveY());

  setDisplay(2, 0, omniDriver.getSendData(0));
  setDisplay(2, 1, omniDriver.getSendData(1));
  setDisplay(2, 2, omniDriver.getSendData(2));

  setDisplay(3, 0, i2cMotorBoard.getSendData(1));
  setDisplay(3, 1, i2cMotorBoard.getSendData(2));
  setDisplay(3, 2, i2cMotorBoard.getSendData(3));
  setDisplay(3, 3, i2cMotorBoard.getSendData(4));

}
