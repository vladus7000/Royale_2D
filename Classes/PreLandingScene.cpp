#include "PreLandingScene.hpp"
#include "LocalizationManager.hpp"
#include "GameplayScene.hpp"
#include "MainMenuScene.hpp"
#include "LayoutSettings.hpp"
#include "GameManager.hpp"

USING_NS_CC;

Scene* PreLandingScene::createScene()
{
    return PreLandingScene::create();
}

bool PreLandingScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float y = origin.y + visibleSize.height * LayoutSettings::PreLandingPercentageFromBottom;

    Vector<MenuItem*> labels;
    auto label = Label::createWithTTF(LocalizationManager::get().getStringForKey("prelanding_back"), LayoutSettings::menuFont, LayoutSettings::fontSize);

    float x = origin.x + visibleSize.width * LayoutSettings::PreLandingPercentageFromLeft + label->getContentSize().width / 2;
    auto menuItem = MenuItemLabel::create(label,
        [this](Ref* pSender)
    {
        auto scene = MainMenu::createScene();
        Director::getInstance()->replaceScene(scene);
    });
    menuItem->setPosition(Vec2(x, y));
    labels.pushBack(menuItem);

    label = Label::createWithTTF(LocalizationManager::get().getStringForKey("prelanding_start"), LayoutSettings::menuFont, LayoutSettings::fontSize);
    x = origin.x + visibleSize.width * (1.0f - LayoutSettings::PreLandingPercentageFromLeft) - label->getContentSize().width / 2;
    menuItem = MenuItemLabel::create(label, [this](Ref* pSender)
    {
        auto scene = GameplayScene::createScene();
        Director::getInstance()->replaceScene(scene);
    });
    menuItem->setPosition(Vec2(x, y));
    labels.pushBack(menuItem);

    for (int i = 0; i < 8; i++)
    {
        label = Label::createWithTTF("[ ]", LayoutSettings::menuFont, LayoutSettings::fontSize);

        menuItem = MenuItemLabel::create(label, [this](Ref* pSender)
        {
            if (!m_selected)
            {
                m_selected = true;
                static_cast<MenuItemLabel*>(pSender)->setString("[+]");
                static_cast<MenuItemLabel*>(pSender)->setColor(cocos2d::Color3B(0, 255, 0));
                GameManager::get().setStartingCoord(static_cast<MenuItemLabel*>(pSender)->getPosition());
            }
        });

        const float Rx = 550.0f;
        const float Ry = 400.0f;
        float xc = sinf(0.785398 * i) * Rx + origin.x + visibleSize.width * 0.5f;
        float yc = cosf(0.785398 * i) * Ry + origin.y + visibleSize.height * 0.5f;
        menuItem->setPosition(Vec2(xc, yc));
        
        labels.pushBack(menuItem);
    }

    auto menu = Menu::createWithArray(labels);

    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto sprite = Sprite::create("game_map_with_water.png");
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    sprite->setScale(0.25f);

    auto progressBG = ui::LoadingBar::create("progressBarBG.png");
    progressBG->setDirection(ui::LoadingBar::Direction::LEFT);

    x = origin.x + visibleSize.width * 0.5f;
    progressBG->setPosition(Vec2(x, y));
    progressBG->setScaleX(5.5f);
    progressBG->setScaleY(2.0f);
    progressBG->setPercent(100);
    addChild(progressBG, 1);

    m_loadingBar =  ui::LoadingBar::create("progressBar.png");
    m_loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
    
    x = origin.x + visibleSize.width * 0.5f;
    m_loadingBar->setPosition(Vec2(x, y));
    m_loadingBar->setScaleX(5.5f);
    m_loadingBar->setScaleY(2.0f);
    m_loadingBar->setPercent(0);

    addChild(m_loadingBar, 2);
    this->addChild(sprite, 0);

    scheduleUpdate();

    return true;
}

void PreLandingScene::update(float delta)
{
    m_selectTimer += delta;

    m_loadingBar->setPercent(100.0f * (m_selectTimer / m_timeToSelect));

    if (m_loadingBar->getPercent() == 100)
    {
        auto scene = GameplayScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}
