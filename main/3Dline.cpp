#include "3Dline.h"
#include <Arduino.h>  // Required for Arduino functions
#include <Adafruit_NeoPixel.h>

void runTrack(Adafruit_NeoPixel &strip) {
    int face = random(0, 6); // bottom, left, back, right, front, top
    int startx = random(0, 100); // coordinate x1 in cm
    int starty = random(0, 100); // coordinate y1 in cm
    int endx = random(0, 100); // coordinate x2 in cm
    int endy = random(0, 100); // coordinate y2 in cm

    int startz = 0; // Initialize z coordinate for start point
    int endz = 0; // Initialize z coordinate for end point

    // Convert face and coordinates to 3D coordinates
    int startCoords[3];
    int endCoords[3];

	//Set x,y,z points based on starting face
    switch (face) {
        case 0: // bottom
            startCoords[0] = startx;
            startCoords[1] = starty;
            startCoords[2] = 0;
            endCoords[0] = endx;
            endCoords[1] = endy;
            endCoords[2] = 100;
            break;
        case 1: // left
            startCoords[0] = 0;
            startCoords[1] = startx;
            startCoords[2] = starty;
            endCoords[0] = 100;
            endCoords[1] = endx;
            endCoords[2] = endy;
            break;
        case 2: // back
            startCoords[0] = startx;
            startCoords[1] = 0;
            startCoords[2] = starty;
            endCoords[0] = endx;
            endCoords[1] = 100;
            endCoords[2] = endy;
            break;
        case 3: // right
            startCoords[0] = 100;
            startCoords[1] = startx;
            startCoords[2] = starty;
            endCoords[0] = 0;
            endCoords[1] = endx;
            endCoords[2] = endy;
            break;
        case 4: // front
            startCoords[0] = startx;
            startCoords[1] = 100;
            startCoords[2] = starty;
            endCoords[0] = endx;
            endCoords[1] = 0;
            endCoords[2] = endy;
            break;
        case 5: // top
            startCoords[0] = startx;
            startCoords[1] = starty;
            startCoords[2] = 100;
            endCoords[0] = endx;
            endCoords[1] = endy;
            endCoords[2] = 0;
            break;
    }

	float distance = sqrt(pow(endCoords[0] - startCoords[0], 2) +
                          pow(endCoords[1] - startCoords[1], 2) +
                          pow(endCoords[2] - startCoords[2], 2));


	int currentCoords[3] = {startCoords[0], startCoords[1], startCoords[2]};
	while(distance>0){//Move the current point by the STEPSIZE
            currentCoords[0] += (endCoords[0] > currentCoords[0]) ? STEPSIZE : -STEPSIZE;
            currentCoords[1] += (endCoords[1] > currentCoords[1]) ? STEPSIZE : -STEPSIZE;
            currentCoords[2] += (endCoords[2] > currentCoords[2]) ? STEPSIZE : -STEPSIZE;
			distance-=sqrt(3)*STEPSIZE;
	
			LEDController.TurnON(currentCoords,LINERADIUS); //Turn on LEDs within certain distance of current location
			delay(5); //TIMESTEP
	}

	delay(2000);
}
