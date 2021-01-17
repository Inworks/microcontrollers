/******************************************************************************
    ESP32_IFTTT_Timer.ino
    
    Example for sending regularly timed HTTP POST requests to IFTTT with the ESP32.
    In this demo, on regularly timed intervals the ESP32 is triggered to send the current light level to an IFTTT Webhook.
    
    Created 22 September 2018
    By Jenny Filipetti @ CU Denver Inworks
    http://codebase.jennyfilipetti.com/workshops/dsw18-iot.html
    This code is in the public domain.
    
    connectToWifi() method by Alex Wende @ SparkFun Electronics, 7 February 2017
*/
#include <WiFi.h>
#include <HTTPClient.h>

#define TOUCHPIN 4                          // Specifies the ESP32 pin where our sensor (in this case capacitive) is connected. For this demo, should be a TOUCH pin.
#define LDRPIN 36                          // Specifies the ESP32 pin where our sensor (in this case a photoresistor) is connected. For this demo, must be an ADC1 pin.
                                           
const char* ssid = "Inworks-IoT2";                               // Your router's SSID goes here
const char* password = "MakeItMatter";                           // Your wifi password goes here
const String eventName = "YOUR-EVENT-NAME-HERE";                 // Your IFTTT Applet event name goes here
const String serviceKey = "YOUR-SERVICE-KEY-HERE";               // Your IFTTT Maker Webhook service key goes here
                                                                 // To find yours, click "Documentation" at https://ifttt.com/maker_webhooks
long timeOfLastMessage = 0;
const int INTERVAL = 60000;                 // Timer interval (in milliseconds)

void setup() {
  Serial.begin(115200);                     // Begin serial communications; useful for debugging.
  pinMode(TOUCHPIN, INPUT);
  pinMode(LDRPIN, INPUT);
  
  Serial.println("Initializing board...");
  connectToWifi();
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){          // Check wifi connection status
    if (millis() - timeOfLastMessage >= INTERVAL){      // If our time interval has elapsed since we last sent a message...
      postMessage();                                    // Send the HTTP POST request
      timeOfLastMessage = millis();                     // Update our variable tracking the time we last sent a message
    }
  }
  else{                                      // If the wifi connection is not connected, print an error and attempt to reconnect
      Serial.println("Error in WiFi connection");  
      delay(1000); 
      connectToWifi();
  }
  delay(10);                               // Small delay to improve performance
}

void postMessage(){
   Serial.println("Sending POST request...");
  
   HTTPClient http;  
   String destinationURL = "https://maker.ifttt.com/trigger/" + eventName + "/with/key/" + serviceKey;
   String jsonMessage;
   
   jsonMessage = "{" + formatJSONValue(1, analogRead(LDRPIN)) + "}";       // Prepare a properly formatted JSON message with our light level value

   // The following line is an example of how to send two variables, in this case the light level value and the touch pin value (expected to always be 1 for "high/active")
   // jsonMessage = "{" + formatJSONValue(1, analogRead(LDRPIN)) + "," + formatJSONValue(2, digitalRead(TOUCHPIN)) + "}";
   
   // The following line is an example of how to send the IFTTT maximum of three variables, in this case a String message in addition to everything from before  
   // jsonMessage = "{" + formatJSONValue(1, "Hello brave new IoT world!") + "," + formatJSONValue(2, analogRead(LDRPIN)) + formatJSONValue(3, digitalRead(TOUCHPIN)) + "}";

   Serial.println(jsonMessage);
   
   http.begin(destinationURL);                                // Specify destination for HTTP request (URL)
   
   http.addHeader("Host", "maker.ifttt.com");                 // This and the below are optional additions of relevant HTTP Request headers
   http.addHeader("User-Agent", "ESP32_Thing");
   http.addHeader("Content-Type", "application/json"); 

   int httpResponseCode = http.POST(jsonMessage);             //Send the actual POST request
 
   if(httpResponseCode > 0){                                  // If our HTTP request was successful
    String response = http.getString();                       // Get the response to the request
 
    Serial.println(httpResponseCode);                         // Print HTTP response code
    Serial.println(response);                                 // Print HTTP request text response
 
   }
   else{
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
   }
   
   http.end();                                                // Free up resources    
}

/*
 *    Preparly a properly formatted JSON key/value pair for a String variable.
 *    Note: this method is written specifically for integration with the IFTTT Webhooks which expects the keys "value1", "value2", and "value3"
 */
String formatJSONValue(int numVariable, String value){
  String jsonMessage = "\"value";
  jsonMessage += numVariable;
  jsonMessage += "\":\"";
  jsonMessage += value;
  jsonMessage += "\"";
  return jsonMessage;
}

/*
 *    Prepare a properly formatted JSON key/value pair for an integer variable.
 *    The only difference from the above method is the absence of quotation marks around the object value.
 *    Note: this method is written specifically for integration with the IFTTT Webhooks which expect the keys "value1", "value2", and "value3"
 */
String formatJSONValue(int numVariable, int value){
  String jsonMessage = "\"value";
  jsonMessage += numVariable;
  jsonMessage += "\":";
  jsonMessage += value;
  jsonMessage += "";
  return jsonMessage;
}

void connectToWifi(){
  bool timeOut = 0; // Change to 1 if connection times out
  byte count = 0;   // Counter for the number of attempts to connect to wireless AP
  WiFi.begin(ssid, password); 

  Serial.println("Connecting to wifi...");
  while (WiFi.status() != WL_CONNECTED && (timeOut == 0)) // Test to see if we're connected
  {
    Serial.print('.');
    count++;
    if(count > 60) break; // Give up after ~30 seconds
    else delay(500);      // Check again after 500ms
  }
  
  if (WiFi.status() == WL_CONNECTED)        // We're connected
  {
    Serial.println("\r\nWiFi connected");
  }
  else                                      // Unable to connect
  {
    WiFi.disconnect();
    Serial.println("\r\nConnection Timed Out!\r\n");
  }
}
 


