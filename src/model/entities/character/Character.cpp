#include "Character.h"
#include "../../../viewer/texture/CharacterTexture.h"
#include <iostream>
#include <string>

const float Character::SCALE = 0.5;

Character::Character() : Character("default"){}

Character::Character(std::string name) : Character(name, TypeCharacter::man){}

Character::Character(std::string name, TypeCharacter type) :
name(name),
animationIdle(setCharacterAnimation(type, TypeAnimationCharacter::idle)),
animationWalk(setCharacterAnimation(type, TypeAnimationCharacter::walk)),
animationRun(setCharacterAnimation(type, TypeAnimationCharacter::run)),
animationJump(setCharacterAnimation(type, TypeAnimationCharacter::jump)),
animationDead(setCharacterAnimation(type, TypeAnimationCharacter::dead))
{ this->currentAnimation = &this->animationIdle; this->speed = 0; this->direction = Direction::right; this->applySprite();}

void Character::update(){
  this->watchDirection();
  this->moveCharacter();
  this->applySprite();
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
  }
  this->setSpeedWhenWalk();
}

void Character::run(Direction newDirection){
  if(this->currentAnimation == &this->animationRun && this->direction == newDirection){
  }else{
    this->currentAnimation->reset();
    this->direction = newDirection;
    this->currentAnimation = &this->animationRun;
  }
  this->setSpeedWhenRun();
}

void Character::stop(){
  if(this->currentAnimation == &this->animationIdle){
  }else{
    this->currentAnimation = &this->animationIdle;
  }
  this->setSpeedWhenStopped();
}

void Character::jump(){
  if(this->currentAnimation == &this->animationJump){
  }else{
    this->currentAnimation->reset();
    this->currentAnimation = &this->animationJump;
  }
  this->setSpeedWhenWalk();
}

void Character::die(){
  if(this->currentAnimation == &this->animationDead){
  }else{
    this->currentAnimation->reset();
    this->currentAnimation = &this->animationDead;
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

int Character::getId(){
  return this->id;
}

int Character::getSpeed(){
  return this->speed;
}

std::string& Character::getName(){
  return this->name;
}

void Character::applySprite(){
  this->setTexture(this->currentAnimation->getTextureDisplay());
  this->setScale(Character::SCALE, Character::SCALE);
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
    case dead:
      return Animation(characterTextures->getDeadTextures());
      break;
    case walk:
      return Animation(characterTextures->getWalkTextures());
      break;
    case run:
      return Animation(characterTextures->getRunTextures());
      break;
    case jump:
      return Animation(characterTextures->getJumpTextures());
      break;
    default:
      return Animation(characterTextures->getIdleTextures());
      break;
  }
}
