#include "GameplayScene.hpp"
#include "PlayerManager.hpp"

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

    initDebugItems();
    initMap();
    initClouds();
    initCharacters();
    initStartActions();
    initInput();
    scheduleUpdate();
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
    PlayerManager::get().update(delta);
    auto character = PlayerManager::get().getPlayerCharacter();
    auto pos = character->getPosition();
    m_velocity = { 0.0f, 0.0f };
    character->getSprite()->setRotation(0.0f);
    if (m_gameplayKeys[(int)GameplayKeys::A])
    {
        m_velocity.x = -1.0f;
        character->getSprite()->setRotation(-45.0f);
    }
    if (m_gameplayKeys[(int)GameplayKeys::D])
    {
        character->getSprite()->setRotation(45.0f);
        m_velocity.x = 1.0f;
    }
    if (m_gameplayKeys[(int)GameplayKeys::A] && m_gameplayKeys[(int)GameplayKeys::D])
    {
        character->getSprite()->setRotation(0.0f);
        m_velocity.x = 0.0f;
    }

    if (m_gameplayKeys[(int)GameplayKeys::W])
    {
        m_velocity.y = 1.0f;
    }
    if (m_gameplayKeys[(int)GameplayKeys::S])
    {
        character->getSprite()->setRotation(180.0f);
        m_velocity.y = -1.0f;
    }
    if (m_gameplayKeys[(int)GameplayKeys::W] && m_gameplayKeys[(int)GameplayKeys::S])
    {
        m_velocity.y = 0.0f;
    }
    m_velocity.normalize();

    pos += m_velocity * 100.0f * delta;

    character->setPosition(pos);
}

void GameplayScene::initDebugItems()
{
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
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    m_status = Label::createWithTTF("Royal 2D", "fonts/Marker Felt.ttf", 24);
    m_status->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 20));
    this->addChild(m_status, 1);
}

void GameplayScene::initInput()
{
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

        if (keyCode == EventKeyboard::KeyCode::KEY_A)
        {
            m_gameplayKeys[(int)GameplayKeys::A] = true;
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_D)
        {
            m_gameplayKeys[(int)GameplayKeys::D] = true;
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_W)
        {
            m_gameplayKeys[(int)GameplayKeys::W] = true;
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_S)
        {
            m_gameplayKeys[(int)GameplayKeys::S] = true;
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
        {
            m_gameplayKeys[(int)GameplayKeys::Space] = true;
        }
    };

    m_keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_A)
        {
            m_gameplayKeys[(int)GameplayKeys::A] = false;
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_D)
        {
            m_gameplayKeys[(int)GameplayKeys::D] = false;
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_W)
        {
            m_gameplayKeys[(int)GameplayKeys::W] = false;
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_S)
        {
            m_gameplayKeys[(int)GameplayKeys::S] = false;
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
        {
            m_gameplayKeys[(int)GameplayKeys::Space] = false;
        }
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
}

void GameplayScene::initMap()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    m_map = Sprite::create("game_map_with_water.png");
    m_map->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    m_map->setScale(0.25f);

    this->addChild(m_map, 0);
}

void GameplayScene::initCharacters()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    PlayerManager::get().reset();

    PlayerManager::get().getPlayerCharacter()->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(PlayerManager::get().getPlayerCharacter()->getSprite(), 0);
}

void GameplayScene::initStartActions()
{
    auto landed = CallFunc::create([this]()
    {
        m_matchState = MatchState::OnGround;
        PlayerManager::get().getPlayerCharacter()->setState(Character::State::OnGround);

        for (auto it : m_clouds)
        {
            removeChild(it);
        }
        m_clouds.clear();
    });

    auto action = ScaleTo::create(15.0f, 1.0f);
    auto sequence = Sequence::create(action, landed, NULL);
    m_map->runAction(sequence);
}

void GameplayScene::initClouds()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    for (int i = 0; i < 10; i++)
    {
        auto cloud = Sprite::create("cloud.png");

        auto x = cocos2d::RandomHelper::random_real(50.0f, visibleSize.width-50.0f);
        auto y = cocos2d::RandomHelper::random_real(50.0f, visibleSize.height-50.0f);
        cloud->setPosition(Vec2(x + origin.x, y + origin.y));

        auto opacity = cocos2d::RandomHelper::random_int(120, 210);
        cloud->setOpacity(opacity);

        auto scale = cocos2d::RandomHelper::random_real(0.4f, 1.2f);
        cloud->setScale(scale);

        x = cocos2d::RandomHelper::random_real(-300.0f, 300.0f);
        y = cocos2d::RandomHelper::random_real(-300.0f, 300.0f);
        auto action = MoveBy::create(15.0f, Vec2(x, y));
        auto actionOpacity = FadeTo::create(15.0f, 0);
        auto parallel = Spawn::create(action, actionOpacity, NULL);

        cloud->runAction(parallel);

        m_clouds.push_back(cloud);
        this->addChild(cloud, 1);
    }
}
