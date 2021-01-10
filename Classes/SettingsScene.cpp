#include "SettingsScene.hpp"
#include "LocalizationManager.hpp"
#include "LayoutSettings.hpp"

USING_NS_CC;

Scene* SettingsScene::createScene()
{
    return SettingsScene::create();
}

bool SettingsScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create(LayoutSettings::menuBackground);
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(sprite, 0);

    float y = origin.y + visibleSize.height * LayoutSettings::PreLandingPercentageFromBottom;

    Vector<MenuItem*> labels;
    auto label = Label::createWithTTF(LocalizationManager::get().getStringForKey("prelanding_back"), LayoutSettings::menuFont, LayoutSettings::fontSize);

    float x = origin.x + visibleSize.width * LayoutSettings::PreLandingPercentageFromLeft + label->getContentSize().width / 2;
    auto menuItem = MenuItemLabel::create(label,
        [this](Ref* pSender)
    {
        Director::getInstance()->popScene();
    });
    menuItem->setPosition(Vec2(x, y));
    labels.pushBack(menuItem);

    auto menu = Menu::createWithArray(labels);

    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}
