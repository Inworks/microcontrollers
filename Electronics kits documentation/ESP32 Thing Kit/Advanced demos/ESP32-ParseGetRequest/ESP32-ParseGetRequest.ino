/*
 * This code demos how to parse JSON from an HTTP GET request on the ESP32.
 * 
 * Modified by Jenny Filipetti, CU Denver Inworks from ArduinoJson JSONHttpClient example, to use wifi instead of Ethernet.
 * Original code from arduinojson.org, copyright Benoit Blanchon 2014-2018 (MIT License). 
 */

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

String url = "http://arduinojson.org/example.json";
const char* ssid     = "YOUR-WIFI-NETWORK-HERE";
const char* password = "YOUR-WIFI-PASSWORD-HERE";

// Use http://arduinojson.org/assistant to supply the following buffer size values. This will also provide sample parsing code.
const size_t bufferSize = JSON_ARRAY_SIZE(350) + JSON_OBJECT_SIZE(1) + 4*JSON_OBJECT_SIZE(2) + 282*JSON_OBJECT_SIZE(3) + 283*JSON_OBJECT_SIZE(4) + 282*JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(9) + JSON_OBJECT_SIZE(18) + 98010;
DynamicJsonBuffer jsonBuffer(bufferSize);

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing...");

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    makeHTTPRequest();
}

void loop() {
}

void makeHTTPRequest(){
  HTTPClient http;

  Serial.print("[HTTP] Making GET request...");
  http.begin(url);
  
  // start connection and send HTTP header
  int httpCode = http.GET();
  if(httpCode > 0) {
    Serial.print("Status code: "); 
    Serial.println(httpCode);

    if(httpCode == HTTP_CODE_OK) {
        String resp = http.getString();
        Serial.println(resp);

        const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
        DynamicJsonBuffer jsonBuffer(capacity);
        JsonObject& root = jsonBuffer.parseObject(resp);          // Parse string result into JSON object
        if (!root.success()) {                                    // Check whether this was successful
          Serial.println("Failed to parse JSON object");
          return;
        }

        char* sensorType = root["sensor"];
        long timeValue;
        float dataValues[] = new float[sizeof(root["data"])];   // Dynamically create array that matches size of returned values

        float longitudeVal = root["data"][0];
        float latitudeVal = root["data"][1];

        Serial.print("Sensor type: ");
        Serial.println(sensorType);
    
        /*
        // Extract and display values
        Serial.print("Sensor type:"); 
        Serial.println(root["sensor"].as<char*>());
        
        Serial.print("Time: "); 
        Serial.println(root["time"].as<char*>());
        
        Serial.print("Longitude: "); 
        Serial.println(root["data"][0].as<char*>());
        
        Serial.print("Latitude: "); 
        Serial.println(root["data"][1].as<char*>());*/
    } 
  }
  else {
    Serial.print("HTTP request failed: ");
    Serial.println(http.errorToString(httpCode).c_str());
  }
  http.end();
}





  











