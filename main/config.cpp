#include "config.h"

// Define the pins for the NeoPixel strips
const int LED_PINS[7] = {2, 3, 4, 5, 6, 7, 8};

// Define the array of Adafruit_NeoPixel objects
Adafruit_NeoPixel strips[7] = {
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[0], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[1], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[2], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[3], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[4], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[5], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[6], NEO_GRB + NEO_KHZ800)
};

// Define the function to turn off all lights
void turnOffAllLights() {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < LED_COUNT; j++) {
      strips[i].setPixelColor(j, strips[i].Color(0, 0, 0));
    }
    strips[i].show();
  }
}

