#include "Character.h"
#include "../../../viewer/texture/CharacterTexture.h"
#include <iostream>
#include <string>

const float Character::SCALE = 0.5;

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

const TypeAnimationCharacter Character::getAnimation() const{
  return this->action;
}

const unsigned int Character::getCurrentFrame() const{
  return this->currentAnimation->getCurrentFrame();
}

const int Character::getType() const{
  return this->type;
}

void Character::applySprite(){
  this->setTexture(this->currentAnimation->getTextureDisplay());
  this->setScale(Character::SCALE, Character::SCALE);
}

void Character::putIn(sf::Packet& packet) const{
  EntityDrawable::putIn(packet);

  packet << this->getType();
  packet << this->getAnimation();
  packet << this->getCurrentFrame();
}

void Character::putOut(sf::Packet& packet){
  EntityDrawable::putOut(packet);

  int animationPrimitive; 
  TypeAnimationCharacter animation;

  unsigned int currentFrame;

  int typePrimitive; 
  TypeCharacter type;

  packet >> typePrimitive;
  packet >> animationPrimitive;
  packet >> currentFrame;

  type = (TypeCharacter)typePrimitive;
  animation = (TypeAnimationCharacter)animationPrimitive;

  this->setTexture(*getTexture(type, animation, currentFrame));
}

const TextureTool* Character::getTexture(TypeCharacter type, TypeAnimationCharacter animation, unsigned int currentFrame){
  CharacterTexture* characterTextures;

  switch(type){
    case girl:
      characterTextures = CharacterTexture::GIRL_TEXTURES;
      break;
    default:
      characterTextures = CharacterTexture::MAN_TEXTURES;
      break;
  }

  switch(animation){
    case TypeAnimationCharacter::dead:
      return characterTextures->getDeadTextures()[currentFrame];
      break;
    case TypeAnimationCharacter::walk:
      return characterTextures->getWalkTextures()[currentFrame];
      break;
    case TypeAnimationCharacter::run:
      return characterTextures->getRunTextures()[currentFrame];
      break;
    case TypeAnimationCharacter::jump:
      return characterTextures->getJumpTextures()[currentFrame];
      break;
    default:
      return characterTextures->getIdleTextures()[currentFrame];
      break;
  }
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
