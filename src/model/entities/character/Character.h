#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "../EntityDrawable.h"
#include <string>
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
  const static float SCALE;

  std::string name;

  Animation animationIdle;
  Animation animationWalk;
  Animation animationRun;
  Animation animationJump;
  Animation animationDead;

  Animation* currentAnimation;

  int speed;

  void applySprite();
  void playAnimation();
public:
  Character();
  Character(std::string name);
  Character(std::string name, TypeCharacter type);

  void update() override;
  void moveCharacter();

  void walk(Direction direction);
  void run(Direction direction);
  void stop();
  void jump();
  void die();

  void setSpeedWhenRun();
  void setSpeedWhenWalk();
  void setSpeedWhenStopped();

  int getSpeed();
};

Animation setCharacterAnimation(TypeCharacter type, TypeAnimationCharacter typeAnimation);

#endif
