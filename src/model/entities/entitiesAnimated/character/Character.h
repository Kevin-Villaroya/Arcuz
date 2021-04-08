#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "entitiesAnimated/EntityDrawableAnimated.h"
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

class Character : public EntityDrawableAnimated{

private:
  const static float SCALE_BOY;
  const static float SCALE_GIRL;

  TypeCharacter type;

  TypeAnimationCharacter action;

  int speed;
  int id;

  float getEntityScale() override;

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

  const int getType() const;
  TypeCharacter getType(std::string type) const;
  std::string getNameAnimationOfType(TypeAnimationCharacter type) const;

  void setType(std::string nameType);
  void setType(TypeCharacter Type);

  void putIn(sf::Packet& packet) const override;
  void putOut(sf::Packet& packet) override;
};

Animation setCharacterAnimation(TypeCharacter type, TypeAnimationCharacter typeAnimation);

#endif
