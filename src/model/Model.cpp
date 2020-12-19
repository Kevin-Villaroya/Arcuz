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

void Model::addCharacter(Character& character){
  entities.push_back(character);
}

const std::vector<EntityDrawable>& Model::getEntities(){
  return this->entities;
}

void Model::setEntities(std::vector<EntityDrawable>& entities){
  for(unsigned int i = 0; i < entities.size(); i++){
    this->entities[i] = entities[i];
  }
  std::cout << "test" << std::endl;
}
