#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

//String url = "https://www.googleapis.com/books/v1/volumes?q=iot";
//String url = "https://api.nasa.gov/neo/rest/v1/neo/3542519?api_key=DEMO_KEY";
//String url = "https://jsonplaceholder.typicode.com/posts/1";
String url = "http://api.openweathermap.org/data/2.5/weather?lat=45.4472729&lon=9.1779966&APPID=561240f392a001668710169f510c2d3e";

const char* ssid     = "Inworks-IoT2";
const char* password = "MakeItMatter";

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

  int httpCode = http.GET();                         // Start connection and send HTTP header
  
  if(httpCode > 0) {
    Serial.print("Status code: ");                  
    Serial.println(httpCode);                       // Print the status code of our received response

    if (httpCode == HTTP_CODE_OK) {                 // If we got a successful status code back
        String payload = http.getString();          // Print the body of the HTTP response
        Serial.println(payload);
    }
  } 
  else {
    Serial.print("Request failed: ");
    Serial.println(http.errorToString(httpCode).c_str());
  }
  http.end();                                     // Close our HTTP connection. 
                                                  // We can create a new one if we need to send another request.
}
















