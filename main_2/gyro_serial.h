#pragma once

class gyroSerial {
  private:
    float rawYaw = 0;
    float i = 0;
    float gyroOffset = 0;

  public:
    void init() {
        update();
        setOffset();
    }

    void update() {
      //      int bufValue = Serial.available();
      //      Serial.print(bufValue);
      if (Serial.available() >= 3) {
        //        int data = Serial.available()
        if (Serial.read() == 'H') {
          rawYaw = (float)((Serial.read() << 8) | Serial.read()) / (float)100;
          rawYaw -= gyroOffset;
          if (rawYaw > 180)
            rawYaw -= 360;
          else if (rawYaw < -180)
            rawYaw += 360;
          i = rawYaw;
          while (Serial.available() > 3) {
            Serial.read();
          }
          return;
        }
      }
      while (Serial.available() > 3) {
        Serial.read();
      }
      return;
    }

    double getData() {
      return i;
    }

    void setOffset() {
      float rawYaw = getData() + gyroOffset;
      if (rawYaw > 180)
        rawYaw -= 360;
      else if (rawYaw < -180)
        rawYaw += 360;
      gyroOffset = rawYaw;
    }

    void show() {
      Serial.print(i);
      Serial.print('\t');
    }
};
