#include "GameplayScene.hpp"

USING_NS_CC;

GameplayScene::GameplayScene()
    : m_status(nullptr)
    , m_pauseMenu(this)
    , m_keyboardListener(nullptr)
    , m_mouseListener(nullptr)
{
}

GameplayScene::~GameplayScene()
{
    if (m_keyboardListener)
    {
        m_keyboardListener->release();
    }

    if (m_mouseListener)
    {
        m_mouseListener->release();
    }
}

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

    m_keyboardListener = EventListenerKeyboard::create();
    m_keyboardListener->retain();
    m_mouseListener = EventListenerMouse::create();
    m_mouseListener->retain();

    Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);

    m_keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
        {
            m_pauseMenu.toggle();
        }
        m_status->setString("onKeyPressed");
    };

    m_keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        m_status->setString("onKeyReleased");
    };

    m_mouseListener->onMouseDown = [this](EventMouse* event)
    {
        m_status->setString("onMouseDown");
    };

    m_mouseListener->onMouseUp = [this](EventMouse* event)
    {
        m_status->setString("onMouseUp");
    };

    m_mouseListener->onMouseMove = [this](EventMouse* event)
    {
        m_status->setString("onMouseMove");
    };

    enableInput();
    return true;
}

void GameplayScene::enableInput()
{
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(m_mouseListener, this);
}

void GameplayScene::disableInput()
{
    this->_eventDispatcher->removeEventListener(m_keyboardListener);
    this->_eventDispatcher->removeEventListener(m_mouseListener);
}

void GameplayScene::setPauseMenuInput(EventListenerKeyboard* k)
{
    this->_eventDispatcher->addEventListenerWithFixedPriority(k, 1);
}

void GameplayScene::removePauseMenuInput(cocos2d::EventListenerKeyboard* k)
{
    this->_eventDispatcher->removeEventListener(k);
}

void GameplayScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void GameplayScene::update(float delta)
{

}
