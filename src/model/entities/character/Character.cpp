#include "Character.h"
#include "../../../viewer/texture/CharacterTexture.h"

Character::Character() :
name("undefined"),
animationIdle(setCharacterAnimation(TypeCharacter::man, TypeAnimationCharacter::idle)){}

Character::Character(std::string name) : name(name){}

Character::Character(std::string name, TypeCharacter type) : name(name){}



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
