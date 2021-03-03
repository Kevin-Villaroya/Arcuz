#include "ModelMenu.h"
#include <iostream>

ModelMenu::ModelMenu(View& view) : view(view), textureFond(TextureTool("assets/menu/fond.png")), fondSprite(textureFond){
    this->initMenu();
    this->nicknameUpdating = false;
    this->font.loadFromFile("assets/font/regular.ttf");
}

void ModelMenu::render(){
    std::vector<sf::Drawable*> allDraws;

    this->setPositionNickname();
    allDraws.push_back(&this->fondSprite);

    allDraws.push_back(&this->squareNickname);
    allDraws.push_back(&this->nickname);

    this->view.render(allDraws);
}

void ModelMenu::initMenu(){
    sf::Vector2u actualScale = this->fondSprite.getTexture()->getSize();
    this->fondSprite.scale(this->view.getSize().x / actualScale.x, this->view.getSize().y / actualScale.y);

    this->initView();

    this->initNicknameSquare();

    this->nickname.setFont(font);
    this->nickname.setFillColor(sf::Color::White);
    this->nickname.setString("Default");
}

void ModelMenu::initView(){
    sf::Vector2f sizeScreen = this->view.getSize();

    this->view.setSize(sizeScreen.x, sizeScreen.y);
    this->view.centerViewOn(sizeScreen.x / 2, sizeScreen.y / 2);
}

void ModelMenu::clickOnMenu(float x, float y){
    sf::Vector2f posMouse = this->convertPositionMouse(x, y);
    this->clickOnNickname(posMouse.x, posMouse.y);
}

void ModelMenu::clickOnNickname(float posX, float posY){
    sf::Vector2f position = this->squareNickname.getPosition();
    sf::Vector2f size = this->squareNickname.getSize();

    if(posX > position.x && posX < position.x + size.x && posY > position.y && posY < position.y + size.y){
        nicknameUpdating = true;
        this->squareNickname.setOutlineColor(sf::Color::Blue);
    }else{
        nicknameUpdating = false;
        this->squareNickname.setOutlineColor(sf::Color::White);
    }
}

bool ModelMenu::nicknameIsUpdating(){
    return this->nicknameUpdating;
}

void ModelMenu::changeNickname(char letter){
    if(this->nickname.getString().getSize() < 15 && ((letter >= 48 && letter <= 59) || (letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122))){
        this->nickname.setString(this->nickname.getString() + letter);
    }else if(this->nickname.getString().getSize() > 0 && letter == 8){
        this->nickname.setString(this->nickname.getString().substring(0, this->nickname.getString().getSize() - 1));
    }
}

void ModelMenu::initNicknameSquare(){
    sf::Vector2f sizeScreen = this->view.getSize();

    this->squareNickname = sf::RectangleShape(sf::Vector2f(sizeScreen.x * 0.5, sizeScreen.y * 0.1));
    this->squareNickname.setPosition(sizeScreen.x / 2 - sizeScreen.x * 0.25 ,1);
    this->squareNickname.setFillColor(sf::Color::Black);
    this->squareNickname.setOutlineThickness(3);
    this->squareNickname.setOutlineColor(sf::Color::White);
}

void ModelMenu::setPositionNickname(){
    sf::Vector2f sizeScreen = this->view.getSize();

    float sizeNickname = this->squareNickname.getSize().x - this->nickname.getGlobalBounds().width;
    this->nickname.setPosition(sizeScreen.x / 2 - sizeScreen.x * 0.25 + 1 + sizeNickname / 2, sizeScreen.y * 0.05 - this->nickname.getCharacterSize() / 2);
}

sf::Vector2f ModelMenu::convertPositionMouse(float x, float y){
    return sf::Vector2f((x / this->view.getSizeWindow().x) * this->view.getSize().x, (y / this->view.getSizeWindow().y) * this->view.getSize().y);
}