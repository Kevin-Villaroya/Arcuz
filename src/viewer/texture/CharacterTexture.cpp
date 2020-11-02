#include "CharacterTexture.h"
#include <string>
#include <experimental/filesystem>
#include <iostream>

CharacterTexture* CharacterTexture::MAN_TEXTURES = new CharacterTexture("man");
CharacterTexture* CharacterTexture::GIRL_TEXTURES = new CharacterTexture("girl");

CharacterTexture::CharacterTexture(std::string type) :
idle(std::vector<TextureTool*>()), walk(std::vector<TextureTool*>()), run(std::vector<TextureTool*>()), jump(std::vector<TextureTool*>()), dead(std::vector<TextureTool*>()){
  this->setWalkTextures(type);
  this->setDeadTextures(type);
  this->setIdleTextures(type);
  this->setJumpTextures(type);
  this->setRunTextures(type);
}

void CharacterTexture::setDeadTextures(std::string type){
  unsigned int count = 1;

  std::string path = "assets/character/" + type + "/Dead (" + std::to_string(count) + ").png";

  while(std::experimental::filesystem::exists(path)){
    this->dead.push_back(new TextureTool(path));
    path = "assets/character/" + type + "/Dead (" + std::to_string(count) + ").png";
    count++;
  }
}

void CharacterTexture::setIdleTextures(std::string type){
  unsigned int count = 1;

  std::string path = "assets/character/" + type + "/Idle (" + std::to_string(count) + ").png";

  while(std::experimental::filesystem::exists(path)){
    this->idle.push_back(new TextureTool(path));
    path = "assets/character/" + type + "/Idle (" + std::to_string(count) + ").png";
    count++;
  }
}

void CharacterTexture::setJumpTextures(std::string type){
  unsigned int count = 1;

  std::string path = "assets/character/" + type + "/Jump (" + std::to_string(count) + ").png";

  while(std::experimental::filesystem::exists(path)){
    this->jump.push_back(new TextureTool(path));
    path = "assets/character/" + type + "/Jump (" + std::to_string(count) + ").png";
    count++;
  }
}

void CharacterTexture::setRunTextures(std::string type){
  unsigned int count = 1;

  std::string path = "assets/character/" + type + "/Run (" + std::to_string(count) + ").png";

  while(std::experimental::filesystem::exists(path)){
    this->run.push_back(new TextureTool(path));
    path = "assets/character/" + type + "/Run (" + std::to_string(count) + ").png";
    count++;
  }
}

void CharacterTexture::setWalkTextures(std::string type){
  unsigned int count = 1;

  std::string path = "assets/character/" + type + "/Walk (" + std::to_string(count) + ").png";

  while(std::experimental::filesystem::exists(path)){
    this->walk.push_back(new TextureTool(path));
    path = "assets/character/" + type + "/Walk (" + std::to_string(count) + ").png";
    count++;
  }
}

std::vector<TextureTool*>& CharacterTexture::getDeadTextures(){
  return this->dead;
}

std::vector<TextureTool*>& CharacterTexture::getIdleTextures(){
  return this->idle;
}

std::vector<TextureTool*>& CharacterTexture::getJumpTextures(){
  return this->jump;
}

std::vector<TextureTool*>& CharacterTexture::getRunTextures(){
  return this->run;
}

std::vector<TextureTool*>& CharacterTexture::getWalkTextures(){
  return this->walk;
}

CharacterTexture::~CharacterTexture(){
  for(unsigned int i = 0; i < this->idle.size(); i++){
    delete this->idle[i];
  }
  for(unsigned int i = 0; i < this->walk.size(); i++){
    delete this->walk[i];
  }
  for(unsigned int i = 0; i < this->run.size(); i++){
    delete this->run[i];
  }
  for(unsigned int i = 0; i < this->jump.size(); i++){
    delete this->jump[i];
  }
  for(unsigned int i = 0; i < this->dead.size(); i++){
    delete this->dead[i];
  }
}
