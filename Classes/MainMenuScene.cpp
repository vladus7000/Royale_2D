#include "MainMenuScene.hpp"
#include "GameplayScene.hpp"

#include "cocos-ext.h"
#include <CCFileUtils.h>

using namespace rapidjson;

USING_NS_CC;
Document document;

void InitLocalization()
{
    std::string filename("localization.json");
    Data d = FileUtils::getInstance()->getDataFromFile(filename);
    document.Parse((char*)d.getBytes(), d.getSize());
}

std::string getStringForKey(const std::string& key)
{
    return document["ru"][key.c_str()].GetString();
}

namespace MenuLayoutSettings
{
    //Fonts
    const std::string menuFont("fonts/comic.ttf");

    //Images
    const std::string menuBackground("menu_background.png");

    //Const
    const float fontSize = 60.0f;
    const float step = 70.0f;
    const float percentageFromLeft = 0.2f;
    const float percentageFromBottom = 0.75f;
}

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

bool MainMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }

    InitLocalization();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vector<MenuItem*> labels;
    auto label = Label::createWithTTF(getStringForKey("main_menu_landing"), MenuLayoutSettings::menuFont, MenuLayoutSettings::fontSize);
    auto menuItem = MenuItemLabel::create(label,
        [this](Ref* pSender)
            {
                auto scene = GameplayScene::createScene();
                Director::getInstance()->replaceScene(scene);
            }
        );
    labels.pushBack(menuItem);

    label = Label::createWithTTF(getStringForKey("main_menu_settings"), MenuLayoutSettings::menuFont, MenuLayoutSettings::fontSize);
    menuItem = MenuItemLabel::create(label, [this](Ref* pSender) {});
    labels.pushBack(menuItem);

    label = Label::createWithTTF(getStringForKey("main_menu_quit"), MenuLayoutSettings::menuFont, MenuLayoutSettings::fontSize);
    menuItem = MenuItemLabel::create(label, [this](Ref* pSender) { Director::getInstance()->end(); });
    labels.pushBack(menuItem);

    for (int i = 0; i < labels.size(); i++)
    {
        MenuItemLabel* item = static_cast<MenuItemLabel*>(labels.at(i));

        float x = origin.x + visibleSize.width * MenuLayoutSettings::percentageFromLeft + item->getContentSize().width / 2;
        float y = origin.y + visibleSize.height * MenuLayoutSettings::percentageFromBottom - i * MenuLayoutSettings::step;

        item->setPosition(Vec2(x, y));
    }

    auto menu = Menu::createWithArray(labels);

    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto sprite = Sprite::create(MenuLayoutSettings::menuBackground);
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(sprite, 0);

    return true;
}