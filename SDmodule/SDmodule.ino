#include <SPI.h>
#include <SD.h>

#include "slaveReceiver.h"
#include "slaveSender.h"

const int chipSelect = 4;
const int ADDRESS = 31;

slaveSender i2cSend(1); //arraySize
slaveReceiver i2cRecerve(3);

void setup() {
  Wire.begin(ADDRESS);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
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

}

void loop() {

}
void receiveEvent(int howMany) {
  i2cRecerve.Update();
}
