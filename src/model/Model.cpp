#include "Model.h"
#include <iostream>

Model::Model(View &view):view(view), map(Map(50,50)), mainCharacter(Character()){
  this->view.centerViewOn(mainCharacter);
}

void Model::update(){//loop update
  this->mainCharacter.update();
  for(unsigned int i = 0; i < this->entities.size(); i++){
    this->entities[i].update();
  }
}

void Model::render(){
  std::vector<EntityDrawable> allDraws;

  for(int i = 0; i < this->map.getLenght(); i++){
    for(int j = 0; j < this->map.getWidth(); j++){
      allDraws.push_back(this->map.getTile(i,j));
    }
  }

  for(unsigned int i = 0; i < this->entities.size(); i++){
    allDraws.push_back(this->entities[i]);
  }

  this->view.render(this->mainCharacter, allDraws);
}

Character& Model::getMainCharacter(){
  return this->mainCharacter;
}

void Model::addCharacter(Character character){
  bool alreadyExist = false;
  for(unsigned int i = 0; i < this->entities.size(); i++){
    if(this->entities[i].getName().compare(character.getName()) == 0){
      alreadyExist = true;
    }
  }
  if(!alreadyExist){
    std::cout << "le joueur " << character.getName() << " est connecté" << std::endl;
    this->entities.push_back(character);
  }else{
    std::cout << "le joueur " << character.getName() << " existe déja ERREUR" << std::endl;
  }
}

void Model::addEntity(EntityDrawable entity){
  this->entities.push_back(entity);
}

const std::vector<EntityDrawable>& Model::getEntities(){
  return this->entities;
}

void Model::setEntities(std::vector<EntityDrawable>& entities){
  this->entities.clear();
  for(unsigned int i = 0; i < entities.size(); i++){
    this->entities.push_back(entities[i]);
  }
  std::cout<<"nombre entite enregistrer "<< this->entities.size() << std::endl;
}

void Model::removeEntitie(EntityDrawable& entitie){
  unsigned int i = 0;
  bool find = false;
  while(i < this->entities.size() || !find){
    if(&this->entities[i] == &entitie){
      std::cout << "Supression de l'entité " << this->entities[i].getName() << std::endl;
      this->entities.erase(this->entities.begin() + i);
      find = true;
    }
    i++;
  }
}

void Model::removeEntitie(const std::string& name){
  unsigned int i = 0;
  bool find = false;
  while(i < this->entities.size() || !find){
    if(this->entities[i].getName().compare(name) == 0){
      std::cout << "Supression de l'entité " << this->entities[i].getName() << std::endl;
      this->entities.erase(this->entities.begin() + i);
      find = true;
    }
    i++;
  }
}
