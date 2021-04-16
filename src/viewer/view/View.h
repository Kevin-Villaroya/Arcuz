#ifndef __VIEW_H__
#define __VIEW_H__

#include <SFML/Graphics.hpp>
#include <vector>
#include "hud/Hud.h"
#include "../model/entities/EntityDrawable.h"
#include "../model/entities/entitiesAnimated/character/Character.h"

class View{
private:
  int height;
  int width;
  sf::RenderWindow& window;

  sf::View game;
  Hud hud;

public:
  View(sf::RenderWindow &window);
  View(sf::RenderWindow &window, int height, int width);
  void render(const Character &character, const std::vector<sf::Drawable*> &entities);
  void render(const std::vector<sf::Drawable*> &entities);

  void centerViewOn(const Character &character);
  void centerViewOn(float x, float y);

  const sf::Vector2f& getSize() const;
  const sf::Vector2u getSizeWindow() const;
  const sf::Vector2f& getCenter() const;
  void setSize(float x, float y);

  void click(float x, float y);
};

#endif
