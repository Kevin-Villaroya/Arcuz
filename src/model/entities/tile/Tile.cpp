#include "Tile.h"
#include "../../../viewer/texture/TextureTile.h"
#include <iostream>

Tile Tile::EMPTY_TILE(TypeTile::EMPTY);

Tile::Tile(TypeTile type) : EntityDrawable(true), poseable(&AbstractPoseable::EMPTY_POSEABLE){
  this->typeEntity = TypeEntity::tile; 
  this->type = type;
  this->setSpriteByType(type);
  this->originOfPoseable = false;

  this->poseable = &AbstractPoseable::EMPTY_POSEABLE;
}

bool Tile::update(){
  if(this->originOfPoseable && this->poseable != &AbstractPoseable::EMPTY_POSEABLE){
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
    case TypeTile::GRASS:
      this->setTexture(*TextureTile::GRASS_TEXTURE);
      break;
    case TypeTile::GROUND:
      this->setTexture(*TextureTile::GROUND_TEXTURE);
      break;
    case TypeTile::EMPTY:
      this->setTexture(*TextureTile::EMPTY_TEXTURE);
      break;
    case TypeTile::MOUNTAIN:
      this->setTexture(*TextureTile::MOUNTAIN_TEXTURE);
      break;
    case TypeTile::FOREST:
      this->setTexture(*TextureTile::FOREST_TEXTURE);
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

void Tile::setOriginPoseable(bool value){
  this->originOfPoseable = value;
}

void Tile::removePoseable(){
  if(this->originOfPoseable && this->poseable != &AbstractPoseable::EMPTY_POSEABLE){
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