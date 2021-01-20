#include <WiFi.h>

const char* ssid = "Inworks-IoT2";
const char* password = "MakeItMatter";

void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("\nConnected to the WiFi network");
 
}
 
void loop() {
 
}
