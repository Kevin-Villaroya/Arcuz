#include "Character.h"
#include "../../../viewer/texture/CharacterTexture.h"
#include <iostream>
#include <string>

const float Character::SCALE_GIRL = 0.4;
const float Character::SCALE_BOY = 0.5;

Character::Character() : Character("default"){}

Character::Character(std::string name) : Character(name, TypeCharacter::man){}

Character::Character(std::string name, TypeCharacter type) :
type(type),
animationIdle(setCharacterAnimation(type, TypeAnimationCharacter::idle)),
animationWalk(setCharacterAnimation(type, TypeAnimationCharacter::walk)),
animationRun(setCharacterAnimation(type, TypeAnimationCharacter::run)),
animationJump(setCharacterAnimation(type, TypeAnimationCharacter::jump)),
animationDead(setCharacterAnimation(type, TypeAnimationCharacter::dead)){
  this->name = name;
  this->typeEntity = TypeEntity::character; 
  this->currentAnimation = &this->animationIdle;
  this->action = TypeAnimationCharacter::idle;
  this->speed = 0; this->direction = Direction::right;
  this->applySprite();
}

bool Character::update(){
  this->watchDirection();
  this->moveCharacter();
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
  if(this->currentAnimation == &this->animationWalk && this->direction == newDirection){
  }else{
    this->currentAnimation->reset();
    this->direction = newDirection;
    this->currentAnimation = &this->animationWalk;
    this->action = TypeAnimationCharacter::walk;
  }
  this->setSpeedWhenWalk();
}

void Character::run(Direction newDirection){
  if(this->currentAnimation == &this->animationRun && this->direction == newDirection){
  }else{
    this->currentAnimation->reset();
    this->direction = newDirection;
    this->currentAnimation = &this->animationRun;
    this->action = TypeAnimationCharacter::run;
  }
  this->setSpeedWhenRun();
}

void Character::stop(){
  if(this->currentAnimation == &this->animationIdle){
  }else{
    this->currentAnimation = &this->animationIdle;
    this->action = TypeAnimationCharacter::idle;
  }
  this->setSpeedWhenStopped();
}

void Character::jump(){
  if(this->currentAnimation == &this->animationJump){
  }else{
    this->currentAnimation->reset();
    this->currentAnimation = &this->animationJump;
    this->action = TypeAnimationCharacter::jump;
  }
  this->setSpeedWhenWalk();
}

void Character::die(){
  if(this->currentAnimation == &this->animationDead){
  }else{
    this->currentAnimation->reset();
    this->currentAnimation = &this->animationDead;
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

void Character::setDelayOfAnimation(unsigned int frames){
  this->animationIdle.setDelay(frames);
  this->animationJump.setDelay(frames);
  this->animationWalk.setDelay(frames);
  this->animationRun.setDelay(frames);
  this->animationDead.setDelay(frames);
}

const TypeAnimationCharacter Character::getAnimation() const{
  return this->action;
}

Animation* Character::getAnimation(TypeAnimationCharacter typeAnimation){
  switch(typeAnimation){
    case TypeAnimationCharacter::dead:
      return &this->animationDead;
      break;
    case TypeAnimationCharacter::walk:
      return &this->animationWalk;
      break;
    case TypeAnimationCharacter::run:
      return &this->animationRun;
      break;
    case TypeAnimationCharacter::jump:
      return &this->animationJump;
      break;
    default:
      return &this->animationIdle;
      break;
  }
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

void Character::setType(std::string nameType){
  TypeCharacter type = this->getType(nameType);
  this->setType(type);
}

void Character::setType(TypeCharacter type){
  this->type = type;

  this->animationIdle = setCharacterAnimation(type, TypeAnimationCharacter::idle);
  this->animationWalk = setCharacterAnimation(type, TypeAnimationCharacter::walk);
  this->animationRun = setCharacterAnimation(type, TypeAnimationCharacter::run);
  this->animationJump = setCharacterAnimation(type, TypeAnimationCharacter::jump);
  this->animationDead = setCharacterAnimation(type, TypeAnimationCharacter::dead);
}

void Character::applySprite(){
  this->setTexture(this->currentAnimation->getTextureDisplay());

  if(this->type == TypeCharacter::girl){
    this->setScale(Character::SCALE_GIRL, Character::SCALE_GIRL);
  }else if(this->type == TypeCharacter::man){
    this->setScale(Character::SCALE_BOY, Character::SCALE_BOY);
  }
}

void Character::putIn(sf::Packet& packet) const{
  EntityDrawable::putIn(packet);

  packet << this->getType();
  packet << this->getAnimation();
  packet << (uint32_t)this->direction;
}

void Character::putOut(sf::Packet& packet){
  EntityDrawable::putOut(packet);

  int animationPrimitive; 
  TypeAnimationCharacter animation;
  uint32_t direction;

  int typePrimitive; 
  TypeCharacter type;

  packet >> typePrimitive;
  packet >> animationPrimitive;
  packet >> direction;

  this->direction = (Direction)direction;
  type = (TypeCharacter)typePrimitive;
  animation = (TypeAnimationCharacter)animationPrimitive;

  if(this->type != type){
    setType(type);
    setCharacterAnimation(type, animation);
  }

  this->currentAnimation = this->getAnimation(animation);
  this->watchDirection();
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
