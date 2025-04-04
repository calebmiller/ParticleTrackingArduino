#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

#include "line.h"
#include "ball.h"
#include "noise.h"

// Setup for the clock
Adafruit_7segment matrix = Adafruit_7segment();
int clock_time=0;

// LED string pin
#define LED_PIN    2

// Pixels per string
#define LED_COUNT 100

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// Button Pins
const int BLUE_BUTTON_PIN 5
int blue_state=0;

// setup() function -- runs once at startup --------------------------------

void setup() {
//LED SETUP
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  //strip.setPixelColor(10, strip.Color(255,255,255));
  //strip.show();

//CLOCK SETUP
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);

//BUTTON SETUP
  pinMode(BLUE_BUTTON_PIN, INPUT)
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  //Update clock:
  clock_time+=1;
  matrix.println(clock_time);
  matrix.writeDisplay();

  //CHECK BUTTON PUSH
  blue_state=digitalRead(BLUE_BUTTON_PIN)
  if(blue_state == HIGH){
    //run blue program
    delay(10000) //subroutine should return after animation finishes
  }

  //runBall(strip);
  runNoise(strip);
  //runLine(strip);
  //delay(1000);


}
