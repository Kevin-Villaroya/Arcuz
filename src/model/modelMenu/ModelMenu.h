#ifndef __MODEL_MENU_H__
#define __MODEL_MENU_H__

#include "../viewer/view/View.h"
#include "../../viewer/elementMenu/MenuButton.h"
#include "../../viewer/elementMenu/MenuButtonSelect.h"
#include "../../tool/FontTool.h"
#include "../../viewer/texture/MenuTexture.h"
#include <string>

class ModelMenu{
    private:
        View view;

        sf::RectangleShape squareNickname;

        sf::Text nickname;
        std::string nameCharacter;

        MenuButton solo;
        MenuButton host;
        MenuButton join;

        MenuButtonSelect chooseType;

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

        std::string& getSkin();
        std::string& getNameCharacter();
};

#endif