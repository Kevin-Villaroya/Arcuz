#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "../EntityDrawable.h"
#include "string"
#include "../../../viewer/animation/Animation.h"

enum TypeCharacter{
  man,
  girl
};

enum TypeAnimationCharacter{
  idle,
  walk,
  run,
  jump,
  dead
};

class Character : public EntityDrawable{

private:
  std::string name;

  Animation animationIdle;
  Animation animationWalk;
  Animation animationRun;
  Animation animationJump;
  Animation animationDead;


public:
  Character();
  Character(std::string name);
  Character(std::string name, TypeCharacter type);

  void playAnimation();

};

Animation setCharacterAnimation(TypeCharacter type, TypeAnimationCharacter typeAnimation);

#endif
