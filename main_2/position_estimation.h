#pragma once

class positionEstimmation {
  private:
    long oldXenc = 0;
    long oldYenc = 0;
    float oldGyro = 0;
    long nowXpulse = 0;
    long nowYpulse = 0;
    int nowX = 0;
    int nowY = 0;
    float offsetX = 600;
    float offsetY = 1800;

    int getmm(long pulse) {
      return (pulse * 50.8 * PI) / 4096;
    }

  public:
    void update(long encX, long encY, int gyro) {
      nowXpulse += (encX - oldXenc) * cos((oldGyro + gyro) / 2 * (1) * PI / 180);
      nowYpulse += (encY - oldYenc) * cos((oldGyro + gyro) / 2 * (-1) * PI / 180);

      nowXpulse += (encY - oldYenc) * sin(((oldGyro + gyro) / 2 * (1)) * PI / 180);
      nowYpulse += (encX - oldXenc) * sin(((oldGyro + gyro) / 2 * (-1)) * PI / 180);

      oldXenc = encX;
      oldYenc = encY;
      oldGyro = gyro;
      
      nowX = getmm(nowXpulse) + offsetX;
      nowY = getmm(nowYpulse) + offsetY;
    }
    void reset(){
      nowXpulse = nowYpulse = 0;
    }
    int getNowX() {
      return nowX;
    }
    int getNowY() {
      return nowY;
    }
    void show() {
      Serial.print("gyro : ");  Serial.print(oldGyro);
      Serial.print("\t");
      Serial.print("nowX : ");  Serial.print(nowX);
      Serial.print("\t");
      Serial.print("nowy : ");  Serial.print(nowY);
      Serial.print("\t");
    }
};
