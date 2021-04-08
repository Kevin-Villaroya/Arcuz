#include "EntityDrawableAnimated.h"
#include <iostream>

EntityDrawableAnimated::EntityDrawableAnimated() : EntityDrawable(){}

void EntityDrawableAnimated::applySprite(){
    this->setTexture(*this->currentAnimation->getTextureDisplay());
    this->setScale(this->getEntityScale(), this->getEntityScale());
}

void EntityDrawableAnimated::setDelayOfAnimation(unsigned int frames){
    for(unsigned int i = 0; i < this->animations.size(); i++){
        this->animations[i].setDelay(frames);
    }
}

void EntityDrawableAnimated::addAnimation(Animation animation, std::string typeAnimation){
    this->animations.push_back(animation);
    this->typeAnimations.push_back(typeAnimation);
}

void EntityDrawableAnimated::clearAnimations(){
    this->animations.clear();
    this->typeAnimations.clear();
}

void EntityDrawableAnimated::playAnimation(std::string nameAnimation){
    bool found = false;

    for(unsigned int i = 0; i < this->typeAnimations.size() && !found; i++){
        if(this->typeAnimations[i].compare(nameAnimation) == 0){
            this->currentAnimation = &this->animations[i];
            this->idCurrentAnimation = i;
            found = true;
        }
    }
    this->applySprite();
}

bool EntityDrawableAnimated::update(){
    this->applySprite();
    return true;
}

const std::string& EntityDrawableAnimated::getNameAnimation() const{
  for(unsigned int i = 0; i < this->animations.size(); i++){
        if(&this->animations[i] == this->currentAnimation){
            return this->typeAnimations[i];
        }
    }
    return NULL;
}

Animation* EntityDrawableAnimated::getAnimation(std::string nameAnimation){
    for(unsigned int i = 0; i < this->typeAnimations.size(); i++){
        if(this->typeAnimations[i].compare(nameAnimation) == 0){
            return &this->animations[i];
        }
    }
  return NULL;
}

unsigned int EntityDrawableAnimated::convertNameAnimationToNumber(const std::string& name){
    for(unsigned int i = 0; i < this->animations.size(); i++){
        if(this->typeAnimations[i].compare(name) == 0){
            return i;
        }
    }   
    return 0;
}

std::string& EntityDrawableAnimated::convertNumberToNameAnimation(unsigned int number){
    return this->typeAnimations[number];
}

void EntityDrawableAnimated::putIn(sf::Packet& packet) const{
    EntityDrawable::putIn(packet);

    packet << this->idCurrentAnimation;
    packet << (uint32_t)this->direction;
}

void EntityDrawableAnimated::putOut(sf::Packet& packet){
    EntityDrawable::putOut(packet);

    unsigned int idAnimation; 
    uint32_t direction;

    packet >> idAnimation;
    packet >> direction;

    this->direction = (Direction)direction;
    this->watchDirection();

    this->playAnimation(this->convertNumberToNameAnimation(idAnimation));
}