#include "Character.h"

const CharacterAnimation* MAN = new CharacterAnimation("man");
const CharacterAnimation* GIRL = new CharacterAnimation("girl");

Character::Character(){
  this->name = "undefined";
}

Character::Character(std::string name) : name(name){}
