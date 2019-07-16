#include "sub.h"

void firstArm() {
  static int mainRollValue = 0;
  static int mainRollMax = 18500;
  static int mainRollMin = 0;
  static int subRollValue = 0;
  static int subRollMax = 19000;
  static int subRollMin = 0;

  static bool isClothesPinDown = true;
  static bool isSheetOpen = false;

  static int sheetState = 0;

  if (DS3.getUpClick())
    mainRollValue += 6000;
  else if (DS3.getDownClick())
    mainRollValue -= 2000;
  if (limitSW[1].getClick(RISING))
    mainRollMax = -enc.getCount(3);
  if (limitSW[2].getClick(RISING))
    mainRollMin = -enc.getCount(3);
  mainRollValue = constrain(mainRollValue, mainRollMin, mainRollMax);

  if (DS3.getTriangleClick())
    subRollValue += 2000;
  else if (DS3.getSquareClick())
    subRollValue -= 2000;
  if (limitSW[3].getClick(RISING))
    subRollMax = -enc.getCount(4);
  if (limitSW[4].getClick(RISING))
    subRollMin = -enc.getCount(4);
  subRollValue = constrain(subRollValue, subRollMin, subRollMax);

  if (DS3.getStartClick()) {
    mainRollValue = mainRollMin;
    subRollValue = subRollMin;
    isSheetOpen = false;
    isClothesPinDown = false;
  }

  //腕の自動展開
  if (locationState >= 2 && locationState <= 7) {
    mainRollValue = mainRollMax;
    subRollValue = subRollMax;
  } else {
    mainRollValue = mainRollMin;
    subRollValue = subRollMin;
  }
  //自動でシーツをかける

  switch (sheetState) {
    case 0: //待機
      isSheetOpen = false;
      isClothesPinDown = true;
      if (locationState == 3) {
        isPause = true;
        sheetState++;
      }
      break;
    case 1:
      if (isTargetLocation || DS3.getCircleClick())
        sheetState++;
      break;
    case 2: //シーツ降ろす
      isSheetOpen = true;
      if (limitSW[6].getData() || DS3.getCircleClick())
        sheetState++;
      break;
    case 3: //洗濯ばさみ上げる
      isClothesPinDown = false;
      if (limitSW[7].getData() || DS3.getCircleClick()) {
        isPause = false;
        sheetState++;
      }
    case 4: //横移動
      if (locationState == 6)
        sheetState = 0;

  }

  setDisplay(2, 3, sheetState);

  //  if (isPause && isTargetLocation) {
  //    isSheetOpen = true;
  //    isClothesPinDown = true;
  //
  //  }
  //  if (limitSW[8].getData()) {
  //    isClothesPinDown = false;
  //  }
  //
  //  if (locationState == 3) {
  //    isPause = true;
  //    if (limitSW[6].getData() && limitSW[7].getData())
  //      isPause = false;
  //  }
  //  if (locationState == 6) {
  //    isSheetOpen = false;
  //    isClothesPinDown = false;
  //  }
  Serial.print("isTargetLocation : "); Serial.print(isTargetLocation);
  Serial.print("\t");
  Serial.print("isSheetOpen : "); Serial.print(isSheetOpen);
  Serial.print("\t");
  Serial.print("locationState : "); Serial.print(isTargetLocation);
  Serial.print("\t");


  mainRollUpPid.update(-enc.getCount(3) , mainRollValue);
  subRollUpPid.update(-enc.getCount(4) , subRollValue);


  int mainPower = constrain(mainRollUpPid.getPower(), -50, 80);
  int subPower = constrain(subRollUpPid.getPower(), -50, 80);

  if (DS3.getR1Click())
    isClothesPinDown = !isClothesPinDown;
  int clothesPinValue = 0;
  if (isClothesPinDown && !limitSW[8].getData())
    clothesPinValue = 80;
  else if (!isClothesPinDown && !limitSW[7].getData())
    clothesPinValue = -80;
  else
    clothesPinValue = 0;
  if (DS3.getL1Click())
    isSheetOpen = !isSheetOpen;
  int sheetValue = 0;
  if (isSheetOpen && !limitSW[6].getData())
    sheetValue = -30;
  else if (!isSheetOpen && !limitSW[5].getData())
    sheetValue = 30;
  else
    sheetValue = 0;

  i2cMotorBoard.setMotorData(1, -mainPower);
  i2cMotorBoard.setMotorData(2, -subPower);
  i2cMotorBoard.setMotorData(3, sheetValue);
  i2cMotorBoard.setMotorData(4, -clothesPinValue);

  //  Serial.print("mainRollMax :"); Serial.print(mainRollMax);
  //  Serial.print("\t");
  //  Serial.print("subRollMax :"); Serial.print(subRollMax);
  //  Serial.print("\t");
}
