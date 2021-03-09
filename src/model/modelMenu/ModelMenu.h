#ifndef __MODEL_MENU_H__
#define __MODEL_MENU_H__

#include "../viewer/view/View.h"
#include "../../viewer/elementMenu/MenuButton.h"
#include "../../tool/FontTool.h"
#include <string>

class ModelMenu{
    private:
        View view;

        sf::RectangleShape squareNickname;

        sf::Text nickname;
        std::string nameCharacter;

        MenuButton solo;
        TextureTool soloTexture;

        MenuButton host;
        TextureTool hostTexture;

        MenuButton join;
        TextureTool joinTexture;

        const TextureTool textureFond;
        sf::Sprite fondSprite;

        bool nicknameUpdating;

        bool hosting;

        void initMenu();
        void initNicknameSquare();
        void initView();

        void setPositionNickname();
        sf::Vector2f convertPositionMouse(float x, float y);

        void clickOnNickname(float posX, float posY);
    public:
        ModelMenu(View& view);
        void render();
        void update();

        unsigned int clickOnMenu(float x, float y);
        bool nicknameIsUpdating();
        void changeNickname(char letter);

        bool& isHosting();

        std::string& getNameCharacter();
};

#endif