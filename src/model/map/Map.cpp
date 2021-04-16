#include "Map.h"
#include <string>
#include <iostream>

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

void Map::setSpawnPlayers(){
  bool findPos = false;
  bool findPoseableNotTraversable = false;

  for(int i = 0; i < this->getLenght() && !findPos; i++){
    for(int j = 0; j < this->getWidth() && !findPos; j++){

      for(int x = i; x < i + 5 && x < this->getLenght(); x++){
        for(int y = j; y < j + 5 && y < this->getWidth(); y++){
          if(!this->getTile(x, y).getPoseable()->isTraversable()){
            findPoseableNotTraversable = true;
          }
        }
      }

      if(findPoseableNotTraversable == false && this->getTile(i, j).getPoseable()->isTraversable()){
        this->posSpawn = sf::Vector2u(i, j);
        findPos = true;
      }
      findPoseableNotTraversable = false;
    }
  }
}

sf::Vector2u Map::getPosSpawnPlayers(){
  return this->posSpawn;
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

bool Map::outOfBounds(unsigned int x, unsigned int y){
  return x < 0 || y < 0 || x > this->lenght || y > this->width;
}

void Map::resizeMap(unsigned int lenght, unsigned int width){

  this->lenght = lenght;
  this->width = width;

  std::vector<std::vector<Tile>> tempMap;

  for(unsigned int i = 0; i < lenght; i++){
    std::vector<Tile> tempLine;
    for(unsigned int j = 0; j < width; j++){
      tempLine.push_back(Tile(TypeTile::GROUND));
    }
    tempMap.push_back(tempLine);
  }

  this->tiles = tempMap;
}

void Map::putIn(sf::Packet& packet) const{
  packet << (unsigned int)this->tiles.size();
  packet << (unsigned int)this->tiles[0].size();

  for(unsigned int i = 0; i < this->tiles.size(); i++){
    for(unsigned int j = 0; j < this->tiles[i].size(); j++){
      this->tiles[i][j].putIn(packet);
    }
  }
}

void Map::putOut(sf::Packet& packet){
  unsigned int lenght;
  unsigned int width;

  packet >> lenght;
  packet >> width;

  this->resizeMap(lenght, width);

  for(unsigned int i = 0; i < this->lenght; i++){
    for(unsigned int j = 0; j < this->width; j++){
      this->setTile(this->tiles[i][j], i, j);
      this->tiles[i][j].putOut(packet);
    }
  }
}