#include "3Dline.h"
#include "config.h"
#include <Arduino.h>  // Required for Arduino functions
#include <Adafruit_NeoPixel.h>


void runTrack(LEDSystem* ledControl) {

  int brightness=random(10,25);

  int face = random(0, 6); // bottom, left, back, right, front, top
  int startx = random(0, 100); // coordinate x1 in cm
  int starty = random(0, 100); // coordinate y1 in cm
  int endx = random(0, 100); // coordinate x2 in cm
  int endy = random(0, 100); // coordinate y2 in cm


  int startz = 0; // Initialize z coordinate for start point
  int endz = 0; // Initialize z coordinate for end point

  // Convert face and coordinates to 3D coordinates
  coordinate startPoint;
  coordinate endPoint;

	//Set x,y,z points based on starting face
  switch (face) {
    case 0: // bottom
      startPoint.x = startx;
      startPoint.y = starty;
      startPoint.z = 0-brightness;
      endPoint.x = endx;
      endPoint.y = endy;
      endPoint.z = 100+brightness;
      break;
    case 1: // left
      startPoint.x = 0-brightness;
      startPoint.y = startx;
      startPoint.z = starty;
      endPoint.x = 100+brightness;
      endPoint.y = endx;
      endPoint.z = endy;
        break;
    case 2: // back
      startPoint.x = startx;
      startPoint.y = 0-brightness;
      startPoint.z = starty;
      endPoint.x = endx;
      endPoint.y = 100+brightness;
      endPoint.z = endy;
      break;
    case 3: // right
      startPoint.x = 100+brightness;
      startPoint.y = startx;
      startPoint.z = starty;
      endPoint.x = 0-brightness;
      endPoint.y = endx;
      endPoint.z = endy;
      break;
    case 4: // front
      startPoint.x = startx;
      startPoint.y = 100+brightness;
      startPoint.z = starty;
      endPoint.x = endx;
      endPoint.y = 0-brightness;
      endPoint.z = endy;
      break;
    case 5: // top
      startPoint.x = startx;
      startPoint.y = starty;
      startPoint.z = 100+brightness;
      endPoint.x = endx;
      endPoint.y = endy;
      endPoint.z = 0-brightness;
      break;
  }

	float distance = sqrt(pow(endPoint.x - startPoint.x, 2) +
                        pow(endPoint.y - startPoint.y, 2) +
                        pow(endPoint.z - startPoint.z, 2));


	coordinate currentCoords = {startPoint.x, startPoint.y, startPoint.z};

  ledControl->resetClock();

	while(distance>0-2*brightness){//Move the current point by the STEPSIZE
    currentCoords.x += (endPoint.x > currentCoords.x) ? STEPSIZE : -STEPSIZE;
    currentCoords.y += (endPoint.y > currentCoords.y) ? STEPSIZE : -STEPSIZE;
    currentCoords.z += (endPoint.z > currentCoords.z) ? STEPSIZE : -STEPSIZE;
		distance-=sqrt(3)*STEPSIZE;
	
    ledControl->setVolume(currentCoords, brightness);
    ledControl->show();
    ledControl->updateClock(TIMESTEP);
		delay(TIMESTEP);
	}

	delay(2000);
  ledControl->clear();
}
