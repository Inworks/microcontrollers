/*
 * This code demos how to parse JSON from an HTTP GET request to OpenWeatherMap on the ESP32.
 * 
 * You should first have an API key from OpenWeatherMap. Get one by subscribing to a free or paid tier here: 
 * https://openweathermap.org/price
 * 
 * Created by Jenny Filipetti, CU Denver Inworks (2019).
 * Original ArduinoJson JSONHttpClient example from arduinojson.org, copyright Benoit Blanchon 2014-2018 (MIT License).  
 * Modified to work with OpenWeatherMap API and to use wifi instead of Ethernet.
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid     = "Inworks-IoT2";      // Your wifi network name goes here
const char* password = "MakeItMatter";      // Your wifi password goes here

// Modify this URL for the API call you would like to make. You can use zip code, city name, or GPS coordinates for a specific location.
String baseUrl = "http://api.openweathermap.org/data/2.5/weather?lat=45.4472729&lon=9.1779966";
String key = "YOUR-API-KEY-GOES-HERE";          // Replace with your API key (sent via e-mail when you subscribe to an API)
                                               // Temporarily you can use: b6907d289e10d714a6e88b30761fae22
const size_t bufferSize = 1169;           // Expected memory capacity calculated via http://arduinojson.org/assistant

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

// In this example, we only want to make one HTTP request so loop() is empty
void loop() {
}

void makeHTTPRequest(){
  HTTPClient http;
  String url = baseUrl + "&APPID=" + key;
  
  Serial.print("[HTTP] Making GET request to ");
  Serial.println(url);
  http.begin(url);
  
  // start connection and send HTTP header
  int httpCode = http.GET();

  if(httpCode > 0) {
    Serial.print("Status code: "); 
    Serial.println(httpCode);

    if(httpCode == HTTP_CODE_OK) {
        String resp = http.getString();
        //Serial.println(resp);                 // Uncomment to print the raw text response

        // The next few lines convert our text response into a real JSON object we can parse
        StaticJsonDocument<bufferSize> doc;
        DeserializationError error = deserializeJson(doc, resp);
        if (error){
          Serial.println("Failed to parse JSON object");
          return;
        }

        // The next few lines pick out a specific part of the JSON to display.
        // Review the JSON tutorial and the OpenWeatherMap current weather data API doc to adjust for your data of interest.
        // Overall API doc: https://openweathermap.org/current
        // Weather code values: https://openweathermap.org/weather-conditions
        // More details and examples about ArduinoJSON: https://arduinojson.org/v6/example
        
        JsonObject myWeatherReading = doc["weather"][0];
        String currWeather = myWeatherReading.getMember("main");
        Serial.print("The current weather in Milan is: ");
        Serial.println(currWeather);
    } 
  }
  else {
    Serial.print("HTTP request failed: ");
    Serial.println(http.errorToString(httpCode).c_str());
  }
  
  http.end();       // Close our HTTP request. After we close it, we can begin a new request if we want to make more than one call to the API.
}


