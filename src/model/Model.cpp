#include "Model.h"

Model::Model(View &view):view(view), map(Map(50,50)){}

void Model::update(){//loop update

}

void Model::render(){
  std::vector<EntityDrawable> allDraws;

  for(int i = 0; i < map.getLenght(); i++){
    for(int j = 0; j < map.getWidth(); j++){
      allDraws.push_back(this->map.getTile(i,j));
    }
  }

  for(int i = 0; i < this->entities.size(); i++){
    allDraws.push_back(this->entities[i]);
  }

  this->view.render(allDraws);
}
