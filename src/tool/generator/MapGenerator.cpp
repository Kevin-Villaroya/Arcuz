#include "MapGenerator.h"
#include <iostream>
#include <cstdlib>

const float MapGenerator::PERCENT_MAX_EXTENSION_BIOME = 1.3;
const float MapGenerator::PERCENT_MIN_EXTENSION_BIOME = 0.7;
const float MapGenerator::PERCENT_EXTENSION_CHANCE[4] = {0.9, 0.75, 0.5, 0.2};

MapGenerator::MapGenerator(unsigned int sizeMin) : firstBiome(true){
  this->sizeMin = sizeMin;
}

void MapGenerator::generateMap(){
  int i = 0;

  do{
    this->generateMapProcess();

    for(unsigned int i = 0; i < this->biomes.size(); i++){
      this->biomes[i].incrementeSize();
    }
    i++;
  }while(this->generatedMap.size() < this->sizeMin && this->generatedMap[0].size() < this->sizeMin);
}

void MapGenerator::generateMapProcess(){
  this->resetGenerator();
  this->initSizeMap();
  this->randomizeNumberOfBiomes();

  bool allBiomesGenerated = false;

  while(!allBiomesGenerated){
    Biome* selectedBiome = &this->selectRandomBiome();

    sf::Vector2u positionFirstTile = selectTileFor(*selectedBiome);

    this->expandBiome(*selectedBiome, positionFirstTile);

    selectedBiome->setAverageOccurrenceLeft(selectedBiome->getAverageOccurrenceLeft() - 1);
    allBiomesGenerated = this->allBiomesAreGenerated();
  }
  this->deleteUnusedMap();
  this->addOutline();
}

void MapGenerator::addBiome(const Biome biome){
  this->biomes.push_back(biome);
}

void MapGenerator::initSizeMap(){
  srand((unsigned int)time(0));
  unsigned int sizeMax = 0;

  for(unsigned int i = 0; i < this->biomes.size(); i++){
    this->biomes[i].reset();
    sizeMax += (this->biomes[i].getSize() * MapGenerator::PERCENT_MAX_EXTENSION_BIOME) * (this->biomes[i].getAverageOccurrence() + 1);
  }

  for(unsigned int i = 0; i < sizeMax; i++){
    std::vector<int> line;
    std::vector<int> lineVisite;
    for(unsigned int j = 0; j < sizeMax; j++){
      line.push_back(-1);
      lineVisite.push_back(0);
    }
    this->generatedMap.push_back(line);
    this->alreadyVisited.push_back(lineVisite);
  }
}

void MapGenerator::randomizeNumberOfBiomes(){

  for(unsigned int i = 0; i < this->biomes.size(); i++){
    int nbOccurrence = rand()%(3) + (this->biomes[i].getAverageOccurrenceLeft() - 1);
    this->biomes[i].setAverageOccurrenceLeft(nbOccurrence);
  }
}

void MapGenerator::deleteUnusedMap(){
  bool findBiomeEmpty = false;

  for(unsigned int i = 0; i < this->generatedMap.size(); i++){
    for(unsigned int j = 0; j < this->generatedMap[i].size(); j++){
      if(this->generatedMap[i][j] >= 0){
        findBiomeEmpty = true;
      }
    }
    if(findBiomeEmpty == false){
      this->deleteRowMap(i);
      i--;
    }
    findBiomeEmpty = false;
  }

  for(unsigned int i = 0; i < this->generatedMap[0].size(); i++){
    for(unsigned int j = 0; j < this->generatedMap.size(); j++){
      if(this->generatedMap[j][i] >= 0){
        findBiomeEmpty = true;
      }
    }
    if(findBiomeEmpty == false){
      this->deleteColumnMap(i);
      i--;
    }
    findBiomeEmpty = false;
  }
}

void MapGenerator::deleteRowMap(unsigned int row){
  if (this->generatedMap.size() > row){
    this->generatedMap.erase( this->generatedMap.begin() + row );
  }
}

void MapGenerator::deleteColumnMap(unsigned int column){
  for (unsigned i = 0; i < this->generatedMap.size(); ++i){
    if (this->generatedMap[i].size() > column){
      this->generatedMap[i].erase(this->generatedMap[i].begin() + column);
    }
  }
}

void MapGenerator::setTileToBiome(sf::Vector2u posTile, Biome& biome){
  this->generatedMap[posTile.x][posTile.y] = this->getIdBiome(biome);
  this->alreadyVisited[posTile.x][posTile.y] = 2;
}

void MapGenerator::tryToconvert(sf::Vector2u posTile, Biome& biome, float chance){
  int chanceInt = chance * 100;
  int valueRand = rand() % 100;

  if(valueRand < chanceInt){
    this->setTileToBiome(posTile, biome);
  }
}

void MapGenerator::resetGenerator(){
  this->firstBiome = true;

  for(unsigned int i = 0; i < this->generatedMap.size(); i++){
    this->generatedMap[i].clear();
  }
  this->generatedMap.clear();

  for(unsigned int i = 0; i < this->alreadyVisited.size(); i++){
    this->alreadyVisited[i].clear();
  }
  this->alreadyVisited.clear();
}

Biome& MapGenerator::selectRandomBiome(){

  bool findBiome = false;
  int idBiome;

  if(!allBiomesAreGenerated()){
    while(!findBiome){
      idBiome = rand()%(this->biomes.size());
      if(this->biomes[idBiome].getAverageOccurrenceLeft() > 0){
        findBiome = true;
      }
    }
  }
  return this->biomes[idBiome];
}

sf::Vector2u MapGenerator::selectTileFor(Biome& biome){
  std::vector<sf::Vector2u> allPossibleTiles;
  bool closeFromABiome = false;

  for(unsigned int i = 0; i < this->generatedMap.size(); i++){
    for(unsigned int j = 0; j < this->generatedMap[i].size(); j++){
      for(unsigned int k = i; k < i + biome.getSize() - 1 && k < this->generatedMap.size(); k++){
        for(unsigned int m = j; m < j + biome.getSize() - 1 && m < this->generatedMap[k].size(); m++){
          if(this->generatedMap[k][m] >= 0){
            closeFromABiome = true;
          }
        }
      }
      if((closeFromABiome == true || this->firstBiome) && this->generatedMap[i][j] == -1){
        allPossibleTiles.push_back(sf::Vector2u(i,j));
      }
      closeFromABiome = false;
    }
  }
  int tileChoosed = rand() % allPossibleTiles.size();
  this->firstBiome = false;

  return allPossibleTiles[tileChoosed];
}

void MapGenerator::expandBiome(Biome& biome, sf::Vector2u posTile){
  this->setTileToBiome(posTile, biome);
  float currentChance = 1;

  for(unsigned int stepAutomaton = 0; stepAutomaton < biome.getSize(); stepAutomaton++){
    this->convertTemporaryTo(0);
  
    if(biome.getSize() - stepAutomaton < 4){
      currentChance = MapGenerator::PERCENT_EXTENSION_CHANCE[biome.getSize() - stepAutomaton];
    }

    for(unsigned int i = 0; i < this->generatedMap.size(); i++){
      for(unsigned int j = 0; j < this->generatedMap[i].size(); j++){

        if(this->generatedMap[i][j] == this->getIdBiome(biome) && this->alreadyVisited[i][j] == 0){
          for(unsigned int k = i - 1; k <= i + 1; k++){
            for(unsigned int m = j - 1; m <= j + 1; m++){
              if(k > 0 && m > 0 && k < this->generatedMap.size() && m < this->generatedMap[k].size() && this->generatedMap[k][m] == -1 && this->alreadyVisited[i][j] == 0){
                tryToconvert(sf::Vector2u(k,m), biome, currentChance);
              }
            }
          }

        }

      }
    }
  }
  this->convertTemporaryTo(1);
}

int MapGenerator::getIdBiome(Biome& biome){
  for(unsigned int i = 0; i < this->biomes.size(); i++){
    if(&biome == &this->biomes[i]){
      return i;
    }
  }
  return 0;
}

bool MapGenerator::allBiomesAreGenerated(){
  for(unsigned int i = 0; i < this->biomes.size(); i++){
    if(this->biomes[i].getAverageOccurrenceLeft() > 0){
      return false;
    }
  }
  return true;
}

void MapGenerator::convertTemporaryTo(int value){
  for(unsigned int i = 0; i < this->generatedMap.size(); i++){
    for(unsigned int j = 0; j < this->generatedMap[i].size(); j++){
      if(this->alreadyVisited[i][j] == 2){
        this->alreadyVisited[i][j] = value;
      }
    }
  }
}

void MapGenerator::createMap(Map& map){
  map = Map (this->generatedMap.size(), this->generatedMap[0].size());

  for(unsigned int i = 0; i < this->generatedMap.size(); i++){
    for(unsigned int j = 0; j < this->generatedMap[i].size(); j++){

      if(this->generatedMap[i][j] == -1){
        map.setTile(Tile(TypeTile::EMPTY), i, j);
      }else{
        map.setTile(Tile(this->biomes[this->generatedMap[i][j]].getTypeTile()), i, j);
      }
    }
  }

  this->generatePoseables(map);
}

void MapGenerator::addOutline(){

  for(unsigned int i = 0; i < this->generatedMap.size(); i++){
    for(unsigned int j = 0; j < this->generatedMap[i].size(); j++){
      if(i < 2 || j < 2 || i > this->generatedMap.size() - 2 || j > this->generatedMap[i].size() - 2){
        this->generatedMap[i][j] = -1;
      }
    }
  }
}

void MapGenerator::generatePoseables(Map& map){
   for(unsigned int i = 0; i < this->generatedMap.size(); i++){
    for(unsigned int j = 0; j < this->generatedMap[i].size(); j++){
      if(this->generatedMap[i][j] >= 0){
        AbstractPoseable* poseable = this->biomes[this->generatedMap[i][j]].getPoseable();
        map.getTile(i,j).setPoseable(poseable, true);
      }else{
        AbstractPoseable* poseable = AbstractPoseable::getAbstractPosable("water");
        map.getTile(i,j).setPoseable(poseable, true);
      }
    }
   }
}

void MapGenerator::displayGeneratedMap(){
  for(unsigned int i = 0; i < this->generatedMap.size(); i++){
    for(unsigned int j = 0; j < this->generatedMap[i].size(); j++){

      if(this->generatedMap[i][j] < 0){
        std::cout << this->generatedMap[i][j] <<"|";
      }else{
        std::cout << " "<<this->generatedMap[i][j] << "|";
      }

    }
    std::cout << std::endl;
  }
}