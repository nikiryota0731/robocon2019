#pragma once

class limitsw {
  private:
    int pin;
    bool reverseMode = false;

  public:

    limitsw(int pin_A) {
      pinMode(pin_A, INPUT_PULLUP);
      pin = pin_A;
    }
    void setReverse() {
      reverseMode = true;
    }
    int getState() {
      bool state = !digitalRead(pin);
      if (reverseMode)
        state = !state;
      return state;
    }

    void show() {
      Serial.print(getState());
      Serial.print("\t");
    }

};
