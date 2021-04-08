#include "AbstractPoseable.h"

AbstractPoseable AbstractPoseable::EMPTY_POSEABLE("Empty", true, false);

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