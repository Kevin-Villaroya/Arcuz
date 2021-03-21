#ifndef __MODEL_MENU_IP_H__
#define __MODEL_MENU_IP_H__

#include "../viewer/view/View.h"
#include "../../tool/FontTool.h"
#include "../../viewer/elementMenu/MenuText.h"
#include "../../viewer/elementMenu/MenuButton.h"
#include <SFML/Network.hpp>
#include <string>

class ModelMenuIp{
    private:
        View view;

        std::string nameCharacter;
        std::string type;

        MenuText ipText;
        sf::IpAddress ip;
        MenuText portText;
        unsigned short port;

        MenuButton valider;

        const TextureTool textureFond;
        sf::Sprite fondSprite;

        void initMenu();
        void initView();
        sf::Vector2f convertPositionMouse(float x, float y);

        bool isHosting;
    public:
        ModelMenuIp(View& view);
        void render();
        void update();

        unsigned int clickOnMenu(float x, float y);

        void changeValue(char letter);

        void setNameCharacter(const std::string& nameCharacter);
        std::string& getNameCharacter();

        void setType(std::string type);
        std::string& getType();

        void setPort(unsigned short port);
        unsigned short& getPort();

        void setIp(sf::IpAddress ip);
        sf::IpAddress& getIp();

        bool& getIsHost();
        void setIsHost(bool isHost);
};


#endif