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

void EntityDrawable::putIn(sf::Packet& packet) const{
  packet << this->getName();
  packet << this->getPosX();
  packet << this->getPosY();

  //Ajouter point commun a tout entity TODO
  //une classe heritante de EntityDrawable
  //un type d'animation, null si aucune
  //un numero de frame, 0 par défaut
}

void EntityDrawable::putOut(sf::Packet& packet){
  unsigned int posX;
  unsigned int posY;
  std::string name;

  TextureTool texture;
  packet >> name;
  packet >> posX;
  packet >> posY;

  this->name = name;
  this->setPosition(posX, posY);
}
