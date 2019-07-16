#pragma once
#include <arduino.h>

/************************************
   Include
************************************/

#include "libs/controller_manager_ds3.h"
#include "libs/i2c_master_writer.h"
#include "libs/i2c_master_reader.h"
#include "libs/enc_board_mbed.h"
#include "libs/loop_cycle_controller.h"
#include "libs/pid_controller.h"
#include "libs/sw_controller.h"
#include "gyro_serial.h"
#include "position_estimation.h"
/************************************
   Instace
************************************/

extern ControllerManagerDS3 DS3;
extern I2CMasterWriter i2cOmni, i2cLCD, i2cMotorBoard, i2cServoBoard, i2csolenoidBoard;
extern I2CMasterReader i2ReceiveLCD, i2cSW;
extern EncoderBoardMbed enc;
extern LoopCycleController loopPeriodUs;
extern PidController gyroPid, omniXPid, omniYPid;
extern PidController mainRollUpPid, subRollUpPid;
extern swController DS3RightHatX, LCDSW[4], limitSW[15];
extern gyroSerial gyro;
extern positionEstimmation position;

extern bool isZoneRed, isStart;


extern int locationState;
extern bool isPause, isTargetLocation;

/************************************
   Functions
************************************/

//all_update.cpp
void allUpdate();

//function.cpp
int getAngleDeg(int, int, int, int);
int getDistance(int, int, int, int);
void setDisplay(uint8_t dataPageNum, uint8_t dataNum, int SendData);

//display.cpp
void display();

//motorBoard.cpp
void firstArm();
void secondArm();

//omniAuto.cpp
void omniAuto(int nowX, int nowY);
bool getIsTargetLocation(int nowX, int nowY, int moveX, int moveY);

//omniManual
void omniManual(int moveX, int moveY, int turnXX);


//position_estimation.cpp
int getmm(long pulse);
void positionEstimation();
