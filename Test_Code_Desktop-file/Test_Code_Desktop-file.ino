// I don't know if it's because it's the online IDE, or if the sensor isn't working properly, but the monitor read-out is "stuck" at -127.0 deg.

// DallasTemperature(Edison) for i686 - Version: Latest 
#include <DallasTemperature.h>

// OneWire(Edison) for i686 - Version: Latest 
#include <OneWire.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature Sensors(&oneWire);


void setup() {
    Serial.begin(9600);
    Serial.println("Dallas Temperature Demo");
    Sensors.begin();
}

void loop() {
    Serial.print("Requesting temperatures...");
    Sensors.requestTemperatures();
    delay(100); // makes it look like the program is doing something ;)
    Serial.println("DONE");
    delay(750); // adding delay. Docs say that sensor is able to sample every 750ms.
    Serial.print("Temperature for the device is: ");
    Serial.println(Sensors.getTempCByIndex(0));
    
    delay(500);
}
