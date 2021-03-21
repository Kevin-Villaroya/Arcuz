#ifndef __MENU_BUTTON_SELECT_H__
#define __MENU_BUTTON_SELECT_H__

#include "../view/View.h"
#include "../../tool/FontTool.h"
#include "MenuButton.h"
#include <SFML/Graphics.hpp>
#include <vector>

class  MenuButtonSelect : public MenuButton{
    private:
        std::vector<std::string> options;

        sf::Font font;
        unsigned int currentOption;

    public:
        MenuButtonSelect();
        MenuButtonSelect(float originX, float originY, float sizeX, float sizeY, sf::Color colorCircle, const sf::Font& font, const std::string& nameMenu, const std::string& nameButton);
        MenuButtonSelect(float originX, float originY, float sizeX, float sizeY, sf::Texture* texture, const sf::Font& font, const std::string& nameMenu, const std::string& nameButton);

        void addOption(const std::string &option);

        std::vector<sf::Drawable*> getElementsToRender() override;
        bool clickOnButton(float x, float y) override;
        bool clickOnOption(float x, float y);
        void changeOption();

        std::string& getCurrentOption();

        void update(const View* view) override;
};

#endif