// NewPing - Version: Latest 
// Library to get easy ping function on Ultrasonic Sensor
#include <NewPing.h>

// Pin and variable setup
const int motor1;
const int motor2;

const int rightLED = 3;
const int leftLED = 12;

const int trigPin = 9;
const int echoPin =10;

long distance;

const int MAX_DISTANCE = 200;

//The easy ping function mentioned earlier
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);


//Function that makes an LED on the left side of the car turn on
void leftLight() {
    digitalWrite(leftLED, HIGH);
    delay(10);
    digitalWrite(leftLED, LOW);
}

// Function that makes an LED on the right side of the car turn on
void rightLight() {
    digitalWrite(rightLED, HIGH);
    delay(10);
    digitalWrite(rightLED, LOW);
}



//Setting up pinmodes and running Serial.begin()
void setup() {
    pinMode(rightLED, OUTPUT);
    pinMode(leftLED, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
}

void loop() {
    //Usage of the easy function, the .ping_cm gives us the distance in cm
    distance = sonar.ping_cm();
    
    // Print information to the serial monitor so we can see what's happening
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print("cm");
    Serial.println();
    
    //If the distance is less than 15 cm
    if(distance < 15) {

      //Randomly select either 0 or 1
      int randomNumber = random(0,2);

      // If number is 1 aka true
      if(randomNumber) {
        while(distance < 15) {
         leftLight();
         distance = sonar.ping_cm();
        }
      }

      //Otherwise do this (when number is 0)
      else{
        while(distance<15) {
         rightLight();
         distance = sonar.ping_cm();
        }
      }
    }
        
    
}
