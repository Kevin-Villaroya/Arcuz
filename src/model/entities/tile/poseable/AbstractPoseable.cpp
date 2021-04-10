#include "AbstractPoseable.h"
#include "tree/Tree.h"
#include "stone/Stone.h"
#include "water/Water.h"

AbstractPoseable AbstractPoseable::EMPTY_POSEABLE("Empty", true, false);
std::vector<std::string> AbstractPoseable::typePoseable;

AbstractPoseable::AbstractPoseable(const std::string& name):AbstractPoseable(name, true, false){}

AbstractPoseable::AbstractPoseable(const std::string& name, bool isTraversable, bool recoverable) : EntityDrawableAnimated(){
  this->name = name;
  this->traversable = isTraversable;
  this->recoverable = recoverable;
}

bool AbstractPoseable::isRecoverable(){
  return this->recoverable;
}

void AbstractPoseable::setRecoverable(bool recoverable){
  this->recoverable = recoverable;
}

float AbstractPoseable::getEntityScale(){
  return 1;
}

bool AbstractPoseable::isTraversable(){
  return this->traversable;
}

std::string AbstractPoseable::getName(){
  return this->name;
}

AbstractPoseable* AbstractPoseable::getAbstractPosable(const std::string& namePoseable){

  if(namePoseable.compare("tree") == 0){
    return new Tree();
  }else if(namePoseable.compare("stone") == 0){
    return new Stone();
  }else if(namePoseable.compare("water") == 0){
    return new Water();
  }else{
    return &AbstractPoseable::EMPTY_POSEABLE;
  }
}

void AbstractPoseable::setCollisionPosition(float x, float y){

  this->collisionPoint.x =  x;
  this->collisionPoint.y =  y;

  if(this->getTexture() != NULL &&  x - (this->getTexture()->getSize().x * this->getScale().x) / 2 >= 0 && y - this->getTexture()->getSize().y * this->getScale().y >= 0){
     sf::Transformable::setPosition(x - (this->getTexture()->getSize().x * this->getScale().x) / 2, y - this->getTexture()->getSize().y * this->getScale().y);
  }else{
    sf::Transformable::setPosition(x, y);
  }
  
}

void AbstractPoseable::setCollisionPosition(const sf::Vector2f &position){
  this->setPosition(position.x, position.y);
}