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
  int distance = int(sqrt(pow(offx,2)+pow(offy,2)+pow(offz,2))); 

  int ball1=random(15,20); 
  int ball2=random(15,30); 
    
  int radius1=0;
  int radius2=0;
 
  colour c1={255,63,52};
  colour c2={52,244,255};

 
  ledControl->resetClock();
  int time=0;
  bool both=false;
  while(radius1<ball1 || radius2<ball2){
	if(both){
		ledControl->drawCombined(start, radius1, c1, tau, radius2, c2);
	}
	else{
   	  ledControl->setVolume(start, radius1, 255, 0 , 0);
      if(time>(distance/TIMESTEP)) both=true;
	}

    ledControl->show();
    ledControl->updateClock(TIMESTEP);
	delay(TIMESTEP); 
    time+=TIMESTEP;
    radius1 = (radius1 <ball1 ) ? radius1 + STEPSIZE : radius1;
    radius2 = (radius2 <ball2 ) ? radius2 + STEPSIZE : radius2;
	}

  delay(2000);
  ledControl->clear();
}
