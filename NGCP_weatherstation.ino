#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>

// Pin definitions
#define DHT_PIN     21
#define LM393_PIN   18
#define DHT_TYPE    DHT22

// Sensor objects
BH1750 lightMeter;
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("=== Sensor Test ===");

  // BH1750 - custom I2C pins (SDA=22, SCL=23)
  Wire.begin(22, 23); // SDA, SCL
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("[BH1750]  OK");
  } else {
    Serial.println("[BH1750]  FAILED - check wiring");
  }

  // DHT22
  dht.begin();
  Serial.println("[DHT22]   OK");

  // LM393 (digital input)
  pinMode(LM393_PIN, INPUT);
  Serial.println("[LM393]   OK");

  Serial.println("-------------------");
}

void loop() {
  // --- BH1750 ---
  float lux = lightMeter.readLightLevel();
  if (lux >= 0) {
    Serial.print("[BH1750]  Light: ");
    Serial.print(lux);
    Serial.println(" lx");
  } else {
    Serial.println("[BH1750]  Read error");
  }

  // --- DHT22 ---
  float humidity    = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("[DHT22]   Read error - check wiring");
  } else {
    Serial.print("[DHT22]   Temp: ");
    Serial.print(temperature);
    Serial.print(" C  |  Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  // --- LM393 ---
  int lm393State = digitalRead(LM393_PIN);
  Serial.print("[LM393]   Signal: ");
  Serial.println(lm393State == HIGH ? "HIGH (no trigger)" : "LOW (triggered)");

  Serial.println("-------------------");
  delay(2000);
}