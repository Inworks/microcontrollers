/*
 * Demoes the use of sigma delta modulation in place of analogWrite to control an RGB LED on the ESP32.
 * 
 * Note: this is the more general mode of PWM, useful for motors and other outputs. 
 * Although here we're demoing with an RGB LED for ease of testing, 
 * see the ledc demo code for a better way to control LEDs in particular.
 * 
 * by Jenny Filipetti, CU Denver Inworks (2018)
 * Based on the espressif SigmaDelta example at: 
 * https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/AnalogOut/SigmaDelta/SigmaDelta.ino
 * 
 * Additional examples available at: https://github.com/espressif/arduino-esp32/tree/master/libraries/ESP32/examples/AnalogOut
 * 
 * This code is in the public domain.
 */
#define ledPinR 33      // Enter the RGB red pin here
#define ledPinG 32      // Enter the RGB green pin here
#define ledPinB 39      // Enter the RGB blue pin here

// The following define the channels we will use to actually control our pins.
// Channels can be numbered between 0 and 8.
#define ledR 0          
#define ledG 1
#define ledB 2
#define freq 12000

void setup()
{
    
    sigmaDeltaSetup(ledR, freq);           //setup red channel for LED
    sigmaDeltaAttachPin(ledPinR, ledR);    //attach the correct pin for LED red channel
    sigmaDeltaSetup(ledG, freq);           //setup red channel for LED
    sigmaDeltaAttachPin(ledPinG, ledG);    //attach the correct pin for LED green channel
    sigmaDeltaSetup(ledB, freq);           //setup red channel for LED
    sigmaDeltaAttachPin(ledPinB, ledB);    //attach the correct pin for LED blue channel    

    turnLEDOff();
    
    sigmaDeltaWrite(ledG, 200);
    sigmaDeltaWrite(ledB, 212);

    delay(1000);
    sigmaDeltaWrite(ledR, 100);
    sigmaDeltaWrite(ledG, 80);
    sigmaDeltaWrite(ledB, 0);
    delay(1000);
    
    turnLEDOff();
}

void loop(){
}

void turnLEDOff(){
  sigmaDeltaWrite(ledR, 0);
  sigmaDeltaWrite(ledG, 0);
  sigmaDeltaWrite(ledB, 0);
}

