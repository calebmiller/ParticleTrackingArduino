#include "noise.h"
#include <Arduino.h>  // Required for Arduino functions
#include <Adafruit_NeoPixel.h>


void runNoise(LEDSystem ledControl) {

	for(int i=0; i<10; i++){	
		int nLights = random(10,50);
		for(int i=0; i<nLights; i++){
			int pixel = random(0,100);
			int r = random(50,255);
			int g = random(50,255);
			int b = random(50,255);
      ledControl.setPixel(pixel, r,g,b);
		}
	
		ledControl.show();
		delay(200);

		// Turn off all the lights
		ledControl.clear();
	}
}
