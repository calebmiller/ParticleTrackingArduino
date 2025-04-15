#include "noise.h"
#include <Arduino.h>  // Required for Arduino functions
#include <Adafruit_NeoPixel.h>


void runNoise(LEDSystem* ledControl) {

	for(int i=0; i<3; i++){
    //for(int j=0; j<7; j++){
      int nLights = random(0,5);
		  for(int k=0; k<nLights; k++){
			  int pixel = random(0,100);
			  int r = random(50,255);
			  int g = random(50,255);
			  int b = random(50,255);
        ledControl->setPixel(0,pixel, r,g,b);
        Serial.println("set");
		  }
    //}
		Serial.println("update");
		ledControl->show();
		delay(1000);

    Serial.println("clear");
		// Turn off all the lights
		ledControl->clear();
	}
}
