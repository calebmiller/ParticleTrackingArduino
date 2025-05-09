#include "tau.h"
#include <Arduino.h>  // Required for Arduino functions
#include <Adafruit_NeoPixel.h>

void runTau(LEDSystem* ledControl) {
	int startx=random(30,70);
	int starty=random(30,70);
	int startz=random(30,70);

	int offx=random(-30,30);
	int offy=random(-30,30);
	int offz=random(-30,30);
   

	coordinate start = {startx,starty,startz};
	coordinate tau = {startx+offx,starty+offy,startz+offz};
    int ball1=random(15,20); //pass in? determine randomly?
    int ball2=random(15,30); //pass in? determine randomly?
    
    int radius1=0;
    int radius2=0;
  
  ledControl->resetClock();
  int time=0;
  while(radius1<ball1 || radius2<ball2){
    ledControl->setVolume(start, radius1);
    if(time>100) ledControl->setVolume(tau, radius2);
    ledControl->show();
    ledControl->updateClock(TIMESTEP);
	  delay(TIMESTEP); //TIMESTEP
    time+=TIMESTEP;
    radius1 = (radius1 <ball1 ) ? radius1 + STEPSIZE : radius1;
    radius2 = (radius2 <ball2 ) ? radius2 + STEPSIZE : radius2;
	}

	delay(2000);
  ledControl->clear();
}
