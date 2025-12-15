#include <SLog.h>

void setup() {
  SLog::begin(115200);
  
  // Set log level (default is INFO)
  SLog::setLogLevel(SLog::DEBUG);
  
  // Enable/disable timestamps (enabled by default)
  SLog::setTimestampEnabled(true);
  
  // Basic logging with different levels
  SLog::debug("This is a debug message");
  SLog::info("System initialized");
  SLog::warning("Low memory detected");
  SLog::error("Sensor read failed!");
  
  // Formatted logging
  int sensorValue = analogRead(A0);
  float temperature = 23.5;
  
  SLog::debugf("Sensor value: %d", sensorValue);
  SLog::infof("Temperature: %.2f°C", temperature);
  SLog::warningf("Battery level: %d%% - Please recharge", 15);
  SLog::errorf("Error code: 0x%04X at line %d", 0xDEAD, __LINE__);
  
  // Mixed print and println
  SLog::print("Processing... ", SLog::INFO);
  delay(100);
  SLog::println("Done", SLog::INFO);
  
  // Change log level at runtime
  SLog::setLogLevel(SLog::WARNING);
  SLog::debug("This won't be shown");  // Won't appear
  SLog::error("This error will be shown");
}

void loop() {
  static int counter = 0;
  
  // Log with different levels based on conditions
  if (counter % 100 == 0) {
    SLog::infof("Loop counter: %d", counter);
  }
  
  if (counter > 1000 && counter % 500 == 0) {
    SLog::warning("High loop count detected");
  }
  
  // Simulate occasional error
  if (random(1000) < 5) {
    SLog::error("Random error occurred!");
  }
  
  counter++;
  delay(10);
}

#include <esp_heap_caps.h>

void checkStack() {
  UBaseType_t watermark = uxTaskGetStackHighWaterMark(NULL);
  Serial.printf("Stack high watermark: %d bytes\n", watermark);
}