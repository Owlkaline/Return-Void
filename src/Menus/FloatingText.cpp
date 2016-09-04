#include "../../include/Menus/FloatingText.h"

FloatingText::FloatingText() {

}

FloatingText::~FloatingText() {

}

void FloatingText::draw() { 
   lb.draw();
}

void FloatingText::clean() {

}

void FloatingText::setup(float x, float y, float width, float height, char* filename) {
  lb.setup(x, y, width, height, filename);
  this->x = x;
  this->y = y;
  ticks = 30;
  visible = true;
}

void FloatingText::setup(float x, float y,  const char* str, int length, float scale) {
  lb.setup(x, y, scale);
  lb.setText(str, length);
  this->x = x;
  this->y = y;
  ticks = 30;
  visible = true;
}

void FloatingText::update(float deltaTime) {
  ticks-=1*deltaTime;
  y+=1*deltaTime;
  lb.setY(y);
  if(ticks <= 0)
    visible = false;
}

void FloatingText::setTexture(char* filename) {
  lb.setTexture(filename);
}

void FloatingText::setText(const char* str, int length) {
  lb.setText(str, length);
}

void FloatingText::setTimer(int time) {
  ticks = time;
}

void FloatingText::setColour(float R, float G, float B) {
  lb.setColour(R,G,B);
}

