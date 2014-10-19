/**
 * NeoPixel Arc Reactor
 *
 * Simulates the Arc Reactor from Iron Man with a NeoPixel Ring. The NeoPixel ring pulses with
 * blue light to look more interesting than a solid blue color.
 *
 * Based on Superhero Power Plant code by Tony Sherwood for Adafruit Industries
 */

#include <Adafruit_NeoPixel.h>

#define PIN 1

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(25, PIN, NEO_GRB + NEO_KHZ800);

int alpha; // Current value of the pixels
int dir = 1; // Direction of the pixels... 1 = getting brighter, 0 = getting dimmer
int flip; // Randomly flip the direction every once in a while
int minAlpha = 25; // Min value of brightness
int maxAlpha = 100; // Max value of brightness
int alphaDelta = 5; // Delta of brightness between times through the loop

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

/**
 * The main program loop
 */
void loop() {
  fadeIn();
  
  // Randomly choose to flicker instead of just pulsing
  int shouldFlicker = random(50);
  if (shouldFlicker == 50) {
    flicker();
  }
  
  fadeOut();
}

/**
 * Fill the dots one after the other with a color
 */
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
  }
}

/**
 * Have the blue fade in from the min value (minAlpha) to the max value (maxAlpha)
 */
void fadeIn() {
  for (uint16_t ii = minAlpha; ii < maxAlpha; ii++) {
    for (uint16_t jj = 0; jj < strip.numPixels(); jj++) {
      strip.setPixelColor(jj, strip.Color(0, 0, ii));
      strip.show();
    }
    
    delay(10);
  }
}

/**
 * Have the blue fade out from the max value (maxAlpha) to the min value (minAlpha)
 */
void fadeOut() {
  for (uint16_t ii = maxAlpha; ii > minAlpha; ii--) {
    for (uint16_t jj = 0; jj < strip.numPixels(); jj++) {
      strip.setPixelColor(jj, strip.Color(0, 0, ii));
      strip.show();
    }
    
    delay(10);
  }
}

/**
 * Flicker the color randomly for a bit
 */
void flicker() {
  for (int ii = 0; ii < 200; ii++) {
    flip = random(32);
    if(flip > 20) {
      dir = 1 - dir;
    }
    // Some example procedures showing how to display to the pixels:
    if (dir == 1) {
      alpha += alphaDelta;
    }
    if (dir == 0) {
      alpha -= alphaDelta;
    }
    if (alpha < minAlpha) {
      alpha = minAlpha;
      dir = 1;
    }
    if (alpha > maxAlpha) {
      alpha = maxAlpha;
      dir = 0;
    }
    // Change the line below to alter the color of the lights
    // The numbers represent the Red, Green, and Blue values
    // of the lights, as a value between 0(off) and 1(max brightness)
    colorWipe(strip.Color(alpha, 0, 0)); // Blue
  }
}
