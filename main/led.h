#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include "config.h"


class LEDSystem {
  public:
    void initLEDs(Adafruit_NeoPixel* strs, int nStr, Adafruit_7segment* clk);
    void clear();
    void show();
    void printMap();
    void setPixel(int strip, int pixel, int r, int g, int b);
    void setVolume(coordinate coor, float radius);
    void redFlash();
    void assembly(int strip, int step);
    void lightAll();

  private:
    Adafruit_NeoPixel* strips;
    Adafruit_7segment* clock;
    int currentTime;
    int numStrips;
    coordinate points[460];
    pixel_ID pins[460];

    void generate_grid(int rows, float distance);
    int get_pin_id(int yval);
        
};

#endif // LED_H
