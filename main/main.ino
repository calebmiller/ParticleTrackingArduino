#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include "config.h"

#include "line.h"
#include "ball.h"
#include "noise.h"
#include "led.h"

// Setup for the clock
Adafruit_7segment matrix = Adafruit_7segment();
int clock_time=0;

// Button states
int blue_state=0;
int yellow_state=0;
int white_state=0;

//LEDController
LEDSystem ledControl;


// setup() function -- runs once at startup --------------------------------

void setup() {

  Serial.begin(9600);
  Serial.println("startup");
//CLOCK SETUP
//#ifndef __AVR_ATtiny85__
//  
//  Serial.println("7 Segment Backpack Test");
//#endif
//  matrix.begin(0x70);

//BUTTON SETUP
  pinMode(BLUE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(YELLOW_BUTTON_PIN, INPUT_PULLUP);
  pinMode(WHITE_BUTTON_PIN, INPUT_PULLUP);

  ledControl.initLEDs();
  //ledControl.printMap();
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
    runNoise(ledControl);
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
