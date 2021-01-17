/******************************************************************************
    ESP32_GettingStarted.ino

    Example for uploading code to the ESP32. Demoes the use of Serial communication and digitalWrite.

    This code is in the public domain.
*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Initializing board...");
  
  pinMode(5, OUTPUT);    // Specify that this pin is connected to an output device (as opposed to an input device like a sensor)
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(5, HIGH);      // Set pin 5 to high (turns the built-in LED on)
  delay(100);                 // Wait 100 milliseconds
  digitalWrite(5, LOW);       // Set pin 5 to low (turns the built-in LED off)
  delay(1000);                // Wait 1 second (1000 milliseconds)
}
