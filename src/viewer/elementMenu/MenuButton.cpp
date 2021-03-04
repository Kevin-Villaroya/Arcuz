#include "MenuButton.h"
#include <iostream>

sf::Font MenuButton::DEFAULT_FONT;

void MenuButton::initFont(){
    MenuButton::DEFAULT_FONT.loadFromFile("assets/font/regular.ttf");
}

MenuButton::MenuButton() : MenuButton(0,0,0,0,sf::Color::Black, MenuButton::DEFAULT_FONT ,"" ,""){}

MenuButton::MenuButton(float originX, float originY, float sizeX, float sizeY, sf::Texture* texture, sf::Font& font, const std::string& nameMenu, const std::string& nameButton) : 
MenuButton(originX, originY, sizeX, sizeY, sf::Color::White, font, nameMenu, nameButton){
    this->circle.setTexture(texture);
    this->circle.setTextureRect(sf::IntRect(-100, 0, 560, 560));
}

MenuButton::MenuButton(float originX, float originY, float sizeX, float sizeY, sf::Color colorCircle, sf::Font& font, const std::string& nameMenu, const std::string& nameButton){
    this->circle = sf::CircleShape(sizeX * 0.1);
    this->circle.setPosition(originX + sizeX * 0.1, originY + sizeY * 0.1);
    this->circle.setFillColor(colorCircle);

    this->line = sf::RectangleShape(sf::Vector2f(sizeX * 0.7, 5));
    this->line.setPosition(sizeX * 0.2 + originX + sizeX * 0.1, sizeX * 0.1 + originY + sizeY * 0.1);
    this->line.setFillColor(sf::Color::Black);

    this->button = sf::RectangleShape(sf::Vector2f(sizeX * 0.5, sizeY - (sizeX * 0.1 + sizeY * 0.1 + 10)));
    this->button.setPosition(sizeX * 0.2 + originX + sizeX * 0.1 + 10, sizeX * 0.1 + originY + sizeY * 0.1 + 10);
    this->button.setFillColor(sf::Color::Black);

    this->nameMenu.setFont(font);
    this->nameMenu.setFillColor(sf::Color::Black);
    this->nameMenu.setString(nameMenu);
    this->nameMenu.setPosition(sizeX * 0.2 + originX + sizeX * 0.1 + 5, sizeX * 0.1 + originY + sizeY * 0.1 - this->nameMenu.getCharacterSize() - 5);

    this->nameButton.setFont(font);
    this->nameButton.setFillColor(sf::Color::White);
    this->nameButton.setString(nameButton);
    this->nameButton.setCharacterSize((sizeY - (sizeX * 0.1 + sizeY * 0.1 + 10)) / 2.5);
    this->nameButton.setPosition(sizeX * 0.2 + originX + sizeX * 0.1 + 10, sizeX * 0.1 + originY + sizeY * 0.1 + 10);
}

std::vector<sf::Drawable*> MenuButton::getElementsToRender(){
    std::vector<sf::Drawable*> allDraws;

    allDraws.push_back(&this->circle);
    allDraws.push_back(&this->line);
    allDraws.push_back(&this->button);
    allDraws.push_back(&this->nameMenu);
    allDraws.push_back(&this->nameButton);

    return allDraws;
}

bool MenuButton::clickOnButton(float posX, float posY){
    sf::Vector2f position = this->button.getPosition();
    sf::Vector2f size = this->button.getSize();

    if(posX > position.x && posX < position.x + size.x && posY > position.y && posY < position.y + size.y){
        return true;
    }else{
        return false;
    }
}

void MenuButton::setPositionNameButton(){
    sf::Vector2f sizeScreen = this->button.getSize();
    sf::Vector2f posScreen = this->button.getPosition();

    float sizeName = this->nameButton.getGlobalBounds().width;
    this->nameButton.setPosition(posScreen.x + sizeScreen.x / 2 - sizeName / 2, posScreen.y + sizeScreen.y /2 - this->nameButton.getCharacterSize() / 1.5);
}
