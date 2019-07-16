#ifndef DEF_ControllerManager_H
#define DEF_ControllerManager_H

#include <Wire.h>

constexpr int16_t CutAnalogValue = 20;  // アナログスティックの中間不感値
constexpr int16_t CutValue = CutAnalogValue * 2;

struct buttonData {
  bool oldData = 0;
  bool newData = 0;
};

class ControllerManagerDS3 {

  private:

    bool Select, L3, R3, START, PS, Up, Right, Down, Left;
    bool L2, R2, L1, R1, Triangle, Circle, Cross, Square;
    bool Touch;

    int16_t LeftHatX, LeftHatY;
    int16_t RightHatX, RightHatY;
    int16_t AnalogL2, AnalogR2;

    int16_t RightHatX_map, RightHatY_map;
    int16_t LeftHatX_map, LeftHatY_map;

    int16_t theta;
    uint16_t r;
    int16_t LeftxAxis, LeftyAxis, RightxAxis;

    buttonData buttonStock[17];
    bool Click_Data[17] = {};
    bool Toggle_Data[17] = {};

    int CountUp_Data[17] = {};

    const int I2C_Address;

  public:

    ControllerManagerDS3(uint8_t Address) : I2C_Address(Address) {}

    void update() {
      Wire.requestFrom(I2C_Address, 9);
      uint8_t buf[] = { 0, 0, 127, 127, 127, 127, 0, 0, 0};
      while (Wire.available()) {
        buf[0] = Wire.read();
        buf[1] = Wire.read();
        buf[2] = Wire.read();
        buf[3] = Wire.read();
        buf[4] = Wire.read();
        buf[5] = Wire.read();
        buf[6] = Wire.read();
        buf[7] = Wire.read();
        buf[8] = Wire.read();
      }
      Select = bitRead(buf[0], 0);
      L3 = bitRead(buf[0], 1);
      R3 = bitRead(buf[0], 2);
      START = bitRead(buf[0], 3);
      Up = bitRead(buf[0], 4);
      Right = bitRead(buf[0], 5);
      Down = bitRead(buf[0], 6);
      Left = bitRead(buf[0], 7);

      L2 = bitRead(buf[1], 0);
      R2 = bitRead(buf[1], 1);
      L1 = bitRead(buf[1], 2);
      R1 = bitRead(buf[1], 3);
      Triangle = bitRead(buf[1], 4);
      Circle = bitRead(buf[1], 5);
      Cross = bitRead(buf[1], 6);
      Square = bitRead(buf[1], 7);

      PS = bitRead(buf[8], 0);
      Touch = 0 ;

      buttonStock[0].newData = Triangle;
      buttonStock[1].newData = Circle;
      buttonStock[2].newData = Cross;
      buttonStock[3].newData = Square;

      buttonStock[4].newData = Up;
      buttonStock[5].newData = Right;
      buttonStock[6].newData = Down;
      buttonStock[7].newData = Left;

      buttonStock[8].newData = START;
      buttonStock[9].newData = Select;

      buttonStock[10].newData = Touch;

      buttonStock[11].newData = L2;
      buttonStock[12].newData = R2;
      buttonStock[13].newData = L1;
      buttonStock[14].newData = R1;
      buttonStock[15].newData = L3;
      buttonStock[16].newData = R3;

      for (int i = 0; i < 17; i++) {
        if (buttonStock[i].oldData == 0 && buttonStock[i].newData == 1) {
          Click_Data[i] = true;
        }
        else
          Click_Data[i] = false;

        buttonStock[i].oldData = buttonStock[i].newData;
      }

      for (int i = 0; i < 17; i++)
        if (Click_Data[i])   Toggle_Data[i] ^= 1;

      for (int i = 0; i < 17; i++)
        if (Click_Data[i])       CountUp_Data[i]++;

      if (PS) {
        for (int i = 0; i < 17; i++) {
          CountUp_Data[i] = 0;
          
        }
      }

      RightHatX_map = buf[2] - 127;
      RightHatY_map = -(buf[3] - 127);
      LeftHatX_map = buf[4] - 127;
      LeftHatY_map = -(buf[5] - 127);

      RightHatX = buf[2];
      RightHatY = buf[3];
      LeftHatX = buf[4];
      LeftHatY = buf[5];
      AnalogL2 = buf[6];
      AnalogR2 = buf[7];

      r = sqrt((LeftHatX * LeftHatX) + (LeftHatY * LeftHatY)) * 2;
      r = constrain(r, 0, 255);

      float Rad = atan2(LeftHatY, LeftHatX);
      theta = round(degrees(Rad));
      if (theta < 0) theta += 360;
      if (theta > 359) theta -= 360;

      if (r < CutValue) {
        r = 0;
        LeftxAxis = 0;
        LeftyAxis = 0;
      }
      else {
        r = map(r, CutValue, 255, 0, 255);
        LeftxAxis = r * cos(radians((float)theta));
        LeftyAxis = r * sin(radians((float)theta));
      }

      if (-CutAnalogValue < RightHatX && RightHatX < CutAnalogValue) {
        RightxAxis = 0;
      }
      else {
        if (RightHatX < 0) RightxAxis = map(RightHatX, -127, -CutAnalogValue, -127, 0);
        else RightxAxis = map(RightHatX, CutAnalogValue, 128, 0, 128);
      }
    }
    bool getTouch() {
      return Touch;
    }
    bool getPS() {
      return PS;
    }
    bool getStart() {
      return START;
    }
    bool getSelect() {
      return Select;
    }
    bool getL3() {
      return L3;
    }
    bool getR3() {
      return R3;
    }
    bool getUp() {
      return Up;
    }
    bool getRight() {
      return Right;
    }
    bool getDown() {
      return Down;
    }
    bool getLeft() {
      return Left;
    }
    bool getL2() {
      return L2;
    }
    bool getR2() {
      return R2;
    }
    bool getL1() {
      return L1;
    }
    bool getR1() {
      return R1;
    }
    bool getTriangle() {
      return Triangle;
    }
    bool getCircle() {
      return Circle;
    }
    bool getCross() {
      return Cross;
    }
    bool getSquare() {
      return Square;
    }
    /* Click */
    bool getTriangleClick() {
      return Click_Data[0];
    }
    bool getCircleClick() {
      return Click_Data[1];
    }
    bool getCrossClick() {
      return Click_Data[2];
    }
    bool getSquareClick() {
      return Click_Data[3];
    }

    bool getUpClick() {
      return Click_Data[4];
    }
    bool getRightClick() {
      return Click_Data[5];
    }
    bool getDownClick() {
      return Click_Data[6];
    }
    bool getLeftClick() {
      return Click_Data[7];
    }

    bool getStartClick() {
      return Click_Data[8];
    }
    bool getShareClick() {
      return Click_Data[9];
    }
    bool getTouchClick() {
      return Click_Data[10];
    }

    bool getL2Click() {
      return Click_Data[11];
    }
    bool getR2Click() {
      return Click_Data[12];
    }
    bool getL1Click() {
      return Click_Data[13];
    }
    bool getR1Click() {
      return Click_Data[14];
    }
    bool getL3Click() {
      return Click_Data[15];
    }
    bool getR3Click() {
      return Click_Data[16];
    }

    /*    Toggle    */
    bool getTriangleToggle() {
      return Toggle_Data[0];
    }
    bool getCircleToggle() {
      return Toggle_Data[1];
    }
    bool getCrossToggle() {
      return Toggle_Data[2];
    }
    bool getSquareToggle() {
      return Toggle_Data[3];
    }

    bool getUpToggle() {
      return Toggle_Data[4];
    }
    bool getRightToggle() {
      return Toggle_Data[5];
    }
    bool getDownToggle() {
      return Toggle_Data[6];
    }
    bool getLeftToggle() {
      return Toggle_Data[7];
    }

    bool getStartToggle() {
      return Toggle_Data[8];
    }
    bool getSelectToggle() {
      return Toggle_Data[9];
    }
    bool getTouchToggle() {
      return Toggle_Data[10];
    }

    bool getL2Toggle() {
      return Toggle_Data[11];
    }
    bool getR2Toggle() {
      return Toggle_Data[12];
    }
    bool getL1Toggle() {
      return Toggle_Data[13];
    }
    bool getR1Toggle() {
      return Toggle_Data[14];
    }
    bool getL3Toggle() {
      return Toggle_Data[15];
    }
    bool getR3Toggle() {
      return Toggle_Data[16];
    }

    /*      CountUp     */
    int getTriangleCountUp() {
      return CountUp_Data[0];
    }
    int getCircleCountUp() {
      return CountUp_Data[1];
    }
    int getCrossCountUp() {
      return CountUp_Data[2];
    }
    int getSquareCountUp() {
      return CountUp_Data[3];
    }

    int getUpCountUp() {
      return CountUp_Data[4];
    }
    int getRightCountUp() {
      return CountUp_Data[5];
    }
    int getDownCountUp() {
      return CountUp_Data[6];
    }
    int getLeftCountUp() {
      return CountUp_Data[7];
    }

    int getStartCountUp() {
      return CountUp_Data[8];
    }
    int getShareCountUp() {
      return CountUp_Data[9];
    }
    int getTouchCountUp() {
      return CountUp_Data[10];
    }

    int getL2CountUp() {
      return CountUp_Data[11];
    }
    int getR2CountUp() {
      return CountUp_Data[12];
    }
    int getL1CountUp() {
      return CountUp_Data[13];
    }
    int getR1CountUp() {
      return CountUp_Data[14];
    }
    int getL3CountUp() {
      return CountUp_Data[15];
    }
    int getR3CountUp() {
      return CountUp_Data[16];
    }
    
    //countReset//
    void TriangleCountUpReset() {
      CountUp_Data[0] = 0;
    }
    void CircleCountUpReset() {
      CountUp_Data[1] = 0;
    }
    void CrossCountUpReset() {
      CountUp_Data[2] = 0;
    }
    void SquareCountUpReset() {
      CountUp_Data[3] = 0;
    }

    void UpResetCountUpReset() {
      CountUp_Data[4] = 0;
    }
    void RightCountUpReset() {
      CountUp_Data[5] = 0;
    }
    void DownCountUpReset() {
      CountUp_Data[6] = 0;
    }
    void LeftCountUpReset() {
      CountUp_Data[7] = 0;
    }

    void StartCountUpReset() {
      CountUp_Data[8] = 0;
    }
    void ShareCountUpReset() {
      CountUp_Data[9] = 0;
    }
    void TouchCountUpReset() {
      CountUp_Data[10] = 0;
    }

    void L2CountUpReset() {
      CountUp_Data[11] = 0;
    }
    void R2CountUpReset() {
      CountUp_Data[12] = 0;
    }
    void L1CountUpReset() {
      CountUp_Data[13] = 0;
    }
    void R1CountUpReset() {
      CountUp_Data[14] = 0;
    }
    void L3CountUpReset() {
      CountUp_Data[15] = 0;
    }
    void R3CountUpReset() {
      CountUp_Data[16] = 0;
    }

    int16_t getLeftHatX() {
      return LeftHatX;
    }
    int16_t getLeftHatY() {
      return LeftHatY;
    }
    int16_t getRightHatX() {
      return RightHatX;
    }
    int16_t getRightHatY() {
      return RightHatY;
    }
    int16_t getAnalogL2() {
      return AnalogL2;
    }
    int16_t getAnalogR2() {
      return AnalogR2;
    }

    int16_t gettheta() {
      return theta;
    }
    uint16_t getr() {
      return r;
    }
    int16_t getLeftxAxis() {
      return LeftxAxis;
    }
    int16_t getLeftyAxis() {
      return LeftyAxis;
    }
    int16_t getRightxAxis() {
      return RightxAxis;
    }
};

#endif

