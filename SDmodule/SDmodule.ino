#include <SPI.h>
#include <SD.h>

#include "slaveReceiver.h"
#include "slaveSender.h"
#include "sw_controller.h"

const int chipSelect = 10;
const int ADDRESS = 12;

const int PIN[4][2] = {
  {2, 3},
  {4, 5},
  {8, 9},
  {6, 7}
};

slaveSender i2cSend(1); //arraySize
slaveReceiver i2cRecerve(3);
bool toggleSW[4];

void setup() {
  Wire.begin(ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
  for (int i = 0; i < 4; i++) {
    pinMode(PIN[i][0], OUTPUT);
    pinMode(PIN[i][1], INPUT_PULLUP);
  }

}

void loop() {
  for (int i = 0; i < 4; i++) {
    toggleSW[i] = digitalRead(PIN[i][1]);
    digitalWrite(PIN[i][0], toggleSW[i]);
    i2cSend.setBitData(0, i, toggleSW[i]);
    //    Serial.print(toggleSW[i]);
  }
  i2cSend.show();

  //  Serial.println();

}
void requestEvent() {
  i2cSend.update();
}

void receiveEvent(int howMany) {
  i2cRecerve.Update();
}
