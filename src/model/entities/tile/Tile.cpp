#include "Tile.h"
#include "../../../viewer/texture/TextureTile.h"
#include <iostream>

Tile::Tile(TypeTile type) : EntityDrawable(true), poseable(&AbstractPoseable::EMPTY_POSEABLE){
  this->typeEntity = TypeEntity::tile; 
  this->setSpriteByType(type);
  this->originOfPoseable = false;

  this->poseable = &AbstractPoseable::EMPTY_POSEABLE;
}

bool Tile::update(){
  if(this->originOfPoseable){
    this->poseable->update();
  }
  
  return false;
  }

TypeTile Tile::getType() const{
  return this->type;
}

void Tile::setType(TypeTile type){
  this->type = type;
}

void Tile::setSpriteByType(TypeTile type){
  switch(type){
    case GRASS:
      this->setTexture(*TextureTile::GRASS_TEXTURE);
      break;
    case GROUND:
      this->setTexture(*TextureTile::GROUND_TEXTURE);
      break;
  }
}

void Tile::setPoseable(AbstractPoseable* poseable, bool isOrigin){
  this->poseable = poseable;
  this->originOfPoseable = isOrigin;

  if(this->originOfPoseable == true){
    this->poseable->setCollisionPosition(this->getOriginCollision().x, this->getOriginCollision().y);
  }
}

AbstractPoseable* Tile::getPoseable(){
  return this->poseable;
}

bool Tile::isOriginPoseable(){
  return originOfPoseable;
}

void Tile::removePoseable(){
  if(this->originOfPoseable){
    delete this->poseable;
  }
  
  this->poseable = &AbstractPoseable::EMPTY_POSEABLE;
  this->originOfPoseable = false;
}

bool Tile::isTraversable(){
  return this->poseable->isTraversable();
}

Tile::~Tile(){
  this->removePoseable();
}