#pragma once
class swController {
  private:
    bool oldData = 0;
    bool newData = 0;
    bool clickDataRising, clickDataFalling, toggleData, changeData;
    int countUpData = 0;

  public:
    void update(bool buttonState) {
      newData = buttonState;
      changeData = oldData != newData;
      oldData && !newData ?
      clickDataFalling = true : clickDataFalling = false;
      !oldData && newData ?
      clickDataRising = true : clickDataRising = false;
      oldData = newData;
      if (clickDataRising)  toggleData ^= 1;
      if (clickDataRising)  countUpData++;
    }
    int countDataReset(){
    	 countUpData = 0;
    }

    bool getData() {
      return newData;
    }
    bool getChange() {
      return changeData;
    }
    bool getClick(int mode = RISING) {
    	if(mode == RISING)
      	return clickDataRising;
    	if(mode == FALLING)
      	return clickDataFalling;
      
    }
    bool getToggle() {
      return toggleData;
    }
    int getCountUp() {
      return countUpData;
    }
    void show() {
      Serial.print(newData); Serial.print(",");
      Serial.print(changeData); Serial.print(",");
      Serial.print(clickDataRising); Serial.print(",");
      Serial.print(toggleData); Serial.print(",");
      Serial.print(countUpData); Serial.print("\t");
    }
};