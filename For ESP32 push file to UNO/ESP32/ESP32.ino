#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

const char* ssid = "DESKTOP-O841IQH 3323";
const char* password = "38=448qQ";


WebServer server(80);

void setup() {
  // Start the serial communication
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  // Print the IP address
  Serial.println(WiFi.localIP());

  // Start the server
  server.on("/upload", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Upload: %s\n", upload.filename.c_str());
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      // Send the code file to the Arduino UNO via serial communication
      Serial.write(upload.buf, upload.currentSize);
    } else if (upload.status == UPLOAD_FILE_END) {
      Serial.printf("Upload Success: %u\n", upload.totalSize);
    }
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
