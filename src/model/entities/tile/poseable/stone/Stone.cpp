#include "Stone.h"
#include "../../../../../viewer/texture/StructureTexture.h"
#include <iostream>

Stone::Stone() : AbstractPoseable("stone", false, true){
  this->addAnimation(Animation(StructureTexture::getTexturesOf("stone")), "idle");
  this->setDelayOfAnimation(0);
  this->playAnimation("idle");
}