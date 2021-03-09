#include "MenuText.h"
#include "../tool/FontTool.h"
#include <iostream>

MenuText::MenuText() : MenuText(0,0,0,0,"","default:"){}

MenuText::MenuText(float originX, float originY, float sizeX, float sizeY, const std::string& nameButton, const std::string& defaultValue){
    this->originX = originX; this->originY = originY; this->sizeY = sizeY; this->sizeX = sizeX;

    this->enabled = true;

    this->text.setFont(FontTool::REGULAR_FONT);
    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(this->text.getCharacterSize() * 2);
    this->text.setString(nameButton);

    this->value.setFont(FontTool::REGULAR_FONT);
    this->value.setFillColor(sf::Color::Black);
    this->value.setCharacterSize(this->value.getCharacterSize() * 2);
    this->value.setString(defaultValue);

    this->square = sf::RectangleShape(sf::Vector2f(sizeX - (this->text.getGlobalBounds().width) + 10, sizeY));
    this->square.setFillColor(sf::Color::White);
    this->square.setOutlineThickness(3);
    this->square.setOutlineColor(sf::Color::Black);
}

std::vector<sf::Drawable*> MenuText::getElementsToRender(){
    std::vector<sf::Drawable*> allDraws;

    allDraws.push_back(&this->square);
    allDraws.push_back(&this->text);
    allDraws.push_back(&this->value);

    return allDraws;
}

bool MenuText::clickOnButton(float posX, float posY){
    sf::Vector2f position = this->square.getPosition();
    sf::Vector2f size = this->square.getSize();

    if(posX > position.x && posX < position.x + size.x && posY > position.y && posY < position.y + size.y){
        return true;
    }else{
        return false;
    }
}

void MenuText::update(const View* view){
    this->setScaleText(view);
    this->updatePosition();
}

bool MenuText::isEnabled(){
    return this->enabled;
}

void MenuText::disable(){
    this->enabled = false;
    this->square.setFillColor(sf::Color(105,105,105));
}

void MenuText::enable(){
    this->enabled = true;
    this->square.setFillColor(sf::Color::White);
}

bool MenuText::isChangingValue(){
    return changingValue;
}

void MenuText::setChangingValue(bool value){
    this->changingValue = value;
    if(value){
        this->square.setOutlineColor(sf::Color::Blue);
    }else{
        this->square.setOutlineColor(sf::Color::Black);
    }
}

void MenuText::setScaleText(const View* view){
    sf::Vector2u sizeWindow = view->getSizeWindow();
    sf::Vector2f sizeView = view->getSize();

    if(sizeWindow.x > sizeView.x){
        this->text.setScale(sizeView.x / sizeWindow.x, 1);
        this->value.setScale(sizeView.x / sizeWindow.x, 1);
    }
}

void MenuText::updatePosition(){
    unsigned int posXText = this->originX;
    unsigned int posXSquare = posXText + this->text.getGlobalBounds().width + 10;
    unsigned int posXValue = posXSquare + this->square.getSize().x / 2 - this->value.getGlobalBounds().width / 2;

    this->text.setPosition(posXText, this->originY + sizeY / 2 - (this->text.getLocalBounds().height / 1.5));
    this->value.setPosition(posXValue, this->originY + sizeY / 2 - this->value.getLocalBounds().height / 1.5);
    this->square.setPosition(posXSquare, this->originY);
}

void MenuText::addLetterToValue(char letter){
    if(this->changingValue){
        if(this->getValue().size() < 15 && ((letter >= 48 && letter <= 59) || (letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122) || letter == 46)){
            this->setValue(this->getValue() + letter);
        }else if(this->getValue().size() > 0 && letter == 8){
            this->setValue(this->getValue().substr(0, this->getValue().size() - 1));
        }
    }
}

std::string MenuText::getValue(){
    return this->value.getString();
}

void MenuText::setValue(const std::string& value){
    this->value.setString(value);
}