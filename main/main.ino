#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include "config.h"

#include "line.h"
#include "ball.h"
#include "noise.h"

// Setup for the clock
Adafruit_7segment matrix = Adafruit_7segment();
int clock_time=0;

// Button states
int blue_state=0;
int yellow_state=0;
int white_state=0;

// setup() function -- runs once at startup --------------------------------

void setup() {
//LED SETUP
  for (int i = 0; i < 7; i++) {
    strips[i].begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
    strips[i].show();            // Turn OFF all pixels ASAP
    strips[i].setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  }
  turnOffAllLights();
  //strip.setPixelColor(0, strip.Color(0,0,255));
  strips[0].setPixelColor(50, strips[0].Color(200,150, 255)); //GBR

  strips[0].show();

//CLOCK SETUP
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);

//BUTTON SETUP
  pinMode(BLUE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(YELLOW_BUTTON_PIN, INPUT_PULLUP);
  pinMode(WHITE_BUTTON_PIN, INPUT_PULLUP);
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {

  //read buttons
  blue_state=digitalRead(BLUE_BUTTON_PIN);
  yellow_state=digitalRead(YELLOW_BUTTON_PIN);
  white_state=digitalRead(WHITE_BUTTON_PIN);
  if(blue_state == LOW){
    //run blue program
    //subroutine should return after animation finishes
    runNoise(strips[0]);
  }
  else if(yellow_state == LOW){
    delay(30);
  }
  else if(white_state == LOW){
    delay(30);
  }
  else{
    delay(10);
  }
}
