#include "../../include/Menus/FloatingText.h"

FloatingText::FloatingText() {

}

FloatingText::~FloatingText() {

}

void FloatingText::draw(GraphicsHandler *graphics) { 
   lb.draw(graphics);
}

void FloatingText::clean() {

}

void FloatingText::setup(float x, float y, float width, float height, std::string filename) {
  lb.setup(x, y, width, height, filename);
  this->x = x;
  this->y = y;
  ticks = 400;
  visible = true;
}

void FloatingText::setup(float x, float y, float scale, std::string str) {
  lb.setup(x, y, scale);
  lb.setText(str);
  this->x = x;
  this->y = y;
  ticks = 400;
  visible = true;
}

void FloatingText::update(float deltaTime) {
  ticks-=1*deltaTime;
  y+=1*deltaTime;
  lb.setY(y);
  if(ticks <= 0)
    visible = false;
}

void FloatingText::setTexture(std::string filename) {
  lb.setTexture(filename);
}

void FloatingText::setText(std::string str) {
  lb.setText(str);
}

void FloatingText::setTimer(int time) {
  ticks = time;
}

void FloatingText::setColour(float R, float G, float B) {
  lb.setColour(R,G,B);
}

