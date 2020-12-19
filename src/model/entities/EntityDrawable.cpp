#include "EntityDrawable.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

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

sf::Packet& operator <<(sf::Packet& packet, const EntityDrawable& entity){
    return packet << entity.getPosX() << entity.getPosY();
}

sf::Packet& operator >>(sf::Packet& packet, EntityDrawable& entity){
  unsigned int posX;
  unsigned int posY;
  std::cout << "ok0" << std::endl;
  std::cout << "ok1" << std::endl;
  packet >> posX >> posY;
  std::cout << "ok2" << std::endl;
  entity.setPosition(posX, posY);
  std::cout << "ok3" << std::endl;
  return packet;
}

sf::Packet& operator <<(sf::Packet& packet, const sf::Texture& texture){
  return packet << texture;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Texture& texture){
  std::cout << "ok4" << std::endl;
  sf::Texture textureTemp;
  std::cout << "ok5" << std::endl;
  return packet >> texture;
}
