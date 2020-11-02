#include "CharacterAnimation.h"
#include <string>
#include <experimental/filesystem>
#include "../../tool/SpriteTool.h"
#include <iostream>

CharacterAnimation::CharacterAnimation(std::string type) : dead(Animation()),  idle(Animation()),  walk(Animation()),  run(Animation()),  jump(Animation()){

  this->setWalkAnimation(type);
  this->setDeadAnimation(type);
  this->setIdleAnimation(type);
  this->setJumpAnimation(type);
  this->setRunAnimation(type);

}

void CharacterAnimation::setDeadAnimation(std::string type){
  unsigned int count = 1;

  std::string path = "assets/character/" + type + "/Dead (" + std::to_string(count) + ").png";

  while(std::experimental::filesystem::exists(path)){
    this->dead.addSprite(SpriteTool(path));
    path = "assets/character/" + type + "/Dead (" + std::to_string(count) + ").png";
    count++;
  }
}

void CharacterAnimation::setIdleAnimation(std::string type){
  unsigned int count = 1;

  std::string path = "assets/character/" + type + "/Idle (" + std::to_string(count) + ").png";

  while(std::experimental::filesystem::exists(path)){
    this->idle.addSprite(SpriteTool(path));
    path = "assets/character/" + type + "/Idle (" + std::to_string(count) + ").png";
    count++;
  }
}

void CharacterAnimation::setJumpAnimation(std::string type){
  unsigned int count = 1;

  std::string path = "assets/character/" + type + "/Jump (" + std::to_string(count) + ").png";

  while(std::experimental::filesystem::exists(path)){
    this->jump.addSprite(SpriteTool(path));
    path = "assets/character/" + type + "/Jump (" + std::to_string(count) + ").png";
    count++;
  }
}

void CharacterAnimation::setRunAnimation(std::string type){
  unsigned int count = 1;

  std::string path = "assets/character/" + type + "/Run (" + std::to_string(count) + ").png";

  while(std::experimental::filesystem::exists(path)){
    this->run.addSprite(SpriteTool(path));
    path = "assets/character/" + type + "/Run (" + std::to_string(count) + ").png";
    count++;
  }
}

void CharacterAnimation::setWalkAnimation(std::string type){
  unsigned int count = 1;

  std::string path = "assets/character/" + type + "/Walk (" + std::to_string(count) + ").png";

  while(std::experimental::filesystem::exists(path)){
    this->walk.addSprite(SpriteTool(path));
    path = "assets/character/" + type + "/Walk (" + std::to_string(count) + ").png";
    count++;
  }
}
