#include "MainMenuScene.hpp"
#include "GameplayScene.hpp"
#include "LayoutSettings.hpp"
#include "LocalizationManager.hpp"

USING_NS_CC;

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
    auto label = Label::createWithTTF(LocalizationManager::get().getStringForKey("main_menu_landing"), LayoutSettings::menuFont, LayoutSettings::fontSize);
    auto menuItem = MenuItemLabel::create(label,
        [this](Ref* pSender)
            {
                auto scene = GameplayScene::createScene();
                Director::getInstance()->replaceScene(scene);
            }
        );
    labels.pushBack(menuItem);

    label = Label::createWithTTF(LocalizationManager::get().getStringForKey("main_menu_settings"), LayoutSettings::menuFont, LayoutSettings::fontSize);
    menuItem = MenuItemLabel::create(label, [this](Ref* pSender) {});
    labels.pushBack(menuItem);

    label = Label::createWithTTF(LocalizationManager::get().getStringForKey("main_menu_quit"), LayoutSettings::menuFont, LayoutSettings::fontSize);
    menuItem = MenuItemLabel::create(label, [this](Ref* pSender) { Director::getInstance()->end(); });
    labels.pushBack(menuItem);

    for (int i = 0; i < labels.size(); i++)
    {
        MenuItemLabel* item = static_cast<MenuItemLabel*>(labels.at(i));

        float x = origin.x + visibleSize.width * LayoutSettings::MainMenuPercentageFromLeft + item->getContentSize().width / 2;
        float y = origin.y + visibleSize.height * LayoutSettings::MainMenuPercentageFromBottom - i * LayoutSettings::step;

        item->setPosition(Vec2(x, y));
    }

    auto menu = Menu::createWithArray(labels);

    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto sprite = Sprite::create(LayoutSettings::menuBackground);
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(sprite, 0);

    return true;
}