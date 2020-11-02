#include "Tile.h"

const TextureTool* Tile::GRASS_TEXTURE = new TextureTool("assets/tiles/tall_grass.png");
const TextureTool* Tile::GROUND_TEXTURE = new TextureTool("assets/tiles/ground.png");
const TextureTool* Tile::GROUND_GRASS_TEXTURE = new TextureTool("assets/tiles/grass.png");

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
      this->setTexture(*Tile::GRASS_TEXTURE);
      break;
    case GROUND:
      this->setTexture(*Tile::GROUND_TEXTURE);
      break;
    case GROUND_GRASS:
      this->setTexture(*Tile::GROUND_GRASS_TEXTURE);
      break;
  }
}
