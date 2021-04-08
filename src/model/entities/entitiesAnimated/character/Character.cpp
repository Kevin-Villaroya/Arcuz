#include "Character.h"
#include "../../../viewer/texture/CharacterTexture.h"
#include <iostream>
#include <string>

const float Character::SCALE_GIRL = 0.22;
const float Character::SCALE_BOY = 0.30;

Character::Character() : Character("default"){}

Character::Character(std::string name) : Character(name, TypeCharacter::man){}

Character::Character(std::string name, TypeCharacter type) :type(type){
  this->addAnimation(setCharacterAnimation(type, TypeAnimationCharacter::idle), "idle");
  this->addAnimation(setCharacterAnimation(type, TypeAnimationCharacter::walk), "walk");
  this->addAnimation(setCharacterAnimation(type, TypeAnimationCharacter::run), "run");
  this->addAnimation(setCharacterAnimation(type, TypeAnimationCharacter::jump), "jump");
  this->addAnimation(setCharacterAnimation(type, TypeAnimationCharacter::dead), "dead");

  this->name = name;
  this->typeEntity = TypeEntity::character;
  this->playAnimation("idle");
  this->action = TypeAnimationCharacter::idle;
  this->speed = 0; this->direction = Direction::right;

  this->applySprite();
}

bool Character::update(){
  this->watchDirection();
  //this->moveCharacter();
  this->applySprite();

  bool updated = this->oldPosX != this->getPosX() || this->oldPosY != this->getPosY();

  this->oldPosX = this->getPosX();
  this->oldPosY = this->getPosY();

  return updated;
}

void Character::noUpdate(){
  this->stop();
}

void Character::moveCharacter(){
  if(this->direction == Direction::right){
    this->move(this->speed, 0);
  }else if(this->direction == Direction::left){
    this->move(-this->speed, 0);
  }else if(this->direction == Direction::up){
    this->move(0, -this->speed);
  }else if(this->direction == Direction::down){
    this->move(0, this->speed);
  }
}

void Character::walk(Direction newDirection){
  if(this->getNameAnimation().compare("walk") == 0 && this->direction == newDirection){
  }else{
    this->currentAnimation->reset();
    this->direction = newDirection;
    this->playAnimation("walk");
    this->action = TypeAnimationCharacter::walk;
  }
  this->setSpeedWhenWalk();
}

void Character::run(Direction newDirection){
  if(this->getNameAnimation().compare("run") == 0 && this->direction == newDirection){
  }else{
    this->currentAnimation->reset();
    this->direction = newDirection;
    this->playAnimation("run");
    this->action = TypeAnimationCharacter::run;
  }
  this->setSpeedWhenRun();
}

void Character::stop(){
  if(this->getNameAnimation().compare("idle") == 0){
  }else{
    this->playAnimation("idle");
    this->action = TypeAnimationCharacter::idle;
  }
  this->setSpeedWhenStopped();
}

void Character::jump(){
  if(this->getNameAnimation().compare("jump") == 0){
  }else{
    this->currentAnimation->reset();
    this->playAnimation("jump");
    this->action = TypeAnimationCharacter::jump;
  }
  this->setSpeedWhenWalk();
}

void Character::die(){
  if(this->getNameAnimation().compare("dead") == 0){
  }else{
    this->currentAnimation->reset();
    this->playAnimation("dead");
    this->action = TypeAnimationCharacter::dead;
  }
  this->setSpeedWhenStopped();
}

void Character::setSpeedWhenWalk(){
  this->speed = 4;
}

void Character::setSpeedWhenRun(){
  this->speed = 8;
}

void Character::setSpeedWhenStopped(){
  this->speed = 0;
}

void Character::setId(int id){
  this->id = id;
}

int Character::getId() const{
  return this->id;
}

int Character::getSpeed() const{
  return this->speed;
}

const TypeAnimationCharacter Character::getAnimation() const{
  return this->action;
}

const int Character::getType() const{
  return this->type;
}

TypeCharacter Character::getType(std::string type) const{

  if(type.compare("girl") == 0){
    return TypeCharacter::girl;
  }else{
    return TypeCharacter::man;
  }
}

std::string Character::getNameAnimationOfType(TypeAnimationCharacter type) const{
  switch(type){
    case TypeAnimationCharacter::dead:
      return "dead";
      break;
    case TypeAnimationCharacter::walk:
      return "walk";
      break;
    case TypeAnimationCharacter::run:
      return "run";
      break;
    case TypeAnimationCharacter::jump:
      return "jump";
      break;
    default:
      return "idle";
      break;
  }
}

void Character::setType(std::string nameType){
  TypeCharacter type = this->getType(nameType);
  this->setType(type);
}

void Character::setType(TypeCharacter type){
  this->type = type;

  this->clearAnimations();

  this->addAnimation(setCharacterAnimation(type, TypeAnimationCharacter::idle), "idle");
  this->addAnimation(setCharacterAnimation(type, TypeAnimationCharacter::walk), "walk");
  this->addAnimation(setCharacterAnimation(type, TypeAnimationCharacter::run), "run");
  this->addAnimation(setCharacterAnimation(type, TypeAnimationCharacter::jump), "jump");
  this->addAnimation(setCharacterAnimation(type, TypeAnimationCharacter::dead), "dead");
}

float Character::getEntityScale(){
   if(this->type == TypeCharacter::girl){
    return Character::SCALE_GIRL;
  }else if(this->type == TypeCharacter::man){
    return Character::SCALE_BOY;
  }
  return 1;
}

void Character::putIn(sf::Packet& packet) const{
  packet << this->getType();

  EntityDrawableAnimated::putIn(packet);
}

void Character::putOut(sf::Packet& packet){
  int typePrimitive; 
  TypeCharacter type;

  packet >> typePrimitive;

  type = (TypeCharacter)typePrimitive;

  if(this->type != type){
    setType(type);
  }

  EntityDrawableAnimated::putOut(packet);
}

Animation setCharacterAnimation(TypeCharacter type, TypeAnimationCharacter typeAnimation){
  CharacterTexture* characterTextures;

  switch(type){
    case girl:
      characterTextures = CharacterTexture::GIRL_TEXTURES;
      break;
    default:
      characterTextures = CharacterTexture::MAN_TEXTURES;
      break;
  }

  switch(typeAnimation){
    case TypeAnimationCharacter::dead:
      return Animation(characterTextures->getDeadTextures());
      break;
    case TypeAnimationCharacter::walk:
      return Animation(characterTextures->getWalkTextures());
      break;
    case TypeAnimationCharacter::run:
      return Animation(characterTextures->getRunTextures());
      break;
    case TypeAnimationCharacter::jump:
      return Animation(characterTextures->getJumpTextures());
      break;
    default:
      return Animation(characterTextures->getIdleTextures());
      break;
  }
}