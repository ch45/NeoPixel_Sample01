// sample01_ino.ino

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LOOP_FUNCTION render_comet_tail // render_bar render_dot

#define BAUD      57600
#define FPS         120
#define LED_COUNT     8
#define LED_PIN       7 // 7 Chaz, 6 Ed

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800); // NEO_RGB Chaz, NEO_GRB Ed

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(51);  // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.begin(BAUD);      // Start serial communication
}

void loop() {
  LOOP_FUNCTION();
}

#if LOOP_FUNCTION == render_bar
void render_bar() {
  while (Serial.available()) {
    char val = Serial.read();
    int i = 0;
    for ( ; i < LED_COUNT && i < val; i++) {
      strip.setPixelColor(i, 100, 100, 100);
    }
    for ( ; i < LED_COUNT; i++) {
      strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
  }
  delay(1000 / FPS);
}
#endif

#if LOOP_FUNCTION == render_dot
void render_dot() {
  char val;
  while (Serial.available()) {
    val = Serial.read();
  }
  int i = val;
  strip.clear();
  strip.setPixelColor(i, 100, 100, 100);
  strip.show();
  delay(1000 / FPS);
}
#endif

#if LOOP_FUNCTION == render_comet_tail
static char prevVal;
static bool diff;
void render_comet_tail() {
  while (Serial.available()) {
    char val = Serial.read();
    if (val > prevVal) {
      strip.clear();
      for (int i = prevVal; i < LED_COUNT && i < val; i++) {
        strip.setPixelColor(i, 0, 100, 0);
      }
      diff = true;
    }
    else if (val < prevVal) {
      strip.clear();
      for (int i = min(prevVal, LED_COUNT) - 1; i >= val; i--) {
        strip.setPixelColor(i, 100, 0, 0);
      }
      diff = true;
    }
    else if (diff) {
      int i = val - 1;
      strip.clear();
      if (i >= 0) {
        strip.setPixelColor(i, 100, 100, 100);
      }
      diff = false;
    }
    prevVal = val;
    strip.show();
  }
  delay(1000 / FPS);
}
#endif

