#include "Animation.h"
#include <iostream>
#include <filesystem>

Animation::Animation() : animation(std::vector<sf::Sprite>()), delay(0){}

Animation::Animation(std::vector<sf::Sprite> animation) : animation(animation), delay(0){
  this->currentDelay = 0;
  this->currentFrame = 0;
}

Animation::Animation(std::vector<sf::Sprite> animation, unsigned int delay) : animation(animation), delay(delay){
  this->currentDelay = 0;
  this->currentFrame = 0;
}

void Animation::addSprite(sf::Sprite sprite){
  this->animation.push_back(sprite);
}

sf::Sprite Animation::play(){
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
  if(this->currentFrame <= animation.size()){
    this->currentFrame = 0;
  }
}
