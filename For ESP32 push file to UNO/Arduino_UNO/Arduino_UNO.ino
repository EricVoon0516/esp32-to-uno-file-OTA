#include <EEPROM.h>

void setup() {
  Serial.begin(9600); // start serial communication at 9600 baud
}

void loop() {
  int incomingByte = 0; // variable to store incoming data
  int address = 0; // starting address for storing data

  // wait for incoming data from ESP32
  if (Serial.available() > 0) {
    incomingByte = Serial.read();

    // write incoming data to flash memory
    EEPROM.write(address, incomingByte);
    address++;

    // increment the address for the next incoming byte
    if (address == EEPROM.length()) {
      address = 0;
    }
  }
}
