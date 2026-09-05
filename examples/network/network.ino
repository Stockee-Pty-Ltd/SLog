#include <SLog.h>
#include <WiFi.h>  // Or Ethernet, depending on your board

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

void setup() {
  SLog::begin(115200);
  SLog::setLogLevel(SLog::DEBUG);
  
  SLog::info("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    SLog::print(".");
    
    if (millis() - startTime > 10000) {
      SLog::error("WiFi connection failed!");
      return;
    }
  }
  
  SLog::infof("\nConnected! IP address: %s", WiFi.localIP().toString().c_str());
  
  // Log memory usage (example for ESP32)
  #ifdef ESP32
    SLog::debugf("Free heap: %d bytes", ESP.getFreeHeap());
  #endif
}

void loop() {
  // Your network application code here
  static int requestCount = 0;
  
  SLog::debugf("Making request #%d", ++requestCount);
  
  // Simulate network operations
  if (requestCount % 10 == 0) {
    SLog::infof("Completed %d requests", requestCount);
  }
  
  delay(5000);
}