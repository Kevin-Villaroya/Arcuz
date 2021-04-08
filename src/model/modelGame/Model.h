#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include <string>

#include "../viewer/view/View.h"
#include "entities/EntityDrawable.h"
#include "map/Map.h"
#include "entities/entitiesAnimated/character/Character.h"

class Model{
private:
  View view;
  Map map;

  Character* mainCharacter;

  bool modelChanged;
  std::vector<EntityDrawable*> entitiesNeedUpdate; //optimisation
  std::vector<sf::Text*> nameEntities;

  std::vector<EntityDrawable*> entities; //all entities in the game (without character)

  void addEntityName(const std::string& name);
  void updateEntitiesName();
public:
  Model(View &view);

  void update();
  void render();
  Character* getMainCharacter();

  bool addCharacter(Character* character);
  void addEntity(EntityDrawable* entity);
  const std::vector<EntityDrawable*>& getEntities();
  void setEntities(std::vector<EntityDrawable*>& entities);

  bool existEntity(const std::string& name);
  bool existEntity(const int uid);
  EntityDrawable* getEntity(const int uid);

  void moveCharacter();
  bool collisionWithABlockedTile(float x, float y);

  void setNameCharacter(const std::string& name);

  size_t quantityOfEntities();

  bool updateNeededForEntities();
  std::vector<EntityDrawable*>& getEntitiesNeedUpdate();

  void removeAllEntities();
  void removeEntitie(EntityDrawable& entitie);//Call destructor of EntityDrawable
  void removeEntitie(const std::string& name);//Call destructor of EntityDrawable

  ~Model();
};

#endif
