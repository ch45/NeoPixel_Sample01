// sample01_ino.ino
// Sketch uses 5682 bytes (19%) of program storage space. Maximum is 28672 bytes.
// Global variables use 182 bytes (7%) of dynamic memory, leaving 2378 bytes for local variables. Maximum is 2560 bytes.


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define BAUD      57600
#define FPS         120
#define LED_COUNT     8
#define LED_PIN       7 // 7 Chaz, 6 Ed

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
char val; // Data received from the serial port

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(51);  // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.begin(BAUD);      // Start serial communication
}

void loop() {
  // strip.clear();
  while (Serial.available()) {
    val = Serial.read();
    int i = 0;
    for ( ; i < LED_COUNT && i <= val; i++) {
      strip.setPixelColor(i, 100, 100, 100);
    }
    for ( ; i < LED_COUNT; i++) {
      strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
    //strip.clear() works here to get teh single LED on
  }
  //set to zzero using val here, seems to work
  //LED_COUNT is more stable but doesnt turn them
  //off when scrolling left
  //strip.setPixelColor(val, 0, 0, 0);
  //strip.clear() works here
  //strip.clear();
  //  strip.show();
  delay(1000 / FPS);
}
    //this bit does band's amplitude(10) to leds
    //    for (int i = 0; i < val; i++) {
    //   // for (int i = 0; i < strip.numPixels(); i++) {
    //      strip.setPixelColor(i, 255, 0, 0);
    //          strip.show();
    //               strip.setPixelColor(i, 0, 0, 0);
    //          strip.show();
    //    delay(1);
    //    }
//void voicePong() {
//}
//
//void redBlue() {
//  //get the strobe left to right red / blue
//  for (int i = 0; i < strip.numPixels(); i++) {
//    strip.setPixelColor(i, 255, 0, 0);
//    strip.show();
//    strip.setPixelColor(i, 0, 0, 0);
//    strip.show();
//    delay(0);
//
//    if (i == 0) {
//      for (int i = strip.numPixels(); i > 0; i--) {
//        strip.setPixelColor(i, 0, 0, 255);
//        strip.show();
//        //        strip.setPixelColor(i, 0, 0, 0);
//        //        strip.show();
//        delay(0);
//      }
//    }
//  }
//}
