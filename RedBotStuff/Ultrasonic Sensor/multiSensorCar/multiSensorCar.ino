/*
by Jonathan Macias
*/

//Pin Set Up
const int trigPinFront = 8;
const int echoPinFront = 9;

const int trigPinRight = 2;
const int echoPinRight = 3;

const int trigPinLeft = 10;
const int echoPinLeft = 11;

const int motor1 = 4;
const int motor2 = 5;

const int leftSignal = 6;
const int rightSignal = 7;
const int midSignal = 12;

// Variable Set Up
long distanceF, distanceL, distanceR;
  

//Function to turn the car right, no delay put in
void turnRight() {
  digitalWrite(motor2, LOW);
  digitalWrite(motor1, HIGH);
}

//Function to turn the car left, no delay put in 
void turnLeft() {
  digitalWrite(motor2,HIGH);
  digitalWrite(motor1,LOW);
}

// Function to set the car to drive straight
void goStraight() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
}

//Function to stop motors
void stop() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
}

// Returns distance in front of a sensor
long pingDistance(trigPin, echoPin) {
    //Sends out sound waves to measure duration it takes to come back
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Calculating the distance of whatever may be in front of the sensor based on how long it takes to receive the sound back
    long duration = pulseIn(echoPin, HIGH);
    long distance = duration * 0.034/2;
    Serial.print("Front Distance: ");
    Serial.print(distance);
    Serial.println();
    return distance;
}

//While this may look intimidating at first glance, all that's really happening is it's taking the distance values we give it and deciding where an obstacle is
// and deciding which direction the car should drive in (using the functions made earlier) based off of that
void decisionTime(distF,distL,distR) {
  if(distanceF >35) {
      digitalWrite(midSignal, HIGH);
      digitalWrite(leftSignal,LOW);
      digitalWrite(rightSignal, LOW);
      goStraight();
    }
    if(distanceF< 35 && distanceL>35 && distanceR>35) {
      if(distanceL>distanceR) {
        digitalWrite(leftSignal,HIGH);
        digitalWrite(midSignal, LOW);
        digitalWrite(rightSignal, LOW);
        turnLeft();
      }
      else {
        digitalWrite(rightSignal, HIGH);
        digitalWrite(midSignal, LOW);
        digitalWrite(leftSignal, LOW);
        turnRight();
      }
    }
    if(distanceL<35) {
      if(distanceL<35 && distanceR <35 && distanceF > 35) {
        digitalWrite(midSignal, HIGH);
        digitalWrite(leftSignal,LOW);
        digitalWrite(rightSignal, LOW);
        goStraight();
      }
      else {
      digitalWrite(leftSignal,HIGH);
      digitalWrite(midSignal,LOW);
      digitalWrite(rightSignal, LOW);
      turnRight();
      }
    }
    if(distanceR<35) {
      if(distanceL<35 && distanceR <35 && distanceF > 35) {
        digitalWrite(midSignal, HIGH);
        digitalWrite(leftSignal,LOW);
        digitalWrite(rightSignal, LOW);
        goStraight();
      }
      else {
      digitalWrite(rightSignal,HIGH);
        digitalWrite(leftSignal, LOW);
        digitalWrite(midSignal, LOW);
        turnLeft();
      }
    }
    if(distanceL<35 && distanceF<35 && distanceR<35) {
      digitalWrite(leftSignal, HIGH);
      digitalWrite(midSignal,HIGH);
      digitalWrite(rightSignal,HIGH);
      stop();
    }
}

//Setup pins and run Serial.begin()
void setup() {
    pinMode(trigPinFront, OUTPUT);
    pinMode(trigPinRight, OUTPUT);
    pinMode(trigPinLeft, OUTPUT);
    pinMode(echoPinFront, INPUT);
    pinMode(echoPinLeft,INPUT);
    pinMode(echoPinRight, INPUT);
    pinMode(leftSignal, OUTPUT);
    pinMode(rightSignal, OUTPUT);
    pinMode(midSignal, OUTPUT);
    Serial.begin(9600);
}

//Our loop just consists of pinging distances with the ultrasonic sensors and driving the car to avoid obstacles based on the distances obtaine
void loop() {

  //Each of the following variables use the pingDistance function made above to find out the distance of whatever object may be in front of the sensor   
    distanceF = pingDistance(trigPinFront, echoPinFront);

    distanceR = pingDistance(trigPinRight,echoPinRight);
    
    distanceL = pingDistance(trigPinLeft, echoPinLeft);

    //This uses the function from earlier with our values put in to select which direction the car should drive in.
    decisionTime(distanceF, distanceL, distanceR);
    
    
}
