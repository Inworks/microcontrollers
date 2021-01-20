/*
  Code that works on Sparkfun Redbot, has turning and reverse functions.
  There is a drive function that has loops to make the car drive forward
  and make turns, you can customize this so that the car drives as you want it to.
*/

// SparkFun RedBot Library - Version: Latest 
// Libraries necessary to run program on Sparkfun Redbot board
#include <RedBot.h>
#include <RedBotSoftwareSerial.h>

RedBotMotors motors;

// Turns left by making the right motor go forward and left motor go backward
// more like a pivot but I put turn for simplicity
void turnLeft() {
  motors.leftMotor(100);
  motors.rightMotor(100);
  delay(500);
  motors.stop();
}

// Turns right just like the turn left function
void turnRight() {
  motors.leftMotor(-100);
  motors.rightMotor(-100);
  delay(500);
  motors.stop();
}

// Reverses the car
void reverse() {
  motors.rightMotor(-150);
  motors.leftMotor(150);
  delay(500);
  motors.stop();
}

// Drive function, there are for loops that make the car actually drive forward
// and there are turn functions tossed in there for a little pazazz
void drive() {
  for(int i=0;i<4; i++) {
    motors.drive(50);
    delay(250);
  }
  turnLeft();
  for(int i=0; i<4;i++) {
    motors.drive(50);
    delay(250);
  }
  turnRight();
}

// Setup function, Serial used during testing but doesn't print anything now
void setup() {
    Serial.begin(9600);
}

//Drive function loops forever
void loop() {
  drive();
}
