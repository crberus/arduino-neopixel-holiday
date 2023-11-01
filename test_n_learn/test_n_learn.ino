#include <FastLED.h>

#define LED_PIN     6  // Define the digital pin for the LED data
#define NUM_LEDS    300 // Define the number of LEDs in your strip
#define BRIGHTNESS  40 // Set the initial brightness (0-255)
#define DELAY_MS    15 // Delay between LED tests in milliseconds

//CRGB leds[NUM_LEDS];  // Basic; not using due to switch to defined arrays
CRGBArray<NUM_LEDS> leds; // Using CRGBArray for better control
CRGBSet fullSet(leds(0,NUM_LEDS));  // Set array to address entire strip
CRGBSet firstSet(leds(0,20));  // Set array for a region of LEDs
CRGBSet secondSet(leds(100,150)); // Set array for a region of LEDs

int flickloop = 1;  // Initialize for later use in internal flicker loop

void setup() {
  // Setup serial port for monitoring
  Serial.begin(9600); // Open serial port, set data rate to 9600 bps
  Serial.println("Serial initialized");

  // Setup WS2812B LED strip using FastLED
  Serial.println("Initializing LED strip");
  //FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS); // Set up the LED strip on digital pin 6
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  Serial.println("Clearing FastLED configuration");
  FastLED.clear();  // Clear any lingering LED configuration

  Serial.println("Setting initial LED brightness");
  FastLED.setBrightness(BRIGHTNESS); // Set the brightness


  // Glow first LED for about a second to confirm control
  leds[0] = CRGB::Green; // Set color of first LED 
  FastLED.show();
  delay(1000);

  // Set entire strip to initial color state
  fullSet = CRGB::DarkRed; 
  FastLED.show();
  delay(1000);
}

// Flicker entire strip randomly in red
void loop() {
  Serial.println("Begin main loop");

  fullSet = CRGB::DarkRed;  // ambient/base color
  FastLED.setBrightness(BRIGHTNESS); // base/ambient brightness
  //leds[0] = CRGB::DarkSlateBlue;  // bit of visual assistance while developing
  FastLED.show();

  delay(random16(500,3000));  // ambient solid for multiple seconds (randomly selected)

  // Setup nested flicker loop; number of loops (period of time) is set by random function
  int flickloop = random8(3,16);  // set number of loops to perform randomly

  while (flickloop > 0) {
    Serial.println("Starting interior loop");
    Serial.println("Filling fullSet Red");
    //firstSet = CRGB::Red;
    
    fullSet = CRGB::Red;
    //fill_solid( leds, NUM_LEDS, CRGB::Red );
    Serial.println("Adusting brightness");
    FastLED.setBrightness(random8(10,50)); // set random brightness for added effect
    //fadeLightBy(firstSet, firstSet, random8(10,90));
    //fadeLightBy(firstSet, 300, random8(10,90));
    //FastLED.show(random8(10,90));
    FastLED.show();
    delay(random16(10,100));

    Serial.println("Filling fullSset DarkRed");
    //firstSet = CRGB::DarkRed;
    //fill_solid(leds, NUM_LEDS, CRGB::DarkRed);
    fullSet = CRGB::DarkRed;
    FastLED.setBrightness(random8(5,30)); // set random brightness for added effect
    FastLED.show();
    delay(random16(20,100));

    flickloop--;
  }

  Serial.println("End main loop");
}

/* 
void loop() {
  // Outer loop
  for (int i = 0; i < 1; i++) {
    // Fade
    for (int j = 0; j < 1; j++) {
      fadeToBlackBy(leds, 10, 5); // 10 is the amount by which brightness is reduced.
      FastLED.show();
      delay(10);  // Delay to control the speed of the fading effect.
    }
    for (int j = 0; j < 1; j++) {
      fadeLightBy(leds, 10, 5); // 10 is the amount by which brightness is reduced.
      FastLED.show();
      delay(10);  // Delay to control the speed of the fading effect.
    }
  }
  // Code to be executed after the outer loop
}
*/




/* walks a dot down the string, strobing it several times before moving to the next
void loop() {
  for(int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Purple;
    FastLED.show();
    for(int strobecount = 1; strobecount < 5; strobecount++) {
      leds[dot] = CRGB::Black; FastLED.show(); delay(30);
      leds[dot] = CRGB::Purple; FastLED.show(); delay(10);
    }
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    //delay(1);
  }
}
*/

/* Very basic - turn LEDs on and then off
void loop() {
  leds[0] = CRGB::Purple;
  leds[1] = CRGB::Purple;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  FastLED.show();
  delay(300);
} */
