#ifndef __MENU_TEXT_H__
#define __MENU_TEXT_H__

#include "../view/View.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class MenuText{
    private:
        float originX;
        float originY;

        float sizeX;
        float sizeY;

        sf::Text text;
        sf::Text value;
        sf::RectangleShape square;

        void setScaleText(const View* view);
        void updatePosition();

        bool changingValue;
        bool enabled;
    public:
        MenuText();
        MenuText(float originX, float originY, float sizeX, float sizeY, const std::string& nameButton, const std::string& defaultValue);

        std::vector<sf::Drawable*> getElementsToRender();
        bool clickOnButton(float x, float y);

        void update(const View* view);

        bool isEnabled();
        void disable();
        void enable();

        bool isChangingValue();
        void setChangingValue(bool value);

        void addLetterToValue(char letter);

        std::string getValue();
        void setValue(const std::string& value);
};

#endif