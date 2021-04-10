#include "Model.h"
#include "../../tool/FontTool.h"
#include "../tile/poseable/tree/Tree.h"
#include "../tile/poseable/stone/Stone.h"
#include "../../../tool/generator/Biome.h"
#include "../../../tool/generator/MapGenerator.h"
#include <iostream>

Model::Model(View &view, unsigned int sizeMinMap):view(view), map(Map(15,15)), mainCharacter(new Character()){
  this->view.centerViewOn(*mainCharacter);
  this->modelChanged = false;

  this->sizeMinMap = sizeMinMap;

  this->addEntityName(mainCharacter->getName());
  this->mainCharacter->setDelayOfAnimation(1);
}

void Model::update(){//loop update
  bool updated = this->mainCharacter->update();
  this->entitiesNeedUpdate.clear();

  this->moveCharacter();

  for(unsigned int i = 0; i < this->entities.size(); i++){
    if(this->entities[i]->update()){
      updated = true;
      this->entitiesNeedUpdate.push_back(this->entities[i]);
    }
  }

  for(int i = 0; i < this->map.getLenght(); i++){
    for(int j = 0; j < this->map.getWidth(); j++){
      this->map.getTile(i,j).update();
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

  float sizeXTile = this->map.getTile(0,0).getTexture()->getSize().x;
  float sizeYTile = this->map.getTile(0,0).getTexture()->getSize().y; 

  for(int i = 0; i < this->map.getLenght(); i++){
    for(int j = 0; j < this->map.getWidth(); j++){
      allDraws.push_back(&this->map.getTile(i,j));
    }
  }

  for(int j = 0; j < this->map.getWidth(); j++){
    for(int i = 0; i < this->map.getLenght(); i++){
      if(this->map.getTile(i,j).isOriginPoseable()){
        allDraws.push_back(this->map.getTile(i,j).getPoseable());
      }

      for(unsigned int k = 0; k < this->entities.size(); k++){
        if((int)(this->entities[i]->getOriginCollision().x / sizeXTile) == i && (int)(this->entities[i]->getOriginCollision().y / sizeYTile) == j){
          allDraws.push_back(this->entities[i]);
        }
      }

      if((int)(this->mainCharacter->getOriginCollision().x / sizeXTile) == i && (int)(this->mainCharacter->getOriginCollision().y / sizeYTile) == j){
        allDraws.push_back(this->mainCharacter);
      }
    }
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
    std::cout << "the player " << character->getName() << " is connected" << std::endl;
    this->addEntity(character);
  }else{
    std::cout << "the player " << character->getName() << " already exist ERROR" << std::endl;
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

void Model::moveCharacter(){
  Direction direction = this->mainCharacter->getDirection();
  int speed = this->mainCharacter->getSpeed();

  float xPos = this->mainCharacter->getPosition().x;
  float yPos = this->mainCharacter->getPosition().y;
  float xCol = this->mainCharacter->getOriginCollision().x;
  float yCol = this->mainCharacter->getOriginCollision().y;

  if(direction == Direction::right){
    xPos += speed;
    xCol += speed;
  }else if(direction == Direction::left){
    xPos -= speed;
    xCol -= speed;
  }else if(direction == Direction::up){
    yPos -= speed;
    yCol -= speed;
  }else if(direction == Direction::down){
    yPos += speed;
    yCol += speed;
  }

  if(!this->collisionWithABlockedTile(xCol, yCol)){
    this->mainCharacter->setPosition(xPos, yPos);
  }else{
    this->unstuckEntity(*this->mainCharacter);
  }
}

void Model::unstuckEntity(EntityDrawable& entity){
  float posX = this->mainCharacter->getOriginCollision().x;
  float posY = this->mainCharacter->getOriginCollision().y;

  sf::Vector2f originTile = sf::Vector2f(posX / this->map.getSizeTile().x, posY / this->map.getSizeTile().y );

  if(posX > originTile.x && posX < originTile.x + 3){
    entity.setPosition(originTile.x, entity.getPosition().y);

  }else if(posX < originTile.x - 3 + this->map.getSizeTile().x){
    entity.setPosition(originTile.x + this->map.getSizeTile().x, entity.getPosition().y);

  }else if(posY > originTile.y && posY < originTile.y + 3){
    entity.setPosition(originTile.x, entity.getPosition().y);

  }else if(posY < originTile.y - 3 + this->map.getSizeTile().y){
    entity.setPosition(originTile.x + this->map.getSizeTile().x, entity.getPosition().y);
  }
}

bool Model::collisionWithABlockedTile(float x, float y){
  float sizeXTile = this->map.getTile(0,0).getTexture()->getSize().x;
  float sizeYTile = this->map.getTile(0,0).getTexture()->getSize().y;

  if(this->map.getTile(x / sizeXTile, y / sizeYTile).isTraversable()){
    return false;
  }
  return true;
}

void Model::setNameCharacter(const std::string& name){
  this->mainCharacter->setName(name);
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
  this->nameEntities[sizeNameEntity]->setCharacterSize(6);
  this->nameEntities[sizeNameEntity]->setString(name);
}

void Model::updateEntitiesName(){

  float posXName = 0;
  float posYName = 0;

  float sizeXCharacter = this->mainCharacter->getTexture()->getSize().x * this->mainCharacter->getScale().x;

  posXName = this->mainCharacter->getPosition().x - this->nameEntities[0]->getGlobalBounds().width / 2 +  sizeXCharacter / 2;
  posYName = this->mainCharacter->getPosition().y - this->nameEntities[0]->getGlobalBounds().height;

  this->nameEntities[0]->setPosition(posXName, posYName);

  for(unsigned int posEntityName = 1; posEntityName < this->nameEntities.size(); posEntityName++){
    unsigned int posEntity = posEntityName - 1;
    if(posEntity < this->entities.size()){
      sizeXCharacter = this->entities[posEntity]->getTexture()->getSize().x * this->entities[posEntity]->getScale().x;

      posXName = this->entities[posEntity]->getPosition().x - this->nameEntities[posEntityName]->getGlobalBounds().width / 2 + sizeXCharacter / 2;
      posYName = this->entities[posEntity]->getPosition().y - this->nameEntities[posEntityName]->getGlobalBounds().height;

      this->nameEntities[posEntityName]->setPosition(posXName, posYName);
    }
  }
}

void Model::setSpawnPlayers(){
  bool findPos = false;

  for(int i = 0; i < this->map.getLenght() && !findPos; i++){
    for(int j = 0; j < this->map.getWidth() && !findPos; j++){
      if(this->map.getTile(i, j).getPoseable()->isTraversable()){
        this->posSpawn = sf::Vector2u(i, j);
        findPos = true;
      }
    }
  }

  this->mainCharacter->setPosition(this->posSpawn.x * this->map.getSizeTile().x, this->posSpawn.y * this->map.getSizeTile().y);
}

void Model::generateMap(){
  Biome plaine(5, 2, 1);
  plaine.addTypeTile(TypeTile::GRASS, 0.95);
  plaine.addTypeTile(TypeTile::GROUND, 0.05);

  Biome foret(3, 3, 3);
  foret.addTypeTile(TypeTile::FOREST, 1);
  foret.addPoseable("tree", 0.4);

  Biome mountain(4, 2, 3);
  mountain.addTypeTile(TypeTile::MOUNTAIN, 1);
  mountain.addPoseable("stone", 0.1);

  MapGenerator generator(this->sizeMinMap);
  generator.addBiome(plaine);
  generator.addBiome(foret);
  generator.addBiome(mountain);

  generator.generateMap();

  generator.createMap(this->map);

  this->setSpawnPlayers();
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