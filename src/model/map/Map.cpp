#include "Map.h"
#include <string>

Map::Map(){}

Map::Map(int lenght, int width) : tiles(std::vector<std::vector<Tile>> (lenght, std::vector<Tile>(width, Tile(TypeTile::GROUND, true)))) {
  this->lenght = lenght;
  this->width = width;

  for(int i = 0; i < lenght; i++){
    for(int j = 0; j < width; j++){
      unsigned int height = this->tiles[i][j].getHeight();
      unsigned int width = this->tiles[i][j].getWidth();
      this->tiles[i][j].setPosition(i * width, j * height);
      if(i == 0 || j == 0){
        this->tiles[i][j].setSpriteByType(TypeTile::GRASS);
      }
    }
  }
}

int Map::getLenght(){
  return this->lenght;
}

int Map::getWidth(){
  return this->width;
}

Tile& Map::getTile(int x, int y){
    if(this->outOfBounds(x,y)){
      throw std::string("ERREUR: SORTIE DE MAP");
    }else{
      return this->tiles[x][y];
    }
}

void Map::setTile(Tile newTile, int x, int y){
    if(this->outOfBounds(x,y)){
      throw std::string("ERREUR: SORTIE DE MAP");
    }else{
      this->tiles[x][y] = newTile;
    }
}

  bool Map::outOfBounds(int x, int y){
    return x < 0 || y < 0 || x > this->lenght || y > this->width;
  }
