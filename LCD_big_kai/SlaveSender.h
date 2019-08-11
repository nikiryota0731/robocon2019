/*
  @progma I2C通信でslaveがmasterに送るクラス
  @date 2018/07/01
*/

#pragma once
#include <arduino.h>
#include <Wire.h>

class SlaveSender {
  private:
    const int I2CADDRESS;
    byte* data;
    int Size;

  public:
    SlaveSender(int arraySize);
    // デストラクタ
    virtual ~SlaveSender() {
      delete[] data;
    }
    void setData(int arrayNum, byte value);
    void setBitData(int arrayNum, int bitNum, bool value);
    void Send_Bit_data(byte byte_Data[], int u);
    void reset();
    void update();
    void show();
};

extern SlaveSender i2cSender;
