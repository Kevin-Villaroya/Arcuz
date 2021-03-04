#ifndef __MENU_BUTTON_H__
#define __MENU_BUTTON_H__

#include "../view/View.h"
#include <SFML/Graphics.hpp>
#include <vector>

class MenuButton{
    private:
        static sf::Font DEFAULT_FONT;
        static void initFont();

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
        MenuButton(float originX, float originY, float sizeX, float sizeY, sf::Color colorCircle, sf::Font& font, const std::string& nameMenu, const std::string& nameButton);
        MenuButton(float originX, float originY, float sizeX, float sizeY, sf::Texture* texture, sf::Font& font, const std::string& nameMenu, const std::string& nameButton);
        
        std::vector<sf::Drawable*> getElementsToRender();
        bool clickOnButton(float x, float y);

        void update(const View* view);

        
};

#endif