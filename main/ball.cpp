#include "ball.h"
#include <Arduino.h>  // Required for Arduino functions
#include <Adafruit_NeoPixel.h>

void runBall(Adafruit_NeoPixel &strip) {
	int startPixel = random(0, strip.numPixels());
    int steps = random(1, 5); // Random number of steps between 1 and 5

    for (int step = 0; step <= steps; step++) {
        for (int offset = -step; offset <= step; offset++) {
            int pixel = startPixel + offset;
            if (pixel >= 0 && pixel < strip.numPixels()) {
                strip.setPixelColor(pixel, strip.Color(255, 255, 255));
            }
        }
        strip.show();
        delay(200);
    }

	delay(1000);
    // Turn off all the lights after the wave
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
}
