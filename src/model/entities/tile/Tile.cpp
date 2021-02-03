#include "Tile.h"
#include "../../../viewer/texture/TextureTile.h"

Tile::Tile(TypeTile type, bool block) : EntityDrawable(true){
  this->block = block;
  this->typeEntity = TypeEntity::tile; 
  this->setSpriteByType(type);
}

bool Tile::update(){return false;}

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
