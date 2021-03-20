#include "EntityDrawable.h"
#include "../../tool/TextureTool.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

EntityDrawable::EntityDrawable() : EntityDrawable(false){}

EntityDrawable::EntityDrawable(bool isSpriteFixe){
  this->isSpriteFixe = isSpriteFixe;
  this->direction = Direction::right;
  this->uid = 0;
  this->oldPosX = this->getPosX();
  this->oldPosY = this->getPosY();
  this->name = "";
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

int EntityDrawable::getUid(){
  return this->uid;
}

void EntityDrawable::setName(const std::string& name){
  this->name = name;
}

void EntityDrawable::setUid(unsigned int uid){
  this->uid = uid;
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

const int EntityDrawable::getIndexTypeEntity() const{
  return this->typeEntity;
}

bool EntityDrawable::update(){
  bool updated = this->oldPosX != this->getPosX() || this->oldPosY != this->getPosY();

  this->oldPosX = this->getPosX();
  this->oldPosY = this->getPosY();

  return updated;
}

void EntityDrawable::noUpdate(){}

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
  packet << this->uid;
  packet << this->getName();
  packet << this->getPosX();
  packet << this->getPosY();
}

void EntityDrawable::putOut(sf::Packet& packet){
  unsigned int posX;
  unsigned int posY;
  std::string name;
  int uid;
  TextureTool texture;

  packet >> uid;
  packet >> name;
  packet >> posX;
  packet >> posY;

  this->uid = uid;
  this->name = name;
  this->setPosition(posX, posY);
}