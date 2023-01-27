void setup() {
  // Start the serial communication
  Serial.begin(115200);
}

void loop() {
  // Receive the code file from the ESP32
  if (Serial.available() > 0) {
    String codeFile = Serial.readString();
    // Process the code file
    // ...
  }
}
