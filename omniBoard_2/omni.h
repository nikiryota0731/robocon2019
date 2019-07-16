#pragma once

class omni {
  private:
    int motorPower;
    int motorAngleData;
  public:
    omni(int motorAngle) {
      motorAngleData = motorAngle;
    }
    int drive(double angle, int power, int turn) {
      motorPower = sin((angle - motorAngleData) * (PI / 180)) * power;
      motorPower += turn - 127;
      return motorPower;
    }
    void show(){
//      Serial.print(motorAngleData);
//      Serial.print(" : ");
      Serial.print(motorPower);
      Serial.print(",\t");
    }
};
