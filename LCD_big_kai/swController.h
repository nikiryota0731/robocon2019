#pragma once

struct buttonData {
  bool oldData = 0;
  bool newData = 0;
};

class swController {
  private:
    buttonData buttonStock;
    bool clickData, toggleData, changeData;
    int countUpData = 0;

  public:
    void update(bool buttonState);
    bool getData();
    bool getChange();
    bool getClick();
    bool getToggle();
    int getCountUp();
    void show();
};

void swController::update(bool buttonState) {
  buttonStock.newData = buttonState;
  changeData = buttonStock.oldData != buttonStock.newData;
  !buttonStock.oldData && buttonStock.newData ?
  clickData = true : clickData = false;
  buttonStock.oldData = buttonStock.newData;
  if (clickData)  toggleData ^= 1;
  if (clickData)  countUpData++;
}

bool swController::getData() {
  return buttonStock.newData;
}
bool swController::getChange() {
  return changeData;
}
bool swController::getClick() {
  return clickData;
}
bool swController::getToggle() {
  return toggleData;
}
int swController::getCountUp() {
  return countUpData;
}

void swController::show() {
  Serial.print(buttonStock.newData); Serial.print("\t");
  Serial.print(clickData); Serial.print("\t");
  Serial.print(toggleData); Serial.print("\t");
  Serial.print(countUpData); Serial.print("\t");
}
