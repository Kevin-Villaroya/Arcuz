#include "ModelMenu.h"
#include <iostream>
#include "../../controller/controllerState/gameController/GameController.h"
#include "../../controller/controllerState/menuIpController/MenuIpController.h"

ModelMenu::ModelMenu(View& view) : view(view), fondSprite(*MenuTexture::getMenuFond()){
    this->initMenu();
    this->nicknameUpdating = false;
    this->hosting = false;
}

void ModelMenu::render(){
    std::vector<sf::Drawable*> allDraws;
    std::vector<sf::Drawable*> menuButtonDrawables;

    allDraws.push_back(&this->fondSprite);

    allDraws.push_back(&this->squareNickname);
    allDraws.push_back(&this->nickname);

    menuButtonDrawables = this->solo.getElementsToRender();
    for(unsigned int i = 0; i < menuButtonDrawables.size(); i++){
        allDraws.push_back(menuButtonDrawables[i]);
    }

    menuButtonDrawables = this->host.getElementsToRender();
    for(unsigned int i = 0; i < menuButtonDrawables.size(); i++){
        allDraws.push_back(menuButtonDrawables[i]);
    }

    menuButtonDrawables = this->join.getElementsToRender();
    for(unsigned int i = 0; i < menuButtonDrawables.size(); i++){
        allDraws.push_back(menuButtonDrawables[i]);
    }

    menuButtonDrawables = this->chooseType.getElementsToRender();
    for(unsigned int i = 0; i < menuButtonDrawables.size(); i++){
        allDraws.push_back(menuButtonDrawables[i]);
    }

    this->view.render(allDraws);
}

void ModelMenu::update(){
    this->setPositionNickname();
    this->chooseType.update(&this->view);
    this->solo.update(&this->view);
    this->host.update(&this->view);
    this->join.update(&this->view);
}

void ModelMenu::initMenu(){
    sf::Vector2f sizeScreen = this->view.getSize();
    sf::Vector2u actualScale = this->fondSprite.getTexture()->getSize();
    this->fondSprite.scale(this->view.getSize().x / actualScale.x, this->view.getSize().y / actualScale.y);

    this->initView();

    this->initNicknameSquare();

    this->nickname.setFont(FontTool::REGULAR_FONT);
    this->nickname.setFillColor(sf::Color::White);
    this->nickname.setString("Default");

    this->chooseType = MenuButtonSelect(sizeScreen.x * 0.1, sizeScreen.y * 0.15, sizeScreen.x * 0.80, sizeScreen.y * 0.15, MenuTexture::getMenuArmoire(), FontTool::REGULAR_FONT, "skin:", "boy");
    this->chooseType.addOption("boy");
    this->chooseType.addOption("girl");

    this->solo = MenuButton(sizeScreen.x * 0.1, sizeScreen.y * 0.3, sizeScreen.x * 0.80, sizeScreen.y * 0.2, MenuTexture::getMenuSolo(), FontTool::REGULAR_FONT, "solo", "launch game");
    this->host = MenuButton(sizeScreen.x * 0.1, sizeScreen.y * 0.55, sizeScreen.x * 0.80, sizeScreen.y * 0.2, MenuTexture::getMenuHost(), FontTool::REGULAR_FONT, "host", "create game");
    this->join = MenuButton(sizeScreen.x * 0.1, sizeScreen.y * 0.8, sizeScreen.x * 0.80, sizeScreen.y * 0.2, MenuTexture::getMenuJoin(), FontTool::REGULAR_FONT, "join", "find game");
}

void ModelMenu::initView(){
    sf::Vector2f sizeScreen = this->view.getSize();

    this->view.setSize(sizeScreen.x, sizeScreen.y);
    this->view.centerViewOn(sizeScreen.x / 2, sizeScreen.y / 2);
}

unsigned int ModelMenu::clickOnMenu(float x, float y){
    sf::Vector2f posMouse = this->convertPositionMouse(x, y);

    this->clickOnNickname(posMouse.x, posMouse.y);
    this->chooseType.clickOnButton(posMouse.x, posMouse.y);

    if(this->solo.clickOnButton(posMouse.x, posMouse.y)){
        return GameController::id;
    }else if(this->host.clickOnButton(posMouse.x, posMouse.y)){
        this->hosting = true;
        return MenuIpController::id;
    }else if(this->join.clickOnButton(posMouse.x, posMouse.y)){
        this->hosting = false;
        return MenuIpController::id;
    }else{
        return 0;
    }
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

bool& ModelMenu::isHosting(){
    return this->hosting;
}

std::string& ModelMenu::getSkin(){
    return this->chooseType.getCurrentOption();
}

std::string& ModelMenu::getNameCharacter(){
    this->nameCharacter = this->nickname.getString();
    return nameCharacter;
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
    sf::Vector2u sizeWindow = this->view.getSizeWindow();

    float sizeNickname = this->squareNickname.getSize().x - this->nickname.getGlobalBounds().width;
    this->nickname.setScale(sizeScreen.x / sizeWindow.x, 1);
    this->nickname.setPosition(sizeScreen.x / 2 - sizeScreen.x * 0.25 + 1 + sizeNickname / 2, sizeScreen.y * 0.05 - this->nickname.getCharacterSize() / 2);
}

sf::Vector2f ModelMenu::convertPositionMouse(float x, float y){
    return sf::Vector2f((x / this->view.getSizeWindow().x) * this->view.getSize().x, (y / this->view.getSizeWindow().y) * this->view.getSize().y);
}