#include "../../include/Mounts/HypnoMount.h"

HypnoMount::HypnoMount() {
  visible = false;
  width = 75/3.73;
  height = 75/3.73;
}

HypnoMount::~HypnoMount() {
  clean();
}

std::string HypnoMount::getTexture() {
  //glBindTexture(GL_TEXTURE_2D, getHypnoMountTexture(isLeft));
  if(isLeft == 0)
    return "HypnoMountLeft";
  return "HypnoMountRight";
}

void HypnoMount::defaults() {
  width = 75/3.73;
  height = 75/3.73;
  health = 20;
}


