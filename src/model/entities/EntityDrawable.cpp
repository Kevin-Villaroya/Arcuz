#include "EntityDrawable.h"
#include <SFML/Graphics/Texture.hpp>

EntityDrawable::EntityDrawable() : EntityDrawable(false){}

EntityDrawable::EntityDrawable(bool isSpriteFixe){
  this->isSpriteFixe = isSpriteFixe;
  this->direction = Direction::right;
}

unsigned int EntityDrawable::getPosX() const{
  return this->getPosition().x;
}

unsigned int EntityDrawable::getPosY() const{
  return this->getPosition().y;
}

unsigned int EntityDrawable::getHeight() const{
  if(this->getTexture() == nullptr){
    return 0;
  }
  return this->getTexture()->getSize().y;
}

unsigned int EntityDrawable::getWidth() const{
  if(this->getTexture() == nullptr){
    return 0;
  }
  return this->getTexture()->getSize().x;
}

void EntityDrawable::setTexture(const sf::Texture &texture){
  Sprite::setTexture(texture);
  this->setOriginCenter();
}

void EntityDrawable::update(){}

void EntityDrawable::watchDirection(){
  if(!this->isSpriteFixe){
    if(this->direction == Direction::right){
      this->setTextureRect(sf::IntRect(0, 0, this->getWidth(), this->getHeight()));
    }else if(this->direction == Direction::left){
      this->setTextureRect(sf::IntRect(this->getWidth(), 0, -(int)this->getWidth(), this->getHeight()));
    }
  }
}

void EntityDrawable::setOriginCenter(){
  //this->setOrigin(this->getTexture()->getCenter().x, this->getTexture()->getCenter().y);
}
