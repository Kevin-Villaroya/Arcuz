#include "Character.h"
#include "../../../viewer/texture/CharacterTexture.h"
#include <iostream>

Character::Character() : Character("default"){}

Character::Character(std::string name) : Character(name, TypeCharacter::man){}

Character::Character(std::string name, TypeCharacter type) :
name(name),
animationIdle(setCharacterAnimation(type, TypeAnimationCharacter::idle)),
animationWalk(setCharacterAnimation(type, TypeAnimationCharacter::walk)),
animationRun(setCharacterAnimation(type, TypeAnimationCharacter::run)),
animationJump(setCharacterAnimation(type, TypeAnimationCharacter::jump)),
animationDead(setCharacterAnimation(type, TypeAnimationCharacter::dead))
{ this->currentAnimation = &this->animationIdle; this->speed = 0;}

void Character::update(){
  this->watchDirection();
  this->moveCharacter();
  this->setTexture(this->currentAnimation->getTextureDisplay());
}

void Character::moveCharacter(){
  this->move(this->speed, this->speed);
}

void Character::walk(Direction newDirection){
  if(this->currentAnimation == &this->animationWalk && this->direction == newDirection){
  }else{
    this->currentAnimation->reset();
    this->direction = newDirection;
    this->currentAnimation = &this->animationWalk;
  }
  this->speed = 1;
}

void Character::run(Direction newDirection){
  if(this->currentAnimation == &this->animationRun && this->direction == newDirection){
  }else{
    this->currentAnimation->reset();
    this->direction = newDirection;
    this->currentAnimation = &this->animationRun;
  }
  this->speed = 2;
}

void Character::stop(){
  if(this->currentAnimation == &this->animationIdle){
  }else{
    this->currentAnimation->reset();
    this->currentAnimation = &this->animationIdle;
  }
  this->speed = 0;
}

void Character::jump(){
  if(this->currentAnimation == &this->animationJump){
  }else{
    this->currentAnimation->reset();
    this->currentAnimation = &this->animationJump;
  }
  this->speed = 1;
}

void Character::die(){
  if(this->currentAnimation == &this->animationDead){
  }else{
    this->currentAnimation->reset();
    this->currentAnimation = &this->animationDead;
  }
  this->speed = 0;
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
