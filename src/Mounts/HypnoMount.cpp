#include "../../include/Mounts/HypnoMount.h"

HypnoMount::HypnoMount() {
  visible = false;
  width = 75/3.73;
  height = 75/3.73;
}

HypnoMount::~HypnoMount() {
  clean();
}

void HypnoMount::setTexture() {
  glBindTexture(GL_TEXTURE_2D, getHypnoMountTexture(isLeft));
}

void HypnoMount::defaults() {
  width = 75/3.73;
  height = 75/3.73;
  health = 20;
}


