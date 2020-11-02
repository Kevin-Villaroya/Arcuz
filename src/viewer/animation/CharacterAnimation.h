#ifndef  __CHARACTER_ANIMATION_H__
#define __CHARACTER_ANIMATION_H__

#include "Animation.h"

class CharacterAnimation{
private:

  Animation dead;
  Animation idle;
  Animation jump;
  Animation run;
  Animation walk;

  void setDeadAnimation(std::string type);
  void setIdleAnimation(std::string type);
  void setJumpAnimation(std::string type);
  void setRunAnimation(std::string type);
  void setWalkAnimation(std::string type);
public:
  CharacterAnimation(std::string type);
};

#endif
