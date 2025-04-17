#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "config.h"


class LEDSystem {
  public:
    void initLEDs(Adafruit_NeoPixel* strips, int numStrips);
    void clear();
    void show();
    void printMap();
    void setPixel(int strip, int pixel, int r, int g, int b);
    void setVolume(coordinate coor, float radius);
    void redFlash();
    void assembly(int strip, int step);

  private:
    Adafruit_NeoPixel* strips;
    int numStrips;
    coordinate points[460];
    pixel_ID pins[460];

    void generate_grid(int rows, float distance);
    int get_pin_id(int yval);
        
};

#endif // LED_H
