#include "../../include/Mounts/BasicMount.h"

BasicMount::BasicMount() {
  this->visible = false;
  this->width = 8;
  this->height = 64;
}

BasicMount::~BasicMount() {
  clean();
}


void BasicMount::setTexture() {
  if(currentTexture == 1) {
    glBindTexture(GL_TEXTURE_2D, getBasicMountBrightTexture());
  } else {
    glBindTexture(GL_TEXTURE_2D, getBasicMountTexture());
  }
}

void BasicMount::defaults() {
  health = 10;
}

