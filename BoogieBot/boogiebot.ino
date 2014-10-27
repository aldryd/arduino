#include <Adafruit_NeoPixel.h>

#define PIN 1

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
#define NUM_PIXELS 48
#define PIXELS_IN_ROW 24
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

const uint32_t DIM = 15;

const uint32_t BLANK_COLOR = strip.Color(0, 0, 0);
const uint32_t BLUE_COLOR = strip.Color(0, 0, 255 / DIM);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  theaterChase(BLUE_COLOR, 50);
  theaterChase(BLUE_COLOR, 100);
  theaterChase(BLUE_COLOR, 200);
  theaterChase(BLUE_COLOR, 100);
  theaterChase(BLUE_COLOR, 50);

  for (int ii = 0; ii < 5; ii++) {
    rainbow(5);
  }

  rainbowCycle(1);

  delay(1000);

  theaterChaseRainbow(100);

  delay(500);

  clearAll();

  wiggle(BLUE_COLOR, 100);

  for (int ii = 0; ii < 10; ii++) {
    fillLeftToRight(0, BLUE_COLOR, 20);
    fillLeftToRight(1, BLUE_COLOR, 20);
  }
}

void wiggle(uint32_t c, int delayMs) {
  clearAll();
  int count = 0, index = 0;

  while (count < NUM_PIXELS / 2) {
    strip.setPixelColor(index, c);
    strip.show();

    strip.setPixelColor(index, BLANK_COLOR);

    if (count % 2 == 0) {
      index = index + PIXELS_IN_ROW + 1;
    } else {
      index = index - PIXELS_IN_ROW + 1;
    }

    delay(delayMs);

    count++;
  }
}

/**
 * Fill the line of LEDs from left to right with the given color
 */
void fillLeftToRight(int row, uint32_t c, int delayMs) {
  // Calculate the LED to start with based on the row
  int first = (row * PIXELS_IN_ROW);
  int last = (row * PIXELS_IN_ROW) + PIXELS_IN_ROW;

  clearRow(row);

  for (int ii = first; ii < last; ii++) {
    strip.setPixelColor(ii, c);
    strip.show();
    delay(delayMs);
  }
}

void clearRow(int row) {
  // Calculate the LED to start with based on the row
  int first = (row * PIXELS_IN_ROW);
  int last = (row * PIXELS_IN_ROW) + PIXELS_IN_ROW;

  for (int ii = first; ii < last; ii++) {
    strip.setPixelColor(ii, BLANK_COLOR);
    strip.show();
  }
}

/**
 * Turn all the LEDs off
 */
void clearAll() {
  for (int ii = 0; ii < NUM_PIXELS; ii++) {
    strip.setPixelColor(ii, BLANK_COLOR);
    strip.show();
  }
}

void fadeIn(uint32_t c, int minAlpha, int maxAlpha) {
  for (uint16_t ii = minAlpha; ii < maxAlpha; ii++) {
    for (uint16_t jj = 0; jj < NUM_PIXELS; jj++) {
      strip.setPixelColor(jj, c / ii);
      strip.show();
    }
    
    delay(10);
  }
}

void fadeOut(uint32_t c, int minAlpha, int maxAlpha) {
  for (uint16_t ii = maxAlpha; ii > minAlpha; ii--) {
    for (uint16_t jj = 0; jj < NUM_PIXELS; jj++) {
      strip.setPixelColor(jj, strip.Color(0, 0, ii));
      strip.show();
    }
    
    delay(10);
  }
  
  clearAll();
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j = 0; j < 256; j++) {
    for(i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color((255 - WheelPos * 3) / DIM, 0, (WheelPos * 3) / DIM);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, (WheelPos * 3) / DIM, (255 - WheelPos * 3) / DIM);
  } else {
   WheelPos -= 170;
   return strip.Color((WheelPos * 3) / DIM, (255 - WheelPos * 3) / DIM, 0);
  }
}





