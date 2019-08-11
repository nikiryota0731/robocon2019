#include <Wire.h>
#include"sub.h"

const int ENC_ADDR = 2;
const int OMNIBOARD_ADD = 8;
const int MOTORBOARD_ADD = 7;
const int DS3BOARD_ADD = 9;
const int LCD_ADD = 11;
const int LIMITSW_ADDR = 15;
const int SERVO_ADDR = 17;
const int SOLENOID_ADD = 21;
const int SDMODULE = 12;

const int START_X = 600;
const int START_Y = 1800;
bool isZoneRed, isStart;


ControllerManagerDS3 DS3(DS3BOARD_ADD);
EncoderBoardMbed enc(ENC_ADDR);
LoopCycleController loopPeriodUs(17000);
positionEstimmation position;

PidController mainRollUpPid(0.08, 0, 0, loopPeriodUs.getCycleUs(), 300.0); //巻取り大PIDオブジェクト
PidController subRollUpPid(0.08, 0, 0, loopPeriodUs.getCycleUs(), 300.0); //巻取り小PIDオブジェクト
swController DS3RightHatX, LCDSW[4], limitSW[15];
omniController omniDriver(loopPeriodUs.getCycleUs(), OMNIBOARD_ADD);

I2CMasterWriter i2cLCD(LCD_ADD, 9);
I2CMasterWriter i2cMotorBoard(MOTORBOARD_ADD, 5), i2cServoBoard(SERVO_ADDR, 1);
I2CMasterWriter i2csolenoidBoard(SOLENOID_ADD, 1);
I2CMasterReader i2ReceiveLCD(LCD_ADD, 1), i2cSW(LIMITSW_ADDR, 2);
I2CMasterReader i2cSDReceive(SDMODULE, 1);
gyroSerial gyro;

void setup() {
  delay(3000);
  Wire.begin();
  Serial.begin(115200);
  enc.init();
  gyro.init();
  gyro.setOffset();
  gyro.setOffset();
}

void loop() {
  //  long oldTime = micros();

  if (DS3.getSelectToggle()) {
    for (int i = 1; i < 5; i++)
      i2cMotorBoard.setMotorData(i, 0);
  } else {
    if(limitSW[0].getClick(FALLING) || DS3.getCircleClick()){
      omniDriver.start();
    }
    omniDriver.run(LCDSW[4].getData(), position.getNowX(), position.getNowY(), gyro.getData());
    firstArm();
    secondArm();

  }
  if (DS3.getStartClick()) {
    gyro.setOffset();
    position.reset();
  }
  display();


  allUpdate();
  //  datalog();
  show();

  //  Serial.println(micros() - oldTime);

}
void show() {
  omniDriver.show();
  //  Serial.print("  ||  ");
//      limitSW[0].show();
//    i2cSW.show(BIN);
  //  enc.show();
//    i2cServoBoard.show();
//    Serial.print(gyro.getData());

  Serial.print('\n');
}

void datalog() {
  Serial.write('s');
  //  S\erial.write((nowX >> 8) & 0x00ff);
  //  Serial.write(nowX & 0x00ff);
  //  Serial.write((nowY >> 8) & 0x00ff);
  //  Serial.write(nowY & 0x00ff);
  //  Serial.write((moveX >> 8) & 0x00ff);
  //  Serial.write(moveX & 0x00ff);
  //  Serial.write((moveY >> 8) & 0x00ff);
//  //  Serial.write(moveY & 0x00ff);
//  Serial.write(i2cOmni.getSendData(0));
//  Serial.write(i2cOmni.getSendData(1));
//  Serial.write(i2cOmni.getSendData(2));
}
