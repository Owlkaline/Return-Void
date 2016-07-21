#include "../../include/Mounts/BasicMount.h"

BasicMount::BasicMount() {
  visible = false;
  width = 8;
  height = 64;
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

void BasicMount::reset() {

}

void BasicMount::defaults() {
  width = 8;
  height = 64;
  health = 10;
}

