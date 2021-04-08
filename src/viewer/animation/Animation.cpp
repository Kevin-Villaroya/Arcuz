#include "Animation.h"
#include <iostream>
#include <experimental/filesystem>

Animation::Animation() : animation(std::vector<TextureTool*>()), delay(0){}

Animation::Animation(const std::vector<TextureTool*> &textures) : Animation(textures, 0, "Default"){}

Animation::Animation(const std::vector<TextureTool*> &textures, unsigned int delay, std::string name) : animation(std::vector<TextureTool*>()), delay(delay), name(name){
  for(unsigned int i = 0; i < textures.size(); i++){
    this->addTexture(textures[i]);
  }
  this->currentDelay = 0;
  this->currentFrame = 0;
}

void Animation::addTexture(TextureTool* texture){
  this->animation.push_back(texture);
}

const sf::Texture* Animation::getTextureDisplay(){
  if(this->currentDelay < this->delay){
    this->currentDelay++;
    return this->animation[this->currentFrame];
  }else{
    unsigned int hasToDisplay = this->currentFrame;
    this->currentDelay = 0;
    this->increaseFrame();
    return this->animation[hasToDisplay];
  }
}

unsigned int Animation::getCurrentFrame(){
  return this->currentFrame;
}

unsigned int Animation::getDelay(){
  return this->delay;
}

void Animation::setDelay(unsigned int delay){
  this->delay = delay;
}

const std::string& Animation::getName(){
  return this->name;
}

void Animation::setName(std::string name){
  this->name = name;
}

void Animation::reset(){
  this->currentFrame = 0;
  this->currentDelay = 0;
}

void Animation::increaseFrame(){
  this->currentFrame++;
  if(this->currentFrame >= animation.size()){
    this->currentFrame = 0;
  }
}

bool Animation::isLastFrame(){
  return this->currentFrame == animation.size();
}
