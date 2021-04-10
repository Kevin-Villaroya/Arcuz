#include "Biome.h"

Biome::Biome(unsigned int size, unsigned int averageOccurrence, unsigned int averageAltitude){
  this->size = size;
  this->averageAltitude = averageAltitude;
  this->averageOccurrence = averageOccurrence;
  this->averageOccurrenceLeft = averageOccurrence;
}

void Biome::addPoseable(const std::string& poseableName, float chance){
  this->poseablesName.push_back(poseableName);
  this->poseableChances.push_back(chance);
}

void Biome::addTypeTile(TypeTile type, float chance){
   this->typesTiles.push_back(type);
  this->typeTileChances.push_back(chance);
}

unsigned int Biome::getSize(){
  return this->size;
}

unsigned int Biome::getAverageAltitude(){
  return this->averageAltitude;
}

unsigned int Biome::getAverageOccurrence(){
  return this->averageOccurrence;
}

unsigned int Biome::getAverageOccurrenceLeft(){
  return this->averageOccurrenceLeft;
}

void Biome::incrementeSize(){
  this->size++;
}

void Biome::reset(){
  this->averageOccurrenceLeft = averageOccurrence;
}

TypeTile Biome::getTypeTile(){
  int value = rand() % 100;
  float currentChance;

  for(unsigned int i = 0; i < this->typeTileChances.size(); i++){
    currentChance += this->typeTileChances[i] * 100;
    if(value <= currentChance){
      return this->typesTiles[i];
    }
  }
  return this->typesTiles[0];
}

AbstractPoseable* Biome::getPoseable(){
  int value = rand() % 100;
  float currentChance;

  for(unsigned int i = 0; i < this->poseableChances.size(); i++){
    currentChance += this->poseableChances[i] * 100;
    if(value <= currentChance){
      return AbstractPoseable::getAbstractPosable(this->poseablesName[i]);
    }
  }
  return &AbstractPoseable::EMPTY_POSEABLE;
}

void Biome::setAverageOccurrenceLeft(unsigned int nbOccurrence){
  this->averageOccurrenceLeft = nbOccurrence;
}