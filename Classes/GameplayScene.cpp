#include "GameplayScene.hpp"

USING_NS_CC;

Scene* GameplayScene::createScene()
{
    return GameplayScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameplayScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameplayScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    m_status = Label::createWithTTF("Royal 2D", "fonts/Marker Felt.ttf", 24);
    if (m_status == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        m_status->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height-20));

        // add the label as a child to this layer
        this->addChild(m_status, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("map.png");
    if (sprite == nullptr)
    {
        problemLoading("'map.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }

    auto keyboardListener = EventListenerKeyboard::create();
    auto mouseListener = EventListenerMouse::create();

    Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);

    keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
        {
            m_status->setString("onKeyPressed");
        }
    };

    keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        m_status->setString("onKeyReleased");
    };

    mouseListener->onMouseDown = [this](EventMouse* event)
    {
        m_status->setString("onMouseDown");
    };

    mouseListener->onMouseUp = [this](EventMouse* event)
    {
        m_status->setString("onMouseUp");
    };

    mouseListener->onMouseMove = [this](EventMouse* event)
    {
        m_status->setString("onMouseMove");
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    return true;
}


void GameplayScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void GameplayScene::update(float delta)
{

}
