#include<Wire.h>
#include "limitsw.h"
#include "slaveSender.h"

#define address 15

limitsw limitSW[15] = {2, 3, 4, 5, 6, 7, 8, 9, 17, 16, 12, 15, 14, 10, 11};
slaveSender i2cSend(2); //arraySize

void setup() {
  Wire.begin(address);
  Wire.onRequest(requestEvent);
  Serial.begin(115200);
//  limitSW[5].setReverse();
}

void loop() {
  for (int i = 0; i < 8; i++)
    i2cSend.setBitData(1, i + 1, limitSW[i].getState());
  for (int i = 8; i < 15; i++)
    i2cSend.setBitData(2, i - 7, limitSW[i].getState());
  show();
}

void show() {
  i2cSend.show();
  //    for (int i = 0; i < 15; i++)
  //      limitSW[i].show();
  //    Serial.println();
  //  Serial.println(analogRead(A3));
}

void requestEvent() {
  i2cSend.Update();
}
