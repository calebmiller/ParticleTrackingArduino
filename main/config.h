// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <Adafruit_NeoPixel.h>

//Button PINs
#define BLUE_BUTTON_PIN 13
#define YELLOW_BUTTON_PIN 12
#define WHITE_BUTTON_PIN 11

// Pixels per string
#define LED_COUNT 100

// LED string pin
extern const int LED_PINS[7];

//Light strips
extern Adafruit_NeoPixel strips[7];

//Animation Properties
#define STEPSIZE 0.1
#define LINERADIUS 15

// Function to turn off all lights
void turnOffAllLights();

#endif

