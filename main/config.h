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
#define NUM_STRIPS 7

//Animation Properties
#define STEPSIZE 1
#define LINERADIUS 15
#define TIMESTEP 50 //should scale with STEPSIZE

//Predefined colors 
// g<<16 | b<<8 | r
#define PINK 4142335 
#define CYAN 3470591

struct colour{
	int r;
	int g;
	int b;
};


struct coordinate{
  int x;
  int y;
  int z;
  
  bool operator<(const coordinate& other) const {
    if (x != other.x) return x < other.x;
    if (y != other.y) return y < other.y;
    return z < other.z;
  }
};

struct pixel_ID
{
  int strip;
  int pixel;
};

#endif

