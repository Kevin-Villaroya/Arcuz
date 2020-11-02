#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "../EntityDrawable.h"
#include "string"
#include "../../../viewer/animation/CharacterAnimation.h"

enum TypeCharacter{
  man,
  girl
};

class Character : public EntityDrawable{

private:
  const static CharacterAnimation* MAN;
  const static CharacterAnimation* GIRL;

  std::string name;

  CharacterAnimation* animation;

public:
  Character();
  Character(std::string name);
  Character(std::string name, TypeCharacter type);
};

#endif
