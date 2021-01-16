// This program is intended to take a reading from the
// DS18B20 temperature sensor on an Arduino Uno.
// These temperature sensors are probably more accurate and have faster read times
// than the cheaper DHT11 and DHT22 sensors (and have waterproof variants)

// NOTE: If the sensor outputs a reading of -127 degrees,
// then the sensor is fried and a new one should be replaced.

// Libraries
// DallasTemperature(Edison) for i686 - Version: Latest
#include <DallasTemperature.h>

// OneWire(Edison) for i686 - Version: Latest
#include <OneWire.h>


#define ONE_WIRE_BUS 2 // data wire plugged into pin 2
OneWire oneWire(ONE_WIRE_BUS); // creating oneWire instance to communicate with sensor
DallasTemperature sensors(&oneWire); // passes oneWire reference to DallasTemperature


void setup() {
    Serial.begin(9600);
    Serial.println("Temperature Sensor Test");
    sensors.begin();
}

void loop() {
    Serial.print("Requesting temperatures...");
    sensors.requestTemperatures(); // issues global request to all devices on bus
    delay(100); // makes it look like the program is doing something ;)
    Serial.println("DONE");
    delay(750); // adding delay. Docs say that sensor is able to sample every 750ms.
    Serial.print("Temperature for the device is: ");
    Serial.println(sensors.getTempCByIndex(0)); // ByIndex() added because...
    // multiple DS18B20 sensors can be on same bus. 0 index refers to first IC on wire.

    delay(500); // used so we don't get crazytown serial prints
}
