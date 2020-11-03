#include "Tile.h"
#include "../../../viewer/texture/TextureTile.h"

Tile::Tile(TypeTile type, bool block){
  this->block = block;
  this->setSpriteByType(type);
}

void Tile::update(){}

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
    case GROUND_GRASS:
      this->setTexture(*TextureTile::GROUND_GRASS_TEXTURE);
      break;
  }
}
