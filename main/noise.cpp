#include "noise.h"
#include <Arduino.h>  // Required for Arduino functions
#include <Adafruit_NeoPixel.h>


void runNoise(Adafruit_NeoPixel &strip) {
	
	int nLights = random(2,10);
	for(int i=0; i<nLights; i++){
		int pixel = random(0,30);
		int r = random(50,255);
		int g = random(50,255);
		int b = random(50,255);
		strip.setPixelColor(pixel, strip.Color(r,g,b));
	}
	
	strip.show();
	delay(200);

	// Turn off all the lights
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }

    strip.show();

}
