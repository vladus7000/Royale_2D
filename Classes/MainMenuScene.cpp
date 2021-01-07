#include "MainMenuScene.hpp"
#include "GameplayScene.hpp"

#include "cocos-ext.h"
#include <CCFileUtils.h>

using namespace rapidjson;

USING_NS_CC;

std::string getStringForKey(const std::string& key)
{
    std::string filename("localization.json");
    unsigned long size;
    Data d =  FileUtils::getInstance()->getDataFromFile(filename);

    Document document;
    document.Parse((char*)d.getBytes(), d.getSize());

    return document["ru"][key.c_str()].GetString();
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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vector<MenuItem*> labels;

    auto label = MenuItemFont::create(getStringForKey("main_menu_play"), 
        [this](Ref* pSender)
            {
                auto scene = GameplayScene::createScene();
                Director::getInstance()->replaceScene(scene);
            }
        );
    labels.pushBack(label);

    label = MenuItemFont::create(getStringForKey("main_menu_settings"), [this](Ref* pSender) {});
    labels.pushBack(label);

    label = MenuItemFont::create(getStringForKey("main_menu_quit"), [this](Ref* pSender) { Director::getInstance()->end(); });
    labels.pushBack(label);

    for (int i = 0; i < labels.size(); i++)
    {
        const float step = 50.0f;
        MenuItemFont* item = static_cast<MenuItemFont*>(labels.at(i));

        float x = origin.x + visibleSize.width * 0.25f + item->getContentSize().width / 2;
        float y = origin.y + visibleSize.height * 0.8f - i * step;

        item->setFontName("fonts/arial.ttf");
        item->setFontSize(100);
        item->setPosition(Vec2(x, y));
    }

    auto menu = Menu::createWithArray(labels);

    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}