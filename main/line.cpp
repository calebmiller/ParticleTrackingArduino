#include "line.h"
#include <Arduino.h>  // Required for Arduino functions
#include <Adafruit_NeoPixel.h>

void runLine(Adafruit_NeoPixel &strip) {

	int startPixel = random(5, 16);
    int direction = random(0, 2) == 0 ? -1 : 1; // Randomly choose direction: -1 (negative) or 1 (positive)
    int numPixels = random(5, 11); // Random number of pixels between 5 and 10

    for (int i = 0; i < numPixels; i++) {
        int pixel = startPixel + i * direction;
        if (pixel >= 0 && pixel < strip.numPixels()) {
            strip.setPixelColor(pixel, strip.Color(255, 255, 255));
            strip.show();
            delay(200);
        }
    }

    delay(1000);
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();

}
