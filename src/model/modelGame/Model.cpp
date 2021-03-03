#include "Model.h"
#include <iostream>

Model::Model(View &view):view(view), map(Map(50,50)), mainCharacter(new Character()){
  this->view.centerViewOn(*mainCharacter);
  this->modelChanged = false;
}

void Model::update(){//loop update
  bool updated = this->mainCharacter->update();
  this->entitiesNeedUpdate.clear();

  for(unsigned int i = 0; i < this->entities.size(); i++){
    if(this->entities[i]->update()){
      updated = true;
      this->entitiesNeedUpdate.push_back(this->entities[i]);
    }
  }

  if(this->mainCharacter->update()){
    updated = true;
    this->entitiesNeedUpdate.push_back(this->mainCharacter);
  }
  this->modelChanged = updated;
}

void Model::render(){
  std::vector<EntityDrawable> allDraws;

  for(int i = 0; i < this->map.getLenght(); i++){
    for(int j = 0; j < this->map.getWidth(); j++){
      allDraws.push_back(this->map.getTile(i,j));
    }
  }

  for(unsigned int i = 0; i < this->entities.size(); i++){
    allDraws.push_back(*this->entities[i]);
  }

  this->view.render(*this->mainCharacter, allDraws);
}

Character* Model::getMainCharacter(){
  return this->mainCharacter;
}

bool Model::addCharacter(Character* character){
  bool alreadyExist = false;
  for(unsigned int i = 0; i < this->entities.size(); i++){
    if(this->entities[i]->getName().compare(character->getName()) == 0){
      alreadyExist = true;
    }
  }
  
  if(!alreadyExist){
    std::cout << "le joueur " << character->getName() << " est connecté" << std::endl;
    this->addEntity(character);
  }else{
    std::cout << "le joueur " << character->getName() << " existe déja ERREUR" << std::endl;
  }

  return !alreadyExist;
}

void Model::addEntity(EntityDrawable* entity){
  entity->setUid(this->entities.size() + 1);
  this->entities.push_back(entity);
}

const std::vector<EntityDrawable*>& Model::getEntities(){
  return this->entities;
}

void Model::setEntities(std::vector<EntityDrawable*>& entities){
  this->removeAllEntities();

  for(unsigned int i = 0; i < entities.size(); i++){
    this->entities.push_back(entities[i]);
  }
}

bool Model::existEntity(const std::string& name){
  bool find = false;
  for(unsigned int i = 0; i < this->entities.size() && !find; i++){
    if(this->entities[i]->getName().compare(name) == 0){
      find = true;
    }
  }
  return find;
}

bool Model::existEntity(const int uid){
  bool find = false;
  for(unsigned int i = 0; i < this->entities.size() && !find; i++){
    if(this->entities[i]->getUid() == uid){
      find = true;
    }
  }
  return find;
}

EntityDrawable* Model::getEntity(const int uid){
  for(unsigned int i = 0; i < this->entities.size(); i++){
    if(this->entities[i]->getUid()== uid){
      return this->entities[i];
    }
  }
  return NULL;
}

size_t Model::quantityOfEntities(){
  return this->entities.size();
}

void Model::removeAllEntities(){
  for(unsigned int i = 0; i < this->entities.size(); i++){
    EntityDrawable* entity = this->entities[i];
    delete entity;
  }
  this->entities.clear();
}

bool Model::updateNeededForEntities(){
  return this->modelChanged;
}

std::vector<EntityDrawable*>& Model::getEntitiesNeedUpdate(){
  return this->entitiesNeedUpdate;
}

void Model::removeEntitie(EntityDrawable& entitie){
  unsigned int i = 0;
  bool find = false;
  while(i < this->entities.size() || !find){
    if(this->entities[i] == &entitie){
      EntityDrawable* entityRemoved = this->entities[i];
      this->entities.erase(this->entities.begin() + i);
      delete entityRemoved;
      find = true;
    }
    i++;
  }
}

void Model::removeEntitie(const std::string& name){
  unsigned int i = 0;
  bool find = false;
  while(i < this->entities.size() || !find){
    if(this->entities[i]->getName().compare(name) == 0){
      this->entities.erase(this->entities.begin() + i);
      find = true;
    }
    i++;
  }
}

Model::~Model(){
  delete mainCharacter;
  for(size_t i = 0; i < this->entities.size(); i++){
    delete this->entities[i];
  }
}