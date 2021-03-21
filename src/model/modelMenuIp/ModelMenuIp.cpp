#include "ModelMenuIp.h"
#include "../tool/FontTool.h"
#include "../../controller/controllerState/gameController/network/NetworkClient.h"
#include "../../controller/controllerState/gameController/network/NetworkServer.h"
#include <SFML/System/Time.hpp>

ModelMenuIp::ModelMenuIp(View& view) : view(view), textureFond(TextureTool("assets/menu/fond.png")), fondSprite(textureFond){
    this->port = 23547;
    this->ip = sf::IpAddress("127.0.0.1");

    this->initMenu();
}

void ModelMenuIp::render(){
    std::vector<sf::Drawable*> allDraws;
    std::vector<sf::Drawable*> menuButtonDrawables;

    allDraws.push_back(&this->fondSprite);

    menuButtonDrawables = this->ipText.getElementsToRender();
    for(unsigned int i = 0; i < menuButtonDrawables.size(); i++){
        allDraws.push_back(menuButtonDrawables[i]);
    }

    menuButtonDrawables = this->portText.getElementsToRender();
    for(unsigned int i = 0; i < menuButtonDrawables.size(); i++){
        allDraws.push_back(menuButtonDrawables[i]);
    }

    menuButtonDrawables = this->valider.getElementsToRender();
    for(unsigned int i = 0; i < menuButtonDrawables.size(); i++){
        allDraws.push_back(menuButtonDrawables[i]);
    }

    this->view.render(allDraws);
}

void ModelMenuIp::update(){
    this->portText.update(&this->view);
    this->ipText.update(&this->view);
    this->valider.update(&this->view);
}

unsigned int ModelMenuIp::clickOnMenu(float x, float y){
    sf::Vector2f posMouse = this->convertPositionMouse(x, y);


    if(this->ipText.clickOnButton(posMouse.x, posMouse.y) && this->isHosting == false){
        this->ipText.setChangingValue(true);
    }else{
        this->ipText.setChangingValue(false);
    }
    
    if(this->portText.clickOnButton(posMouse.x, posMouse.y)){
        this->portText.setChangingValue(true);
    }else{
        this->portText.setChangingValue(false);
    }
    
    if(this->valider.clickOnButton(posMouse.x, posMouse.y)){
        if(this->isHosting){
            return NetworkServer::id;
        }else{
            return NetworkClient::id;
        }
    }

    return 0;
}

void ModelMenuIp::initMenu(){
    sf::Vector2u actualScale = this->fondSprite.getTexture()->getSize();
    sf::Vector2f sizeScreen = this->view.getSize();

    this->initView();

    this->fondSprite.scale(this->view.getSize().x / actualScale.x, this->view.getSize().y / actualScale.y);

    this->portText = MenuText(sizeScreen.x * 0.2, sizeScreen.y * 0.3, sizeScreen.x * 0.6, sizeScreen.y * 0.1, "Port:", std::to_string(this->port));
    this->ipText = MenuText(sizeScreen.x * 0.2, sizeScreen.y * 0.1, sizeScreen.x * 0.6, sizeScreen.y * 0.1, "IP:", this->ip.toString());
    this->valider = MenuButton(sizeScreen.x * 0.1, sizeScreen.y * 0.6, sizeScreen.x * 0.8, sizeScreen.y * 0.2, sf::Color::Green, FontTool::REGULAR_FONT, "Lancer le jeu", "Valider");
}

void ModelMenuIp::initView(){
    sf::Vector2f sizeScreen = this->view.getSize();

    this->view.setSize(sizeScreen.x, sizeScreen.y);
    this->view.centerViewOn(sizeScreen.x / 2, sizeScreen.y / 2);
}

void ModelMenuIp::changeValue(char letter){
    this->ipText.addLetterToValue(letter);
    this->ip = sf::IpAddress(this->ipText.getValue());

    if((letter >= 48 && letter <= 57) || letter == 8){ //letter is a number or a delete
        this->portText.addLetterToValue(letter);
    }
    
    if(this->portText.getValue().size() > 0){
        if(std::stoi(this->portText.getValue()) > 65535){ //if the port is out of range
            this->portText.addLetterToValue(8);
        }else{
            this->port = std::stoi(this->portText.getValue());
        }          
    }
    
}

void ModelMenuIp::setNameCharacter(const std::string& nameCharacter){
    this->nameCharacter = nameCharacter;
}

std::string& ModelMenuIp::getNameCharacter(){
    return this->nameCharacter;
}

void ModelMenuIp::setType(std::string type){
    this->type = type;
}

std::string& ModelMenuIp::getType(){
    return this->type;
}

void ModelMenuIp::setPort(unsigned short port){
    this->port = port;
    this->portText.setValue(std::to_string(port));
}

unsigned short& ModelMenuIp::getPort(){
    return this->port;
}

void ModelMenuIp::setIp(sf::IpAddress ip){
    this->ip = ip;
    this->ipText.setValue(ip.toString());
}

sf::IpAddress& ModelMenuIp::getIp(){
    return this->ip;
}

bool& ModelMenuIp::getIsHost(){
    return this->isHosting;
}

void ModelMenuIp::setIsHost(bool isHost){
    this->isHosting = isHost;
    if(isHost == true){
        this->setIp(sf::IpAddress::getPublicAddress(sf::seconds(1)));
        this->ipText.disable();
    }else{
        this->ipText.enable();
    }
}

sf::Vector2f ModelMenuIp::convertPositionMouse(float x, float y){
    return sf::Vector2f((x / this->view.getSizeWindow().x) * this->view.getSize().x, (y / this->view.getSizeWindow().y) * this->view.getSize().y);
}