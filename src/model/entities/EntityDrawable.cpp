#include "EntityDrawable.h"
#include <SFML/Graphics/Texture.hpp>

EntityDrawable::EntityDrawable(){
  this->direction = Direction::right;
  this->setOriginCenter();
}

unsigned int EntityDrawable::getPosX() const{
  return this->getPosition().x;
}

unsigned int EntityDrawable::getPosY() const{
  return this->getPosition().y;
}

unsigned int EntityDrawable::getLenght() const{
  if(this->getTexture() == nullptr){
    return 0;
  }
  return this->getTexture()->getSize().x;
}

unsigned int EntityDrawable::getWidth() const{
  if(this->getTexture() == nullptr){
    return 0;
  }
  return this->getTexture()->getSize().y;
}

void EntityDrawable::update(){}

void EntityDrawable::watchDirection(){

}

void EntityDrawable::setOriginCenter(){
  this->setPosition(this->getWidth() / 2, this->getLenght() / 2);
}
