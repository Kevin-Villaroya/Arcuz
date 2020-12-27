#include "EntityDrawable.h"
#include "../../tool/TextureTool.h"
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

TextureTool EntityDrawable::getTextureTool() const{
  TextureTool texture;
  texture.loadFromImage(this->getTexture()->copyToImage());
  return texture;
}

const std::string& EntityDrawable::getName() const{
  return this->name;
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

Direction EntityDrawable::getDirection() const{
  return this->direction;
}

bool EntityDrawable::getIsSpriteFixe() const{
  return this->isSpriteFixe;
}

sf::Packet& operator <<(sf::Packet& packet, const EntityDrawable& entity){
  std::cout << "test" << std::endl;
  TextureTool texture = entity.getTextureTool();
  std::cout << "not a bug" << std::endl;
  return packet << entity.getPosX() << entity.getPosY() << texture;
}

sf::Packet& operator >>(sf::Packet& packet, EntityDrawable& entity){
  unsigned int posX;
  unsigned int posY;

  TextureTool texture;
  packet >> posX >> posY >> texture;

  //entity.setTexture(texture);
  entity.setPosition(posX, posY);
  return packet;
}
