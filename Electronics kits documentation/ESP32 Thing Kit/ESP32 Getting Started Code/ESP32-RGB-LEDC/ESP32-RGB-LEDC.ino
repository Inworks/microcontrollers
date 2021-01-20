/*
 * Demoes the use of ledc in place of analogWrite to control an RGB LED on the ESP32.
 * https://github.com/espressif/arduino-esp32/tree/master/libraries/ESP32/examples/AnalogOut/ledcWrite_RGB
 * 
 * This code is in the public domain. Modified by Jenny Filipetti, CU Denver Inworks (2018).
 * Note: this code is used for LED control specifically. For the general PWM case, see the SigmaDelta demo code.
 */
 
#define ledPinR 33      // Enter the RGB red pin here
#define ledPinG 32      // Enter the RGB green pin here
#define ledPinB 39      // Enter the RGB blue pin here

// The following define the channels we will use to actually control our pins.
// Channels can be numbered between 0 and 15.
#define ledR 0          
#define ledG 1
#define ledB 2

#define freq 12000      // In Hz; depends on resolution
#define resolution 8    // 1 - 16 bits

// The following variables are used in the hueToRGB() function:
const boolean invert = true;  // set true if common anode, false if common cathode
uint8_t color = 0;            // a value from 0 to 255 representing the hue
uint32_t R, G, B;             // Will be used to control the colour 
uint8_t brightness = 255;    // Brightness from 0 (off) to 255 (maximum)

void setup(){            
  Serial.begin(115200);
  delay(10); 

  // assign RGB led pins to channels
  ledcAttachPin(ledPinR, ledR); 
  ledcAttachPin(ledPinG, ledG);
  ledcAttachPin(ledPinB, ledB);
  
  // Initialize channels 
  ledcSetup(ledR, freq, resolution);
  ledcSetup(ledG, freq, resolution);
  ledcSetup(ledB, freq, resolution);
}

void loop() {
  
  ledcWrite(ledR, 255);
  ledcWrite(ledG, 255);
  ledcWrite(ledB, 255);
  delay(5000);
  
  for (color = 0; color < 255; color++) { // Slew through the color spectrum
    hueToRGB(color, brightness);  // call function to convert hue to RGB
    
    // write the RGB values to the pins
    ledcWrite(ledR, R);
    ledcWrite(ledG, G);   
    ledcWrite(ledB, B); 
    delay(50);
 }
 
}


void turnLEDOff(){
  ledcWrite(ledR, 0);
  ledcWrite(ledG, 0);
  ledcWrite(ledB, 0);
}

// Courtesy http://www.instructables.com/id/How-to-Use-an-RGB-LED/?ALLSTEPS
// function to convert a color to its Red, Green, and Blue components.
void hueToRGB(uint8_t hue, uint8_t brightness)
{
    uint16_t scaledHue = (hue * 6);
    uint8_t segment = scaledHue / 256;                       // segment 0 to 5 around the color wheel
    uint16_t segmentOffset = scaledHue - (segment * 256);   // position within the segment

    uint8_t complement = 0;
    uint16_t prev = (brightness * ( 255 -  segmentOffset)) / 256;
    uint16_t next = (brightness *  segmentOffset) / 256;

    if(invert)
    {
      brightness = 255 - brightness;
      complement = 255;
      prev = 255 - prev;
      next = 255 - next;
    }

    switch(segment ) {
    case 0:      // red
        R = brightness;
        G = next;
        B = complement;
    break;
    case 1:     // yellow
        R = prev;
        G = brightness;
        B = complement;
    break;
    case 2:     // green
        R = complement;
        G = brightness;
        B = next;
    break;
    case 3:    // cyan
        R = complement;
        G = prev;
        B = brightness;
    break;
    case 4:    // blue
        R = next;
        G = complement;
        B = brightness;
    break;
   case 5:      // magenta
    default:
        R = brightness;
        G = complement;
        B = prev;
    break;
    }
}
