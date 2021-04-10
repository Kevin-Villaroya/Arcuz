#include "Map.h"
#include <string>

Map::Map(){}

Map::Map(int lenght, int width) : tiles(std::vector<std::vector<Tile>> (lenght, std::vector<Tile>(width, Tile(TypeTile::GROUND)))) {
  this->lenght = lenght;
  this->width = width;

  for(int i = 0; i < lenght; i++){
    for(int j = 0; j < width; j++){
      unsigned int heightTile = this->tiles[i][j].getHeight();
      unsigned int widthTile = this->tiles[i][j].getWidth();
      if(i == 0 || j == 0 || i == lenght - 1 || j == width - 1){
        this->setTile(Tile(TypeTile::GRASS), i, j);
      }
      this->tiles[i][j].setPosition(i * widthTile, j * heightTile);
    }
  }
}

int Map::getLenght(){
  return this->lenght;
}

int Map::getWidth(){
  return this->width;
}

sf::Vector2u Map::getSizeTile(){
  return this->tiles[0][0].getTexture()->getSize();
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
      this->tiles[x][y].setPosition(x * newTile.getWidth(), y * newTile.getHeight());
    }
}

  bool Map::outOfBounds(int x, int y){
    return x < 0 || y < 0 || x > this->lenght || y > this->width;
  }
