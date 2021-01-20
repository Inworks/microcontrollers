/*
    Video: https://www.youtube.com/watch?v=oCMOYS71NIU
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updated by chegewara
    Soil sensor functionality added by Jamison Griffith

   Create a BLE server that, once we receive a connection, will send periodic notifications.
   The service advertises itself as: 4fafc201-1fb5-459e-8fcc-c5c9c331914b
   And has a characteristic of: beb5483e-36e1-4688-b7f5-ea07361b26a8

   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create a BLE Service
   3. Create a BLE Characteristic on the Service
   4. Create a BLE Descriptor on the characteristic
   5. Start the service.
   6. Start advertising.

   A connect hander associated with the server starts a background task that performs notification
   every couple of seconds.
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <sstream> // used for testing?
#include <string> // used for testing?
#include <iostream> // used for testing?

using namespace std;

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
//
/*
  _  _                          _
 | || |___ _  _   _  _ ___ _  _| |
 | __ / -_) || | | || / _ \ || |_|
 |_||_\___|\_, |  \_, \___/\_,_(_)
           |__/   |__/
*/
// UPDATE: I was adding multiple UUID's for individual sensors
// and going to implement a loop to iterate them, but haven't finished
// Bluetooth service and rest of program only refers to TEMP_UUID
#define TEMP_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define HUMID_UUID      "4e88292e-c534-11ea-87d0-0242ac130003"
#define SOIL_UUID     "4e882b40-c534-11ea-87d0-0242ac130003"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define SOILPIN 36 // pin to read soil sensor value
#define SOILPOWER 13 // using digital pin to power the sensor, instead of having it on all the time

int soilVal = 0;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};


// Most of this setup loop is initializing the Bluetooth service
void setup() {
  Serial.begin(115200);
  Serial.println("Starting up BLE");

  pinMode(SOILPOWER, OUTPUT);
  digitalWrite(SOILPOWER, LOW); // setting power pin off

  // Create the BLE Device
  BLEDevice::init("Konbit.farm - Site 32");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(TEMP_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(TEMP_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}

/*
  __  __          _                  _             _        _
 |  \/  |___ __ _| |_   __ _ _ _  __| |  _ __  ___| |_ __ _| |_ ___  ___ ___
 | |\/| / -_) _` |  _| / _` | ' \/ _` | | '_ \/ _ \  _/ _` |  _/ _ \/ -_|_-<
 |_|  |_\___\__,_|\__| \__,_|_||_\__,_| | .__/\___/\__\__,_|\__\___/\___/__/
                                        |_|
*/
void loop() {
    // notify changed value
    if (deviceConnected) {
        string test = ""; //should clear out previous assignment
        int soilNum = readSoil(); // readSoil function is listed below
        Serial.println(soilNum);
        soil = soilStatus(soilNum); //soilStatus changes # to human readable
        Serial.println(soil.c_str()); // apparently strings in C and C++ are different
        // and Bluetooth won't properly send C++ strings-- thus the .c_str method.

        //pCharacteristic->setValue((uint8_t*)&value, 4); I have no idea what I was doing here
        pCharacteristic->setValue(test.c_str());
        pCharacteristic->notify();
        delay(500); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
    }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}

/*
  ___             _   _
 | __|  _ _ _  __| |_(_)___ _ _  ___
 | _| || | ' \/ _|  _| / _ \ ' \(_-<
 |_| \_,_|_||_\__|\__|_\___/_||_/__/

*/

// This function turns the soil power pin on takes an analog read
// and then turns back off. The choice to have it take measurements
// itermitantly is to save battery power.
int readSoil() {
  digitalWrite(SOILPOWER, HIGH); // turns soil sensor on
  delay(1000);
  soilVal = analogRead(SOILPIN);
  delay(1000);
  digitalWrite(SOILPOWER, LOW);
  return soilVal;
}

// This function takes an integer and then relates it into human-readable.
// NOTE: These values were obtained by testing in ~5 different soils of varying
// moisture. 0 is bone-dry, or sensor not connected, >2900 is super wet soil.
string soilStatus(int N) {
  string status1 = "Please insert sensor into soil.";
  string status2 = "Soil Status: Very Dry";
  string status3 = "Soil Status: Moderately Dry";
  string status4 = "Soil Status: Moist";
  string status5 = "Soil Status: Wet";
  string status6 = "Sensor error. Check wiring.";

    if (N == 0) {
      return status1;
    }
    else if(N >= 1 && N <= 1250) {
      return status2;
    }
    else if(N > 1250 && N <= 2200) {
      return status3;
    }
    else if(N > 2200 && N <= 2900) {
      return status4;
    }
    else if(N > 2900) {
      return status5;
    }
    else {
      return status6;
    }
}
