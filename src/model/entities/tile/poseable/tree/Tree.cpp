#include "Tree.h"
#include "../../../../../viewer/texture/StructureTexture.h"
#include <iostream>

Tree::Tree() : AbstractPoseable("tree", false, true){
  this->addAnimation(Animation(StructureTexture::getTexturesOf("tree")), "idle");
  this->setDelayOfAnimation(9);
  this->playAnimation("idle");
}