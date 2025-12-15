#include <SLog.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  SLog::begin(115200);
  SLog::setLogLevel(SLog::INFO);
  
  dht.begin();
  SLog::info("DHT Sensor initialized");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    SLog::error("Failed to read from DHT sensor!");
  } else {
    SLog::debugf("Raw values - Temp: %.2f, Hum: %.2f", temperature, humidity);
    
    // Log with different levels based on conditions
    SLog::infof("Temperature: %.1f°C, Humidity: %.1f%%", temperature, humidity);
    
    if (temperature > 30.0) {
      SLog::warning("High temperature warning!");
    }
    
    if (humidity > 80.0) {
      SLog::warning("High humidity detected");
    }
  }
  
  delay(2000);
}