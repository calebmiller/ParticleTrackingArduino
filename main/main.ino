#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include "config.h"

#include "3Dline.h"
#include "ball.h"
#include "noise.h"
#include "led.h"


int LED_PINS[NUM_STRIPS] = {2, 3, 4, 5, 6, 7, 8};

Adafruit_NeoPixel strips[NUM_STRIPS] = {
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[0], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[1], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[2], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[3], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[4], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[5], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[6], NEO_GRB + NEO_KHZ800)
  };


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

  ledControl.initLEDs(strips,NUM_STRIPS);
  //ledControl.clear();
  //ledControl.printMap(); //Takes a long time

 
}



// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  //read buttons
  blue_state=digitalRead(BLUE_BUTTON_PIN);
  yellow_state=digitalRead(YELLOW_BUTTON_PIN);
  white_state=digitalRead(WHITE_BUTTON_PIN);
  if(blue_state == LOW){
    Serial.println("blue button");
    //run blue program
    //subroutine should return after animation finishes
    //runBall(&ledControl);
    ledControl.redFlash();
  }
  else if(yellow_state == LOW){
    runTrack(&ledControl);
  }
  else if(white_state == LOW){
    delay(30);
  }
  else{
    if(millis()%5000==0) runNoise(&ledControl);
    delay(10);
  }
}
