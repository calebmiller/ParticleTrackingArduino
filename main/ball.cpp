#include "ball.h"
#include <Arduino.h>  // Required for Arduino functions
#include <Adafruit_NeoPixel.h>

void runBall(LEDSystem* ledControl) {
	int startx=random(20,80);
	int starty=random(20,80);
	int startz=random(20,80);

	coordinate start = {startx,starty,startz};
  int SIZE=30; //pass in? determine randomly?
  int radius=0;
  while(radius<SIZE){
    ledControl->setVolume(start, radius);
    ledControl->show();
		delay(TIMESTEP); //TIMESTEP
    radius+=STEPSIZE;
	}

	delay(2000);
  ledControl->clear();
}
