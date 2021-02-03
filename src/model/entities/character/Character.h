#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "../EntityDrawable.h"
#include <SFML/Network/Packet.hpp>
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

  TypeCharacter type;

  Animation animationIdle;
  Animation animationWalk;
  Animation animationRun;
  Animation animationJump;
  Animation animationDead;

  Animation* currentAnimation;
  TypeAnimationCharacter action;

  int speed;
  int id;

  void applySprite();
  void playAnimation();
public:
  Character();
  Character(std::string name);
  Character(std::string name, TypeCharacter type);

  bool update() override;
  void noUpdate() override;

  void moveCharacter();

  void walk(Direction direction);
  void run(Direction direction);
  void stop();
  void jump();
  void die();

  void setSpeedWhenRun();
  void setSpeedWhenWalk();
  void setSpeedWhenStopped();
  void setId(int id);

  int getId() const;
  int getSpeed() const;

  const TypeAnimationCharacter getAnimation() const;
  Animation* getAnimation(TypeAnimationCharacter typeAnimation);

  const int getType() const;

  void putIn(sf::Packet& packet) const override;
  void putOut(sf::Packet& packet) override;
};

Animation setCharacterAnimation(TypeCharacter type, TypeAnimationCharacter typeAnimation);

#endif
