#include "Model.h"
#include "../../tool/FontTool.h"
#include <iostream>

Model::Model(View &view):view(view), map(Map(50,50)), mainCharacter(new Character()){
  this->view.centerViewOn(*mainCharacter);
  this->modelChanged = false;

  this->addEntityName(mainCharacter->getName());

  this->mainCharacter->setDelayOfAnimation(1);
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

  this->updateEntitiesName();

  this->modelChanged = updated;
}

void Model::render(){
  std::vector<sf::Drawable*> allDraws;

  for(int i = 0; i < this->map.getLenght(); i++){
    for(int j = 0; j < this->map.getWidth(); j++){
      allDraws.push_back(&this->map.getTile(i,j));
    }
  }

  for(unsigned int i = 0; i < this->entities.size(); i++){
    allDraws.push_back(this->entities[i]);
  }

  for(unsigned int i = 0; i < this->nameEntities.size(); i++){
    allDraws.push_back(this->nameEntities[i]);
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

  this->addEntityName(entity->getName());
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

void Model::setNameCharacter(const std::string& name){
  this->mainCharacter->setName(name);
  std::cout << name << std::endl;
  this->nameEntities[0]->setString(name);
}

size_t Model::quantityOfEntities(){
  return this->entities.size();
}

void Model::removeAllEntities(){
  for(unsigned int i = 0; i < this->entities.size(); i++){
    EntityDrawable* entity = this->entities[i];
    delete entity;
  }

  for(unsigned int i = 0; i < this->entities.size(); i++){
    sf::Text* nameEntity = this->nameEntities[i];
    delete nameEntity;
  }

  this->nameEntities.clear();
  this->entities.clear();

  this->addEntityName(mainCharacter->getName());
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
      sf::Text* nameEntity = this->nameEntities[i+1];

      this->entities.erase(this->entities.begin() + i);
      this->nameEntities.erase(this->nameEntities.begin() + i + 1);

      delete entityRemoved;
      delete nameEntity;

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
      EntityDrawable* entityRemoved = this->entities[i];
      sf::Text* nameEntity = this->nameEntities[i+1];

      this->entities.erase(this->entities.begin() + i);
      this->nameEntities.erase(this->nameEntities.begin() + i + 1);

      delete entityRemoved;
      delete nameEntity;

      find = true;
    }
    i++;
  }
}

void Model::addEntityName(const std::string& name){
  int sizeNameEntity = this->nameEntities.size();

  this->nameEntities.push_back(new sf::Text());
  this->nameEntities[sizeNameEntity]->setFont(FontTool::REGULAR_FONT);
  this->nameEntities[sizeNameEntity]->setFillColor(sf::Color::Black);
  this->nameEntities[sizeNameEntity]->setCharacterSize(8);
  this->nameEntities[sizeNameEntity]->setString(name);
}

void Model::updateEntitiesName(){

  float posXName = 0;
  float posYName = 0;

  posXName = this->mainCharacter->getPosition().x - this->nameEntities[0]->getGlobalBounds().width / 2 + this->mainCharacter->getTexture()->getSize().x / 4;
  posYName = this->mainCharacter->getPosition().y - this->nameEntities[0]->getGlobalBounds().height;

  this->nameEntities[0]->setPosition(posXName, posYName);

  for(unsigned int posEntityName = 1; posEntityName < this->nameEntities.size(); posEntityName++){
    unsigned int posEntity = posEntityName - 1;
    if(posEntity < this->entities.size()){
      posXName = this->entities[posEntity]->getPosition().x - this->nameEntities[posEntityName]->getGlobalBounds().width / 2 + this->entities[posEntity]->getTexture()->getSize().x / 4;
      posYName = this->entities[posEntity]->getPosition().y - this->nameEntities[posEntityName]->getGlobalBounds().height;

      this->nameEntities[posEntityName]->setPosition(posXName, posYName);
    }
  }
}

Model::~Model(){
  delete mainCharacter;
  for(size_t i = 0; i < this->entities.size(); i++){
    delete this->entities[i];
  }
  for(size_t i = 0; i < this->nameEntities.size(); i++){
    delete this->nameEntities[i];
  }
}