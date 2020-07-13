// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain. Modified by Jamison Griffith for use with a Thing ESP32 board.

// Requires the DHT Sensor Library (dependant on the Adafruit Unified Sensor lib)

#include "DHT.h"

#define DHTPIN 25     
// tried using pin 36 but didn't work. Likely due to 34 - 39 being designated as input-only?
// See official ESP32 doc for further detail: https://learn.sparkfun.com/tutorials/esp32-thing-hookup-guide

#define DHTTYPE DHT11   // DHT 11

#define SOILPIN 36 // trying pot as analog input

#define SOILPOWER 13 // using digital pin to power the sensor, instead of having it on all the time

int soilVal = 0; 


// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  pinMode(SOILPOWER, OUTPUT);
  digitalWrite(SOILPOWER, LOW); // setting power pin off
  
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);


  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print("°F ");
  Serial.print("Soil Moisture: ");
  Serial.println(readSoil());
}

// this function returns an analog value related to how moist the soil is
int readSoil() {
  digitalWrite(SOILPOWER, HIGH); // turns soil sensor on
  delay(10);
  soilVal = analogRead(SOILPIN);
  delay(2000);
  digitalWrite(SOILPOWER, LOW);
  return soilVal;
}
