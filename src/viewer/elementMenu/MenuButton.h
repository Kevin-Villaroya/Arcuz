#ifndef __MENU_BUTTON_H__
#define __MENU_BUTTON_H__

#include "../view/View.h"
#include <SFML/Graphics.hpp>
#include "../../tool/FontTool.h"
#include <vector>

class MenuButton{
    protected:
        sf::RectangleShape button;
        sf::RectangleShape line;
        sf::CircleShape circle;

        sf::Text nameMenu;
        sf::Text nameButton;

        float originX;
        float originY;

        float sizeX;
        float sizeY;

        void setScaleIcone(const View* view);
        void setScaleText(const View* view);
        void setPositionNameButton();
    
    public:
        MenuButton();
        MenuButton(float originX, float originY, float sizeX, float sizeY, sf::Color colorCircle, const sf::Font& font, const std::string& nameMenu, const std::string& nameButton);
        MenuButton(float originX, float originY, float sizeX, float sizeY, sf::Texture* texture, const sf::Font& font, const std::string& nameMenu, const std::string& nameButton);
        
        virtual std::vector<sf::Drawable*> getElementsToRender();
        virtual bool clickOnButton(float x, float y);

        virtual void update(const View* view);
};

#endif