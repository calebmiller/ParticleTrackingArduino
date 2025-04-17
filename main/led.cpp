#include "led.h"
#include "config.h"

void LEDSystem::initLEDs(Adafruit_NeoPixel* strips, int numStrips){

  this->strips = strips;
  this->numStrips = numStrips;
  for (int i = 0; i < numStrips; ++i) {
    strips[i].begin();
    strips[i].show();
    strips[i].setBrightness(100);
  }
  clear();
  int rows = 7;
  float distance = 16.0;
  generate_grid(rows, distance);
  Serial.println("Geometry Generated");
}

void LEDSystem::setVolume(coordinate coor, float radius) {
  for(int i=0; i<460;i++){
    int xdiff=abs(points[i].x-coor.x);
    int ydiff=abs(points[i].y-coor.y);
    int zdiff=abs(points[i].z-coor.z);
    if(xdiff<radius && ydiff<radius && zdiff<radius){
      float dist= sqrt(pow(xdiff,2)+pow(ydiff,2)+pow(zdiff,2));
      float scale=1-(dist/radius);
      if (scale<0) scale=0;
      setPixel(pins[i].strip,pins[i].pixel,int(scale*255),int(scale*255),int(scale*255));
    }
  }
}

void LEDSystem::show() {
  for (int i = 0; i < 7; i++) {
    strips[i].show();
  }
}
void LEDSystem::clear(){
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < LED_COUNT; j++) {
      strips[i].setPixelColor(j, strips[i].Color(0, 0, 0));
    }
  strips[i].show();
  }

}

void LEDSystem::generate_grid(int rows, float distance) {
  int cnt=0;
  for (int row = 0; row < rows; row++) {
    int num_points = (row % 2 == 0) ? 7 : 6;
    bool top = (row % 2 == 0);
    int ledcnt=99;
    for (int col = 0; col < num_points; col++) {
      float x = col * distance * sqrt(3) / 2;
      float y = row * distance * sqrt(3) / 2;
      if (row % 2 == 1) x += distance * sqrt(3) / 4;      
      x += 8;
      y += 8;
      for(int lay=0; lay<10; lay++){
        int ledid = top ? (ledcnt - 9 + lay) : (ledcnt - lay);
        float z=lay*10+5;
        coordinate pnt = {int(x), int(y), int(z)};
        int strip_id = get_pin_id(int(y));
        pixel_ID pxl={strip_id,ledid};
        points[cnt]=pnt;
        pins[cnt]=pxl;
        cnt++;
      }
      top = !top;
      ledcnt -= 13;
    }
  }
}
int LEDSystem::get_pin_id(int y) {
  const int keys[] = {8, 21, 35, 49, 63, 77, 91}; //check these!!!!
  const int values[] = {2, 3, 4, 5, 6, 7, 8};
  for (int i = 0; i < 7; i++) {
    if (keys[i] == y) {
      return values[i];
    }
  }
  Serial.print("No Valid Key found");
  return -1; // Return -1 if the key is not found
}


void LEDSystem::printMap(){
  // Print the map for verification
  Serial.println("print map");
  for (int i=0; i<460; ++i) {
    Serial.print("Coordinate: ");
    Serial.print(points[i].x);
    Serial.print(", ");
    Serial.print(points[i].y);
    Serial.print(", ");
    Serial.print(points[i].z);
    Serial.print(" -> Pixel ID: ");
    Serial.print(pins[i].strip);
    Serial.print(", ");
    Serial.println(pins[i].pixel);
  }
}
void LEDSystem::setPixel(int strip, int pixel, int r, int g, int b){
  strips[strip].setPixelColor(pixel, strips[strip].Color(r,g,b));
}
void LEDSystem::assembly(int strip, int step){
	clear();
  //turn on each light in a seequence, pushing the button steps the lights one posistion  
}
void LEDSystem::redFlash(){
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < LED_COUNT; j++) {
      strips[i].setPixelColor(j, strips[i].Color(0, 0, 255)); //GBR
    }
  strips[i].show();
  }
  delay(500);
  clear();
}

