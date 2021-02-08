// This is a short intro to programming an LED light strip with the FastLED library
/*
NOTE: Before our void setup() section, we are going to need to do a few things
to make our code scalable to most strip types, strip lengths,
and generally make our code easier to work with
*/
// Libraries
#include <FastLED.h>
/*
The above line tells Arduino we are using the FastLED library,
NOTE: This will only work if you have it downloaded
(tools > manage libraries > search for and install FastLED)
*/
// Variables
#define NUM_LEDS 30  // sets the number of LEDs in LED light strip
#define DATA_PIN 6  // sets the digital pin on the Arduino that sends data to LED strip
#define BRIGHTNESS 64  // this determines how much current is sent to the LEDs
/*
NOTE: Do not set brightness to the max of 255 unless you know what you're doing with the
electrical side of things and have applied Ohm's Law to your circuit.
The way I've come to understand it, once you get over 400mA
(6 RGB LEDs at full white brightness) the board struggles to keep up.
Depending on your board this could result in some smoke, unless you boost
the powersupply - see the youtube link on the bottom for more info
*/
#define LED_TYPE WS2811  // WS2811 is a specialized integrated circuit (IC)...
//.. and not all LED strips use this particular type of IC. Check before use.
#define COLOR_ORDER GRB  // This is the sequence of how the RBG LEDs are setup...
//.. within each of the lights on the strip
#define UPDATES_PER_SECOND 100 // Speed that the LEDs will refresh
/*
Next, we need to create an array of LEDs. This allows us to manipulate, set
and clear led data that we will be using in our program.
*/

int count = 15;


CRGB leds[NUM_LEDS];
void setup() {
  delay( 3000 );  // power-up safety delay
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  /*
  The above line intakes the information we defined pre-setup into our code
  and then creates an instance of FastLED that we can manipulate as an object.
  !!! This line is the only truely necessary one in the setup. It utilizes a
  class from the FastLED library to allow you to use YOUR light strip.
  */
  FastLED.setBrightness( BRIGHTNESS ); // calling down the brightness from above so we dont break our board
}
void loop() {
  /*
  Below are some examples of how to use the FastLED library's most basic functions
  You can add some /*'s around the blocks of code to turn them off if they get distracting
  and you would like to isolate one section
  */
  // DEMO 1 - TURN SELECT LEDS TO SOLID COLOR
  // This demo selects a single or range of LEDs and then sets them to a solid color.
  leds[0] = CRGB::Red;
  /*
  In the above line leds[] selects the index (from 0 to NUM_LEDS) and once we
  do that we can set it equal to a certain color using "= CRGB::"
  NOTE: CRGB is a class in the FastLED library and it is composed of color variables
  (i.e. capitalization and the colons matter). Try inserting a different primary color!
  */
  FastLED.show();  // This line tells the arduino to actually show the color on led[]
  delay(1500); // Break for next demo
  // DEMO 2 - TURN ALL LEDS TO SOLID COLOR
  // This demo selects all LEDs and then sets them to a solid color.
  // NOTE: the same syntax applies to using the CRGB class above.
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(1500);
  // DEMO 3 - RAINBOW EFFECT
  // This demo turns all LEDs into a rainbow
  fill_rainbow(leds, NUM_LEDS, CRGB(224, 187, 255));
  FastLED.show();
  delay(1500);
  // DEMO 4 - MOVING LED
  // This demo uses a for loop to simulate an LED moving.
  // We use a counter and a while loop so the for loop doesn't run forever.
  int counter = 5;
  // We are running the loop 5 times.
  while (counter > 0) {
    // The for loop adds 1 to the LED index until it reaches NUM_LEDS, and
    // then turns that LED a designated color.
    for (int dot = 0; dot <= NUM_LEDS; dot++) {
      leds[dot] = CRGB::Blue;
      FastLED.show();
      leds[dot] = CRGB::Black;  // Clear this led for the next time around the loop
      delay(100);
    }
   counter = counter -1; // Decrease counter by one,  
    // when counter = zero, the loop will not run again until it is 
    // reset by running the whole void loop over again
  }
  delay(1500);
  // DEMO 5 - BACKWARDS MOVING LED
  // This demo uses a for loop to simulate an LED moving.
  // We use a counter and a while loop so the for loop doesn't run forever.
  int counter2 = 5;
  // We are running the loop 5 times.
  while (counter2 > 0) {
    // The for loop SUBTRACTS 1 from the LED index until it reaches NUM_LEDS, and
    // then turns that LED a designated color-- it runs backwards from the other demo.
    for (int dot = NUM_LEDS; dot >= 0; dot--) {
      leds[dot] = CRGB::Green;
      FastLED.show();
      leds[dot] = CRGB::Black;  // Clear this led for the next time around the loop
      delay(100);      
     }
   counter2 = counter2 -1; // Decrease counter2 by one
  }
  delay(1500);
  // DEMO 6 - FIND THE ODD NUMBERS
  // This demo uses a for loop to simulate an LED moving and highlights the odd numbers.
  // We use a counter and a while loop so the for loop doesn't run forever.
  int counter3 = 5;
  // We are running the loop 5 times.
  while (counter3 > 0) {
    // The for loop adds 1 to the LED index until it reaches NUM_LEDS, and
    // then turns that LED a designated color.
    for (int dot = 0; dot <= NUM_LEDS; dot++) {
      // This section checks whether the LED is an even number or odd.
      // If the led is even it will be blue, and if it is odd it will be red.
      if (dot % 2 == 0) {
        leds[dot] = CRGB::Blue;
        FastLED.show();
      }
      else {
        leds[dot] = CRGB::Red;
        FastLED.show();
      }
      leds[dot] = CRGB::Black;  // Clear this led for the next time around the loop
      delay(100);
    }
   counter3 = counter3 -1;
  }
  delay(1500);
// Clears all LEDs before demos start again
fill_solid(leds, NUM_LEDS, CRGB::Black);
FastLED.show();
delay(1000 / UPDATES_PER_SECOND);
}
/*
Sources:
https://github.com/FastLED/FastLED/wiki/Basic-usage  - Thanks Dan
https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/ - cool example code here
https://youtu.be/aub9PecrbuM - really smart guy who explains the electrical side of things and some code
*/
