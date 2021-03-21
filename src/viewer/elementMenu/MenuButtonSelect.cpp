#include "MenuButtonSelect.h"
#include <iostream>

MenuButtonSelect::MenuButtonSelect() : MenuButtonSelect(0,0,0,0,sf::Color::Black, FontTool::REGULAR_FONT ,"" ,""){}

MenuButtonSelect::MenuButtonSelect(float originX, float originY, float sizeX, float sizeY, sf::Texture* texture, const sf::Font& font, const std::string& nameMenu, const std::string& nameButton):
MenuButtonSelect(originX, originY, sizeX, sizeY, sf::Color::White, font, nameMenu, nameButton){
    this->circle.setTexture(texture);
    this->circle.setTextureRect(sf::IntRect(-100, 0, 560, 560));
}

MenuButtonSelect::MenuButtonSelect(float originX, float originY, float sizeX, float sizeY, sf::Color colorCircle, const sf::Font& font, const std::string& nameMenu, const std::string& nameButton):
MenuButton(originX, originY, sizeX, sizeY, sf::Color::White, font, nameMenu, nameButton){
    this->currentOption = 0;
}

void MenuButtonSelect::addOption(const std::string &option){
    options.push_back(option);
}

std::vector<sf::Drawable*> MenuButtonSelect::getElementsToRender(){
    std::vector<sf::Drawable*> allDraws;

    allDraws = MenuButton::getElementsToRender();

    return allDraws;
}

bool MenuButtonSelect::clickOnButton(float posX, float posY){
    sf::Vector2f position = this->button.getPosition();
    sf::Vector2f size = this->button.getSize();

    if(posX > position.x && posX < position.x + size.x && posY > position.y && posY < position.y + size.y){
        this->changeOption();
        return true;
    }else{
        return false;
    }
}

void MenuButtonSelect::changeOption(){
    if(this->options.size() > this->currentOption + 1){
        this->currentOption++;
    }else{
        this->currentOption = 0;
    }

    this->nameButton.setString(this->options[this->currentOption]);
}

std::string& MenuButtonSelect::getCurrentOption(){
    return this->options[this->currentOption];
}

void MenuButtonSelect::update(const View* view){
    MenuButton::update(view);
}