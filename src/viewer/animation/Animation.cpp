#include "Animation.h"
#include <iostream>
#include <filesystem>

Animation::Animation() : animation(std::vector<TextureTool>()), delay(0){}

Animation::Animation(const std::vector<TextureTool*> &textures) : Animation(textures, 0){}

Animation::Animation(const std::vector<TextureTool*> &textures, unsigned int delay) : animation(std::vector<TextureTool>()), delay(delay){
  for(unsigned int i = 0; i < textures.size(); i++){
    this->addTexture(*textures[i]);
  }
  this->currentDelay = 0;
  this->currentFrame = 0;
}

void Animation::addTexture(const TextureTool &texture){
  this->animation.push_back(texture);
}

sf::Texture& Animation::getTextureDisplay(){
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
