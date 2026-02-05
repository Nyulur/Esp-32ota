#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>

const char* WIFI_SSID = "YOUR_WIFI";
const char* WIFI_PASS = "YOUR_PASS";

const char* AP_SSID   = "ESP32-OTA";
const char* AP_PASS   = "12345678";

WebServer server(80);

void setupWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long t0 = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t0 < 8000) {
    delay(100);
  }

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);
  }
}

void setupWebOTA() {
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html",
      "<h2>ESP32 WebOTA</h2>"
      "<p><a href='/update'>Firmware update</a></p>");
  });

  server.on("/update", HTTP_GET, []() {
    server.send(200, "text/html",
      "<h3>Upload firmware (.bin)</h3>"
      "<form method='POST' action='/update' enctype='multipart/form-data'>"
      "<input type='file' name='update'>"
      "<input type='submit' value='Upload'>"
      "</form>");
  });

  server.on("/update", HTTP_POST,
    []() {
      server.send(200, "text/plain",
        Update.hasError() ? "Update FAILED" : "Update OK, rebooting...");
      delay(250);
      ESP.restart();
    },
    []() {
      HTTPUpload& up = server.upload();
      if (up.status == UPLOAD_FILE_START) {
        Update.begin(UPDATE_SIZE_UNKNOWN);
      } else if (up.status == UPLOAD_FILE_WRITE) {
        Update.write(up.buf, up.currentSize);
      } else if (up.status == UPLOAD_FILE_END) {
        Update.end(true);
      }
    }
  );

  server.begin();
}

void setup() {
  Serial.begin(115200);
  delay(200);
  setupWiFi();
  setupWebOTA();
}

void loop() {
  server.handleClient();
}
