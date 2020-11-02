#include "Model.h"
#include <iostream>
#include <string>

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
  //mainhcharacter pas de sprite
  allDraws.push_back(this->mainCharacter);

  for(unsigned int i = 0; i < this->entities.size(); i++){
    allDraws.push_back(this->entities[i]);
  }

  this->view.render(allDraws);
}
