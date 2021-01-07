#include "PauseMenu.hpp"
#include "GameplayScene.hpp"

USING_NS_CC;

PauseMenu::PauseMenu(GameplayScene * scene)
    : m_gameplay(scene)
    , m_isHide(true)
    , m_background(nullptr)
    , m_keyboardListener(nullptr)
{
}

PauseMenu::~PauseMenu()
{
    if (m_keyboardListener)
    {
        m_keyboardListener->release();
    }
}

void PauseMenu::show()
{
    if (m_isHide)
    {
        m_isHide = false;
        updateState();
    }
}

void PauseMenu::hide()
{
    if (!m_isHide)
    {
        m_isHide = true;
        updateState();
    }
}

void PauseMenu::toggle()
{
    m_isHide = !m_isHide;
    updateState();
}

void PauseMenu::updateState()
{
    if (m_isHide)
    {
        m_background->setVisible(false);
        m_gameplay->removePauseMenuInput(m_keyboardListener);
    }
    else
    {
        if (!m_background)
        {
            auto visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 origin = Director::getInstance()->getVisibleOrigin();
            m_background = Sprite::create("pause_background.png");
            m_background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
            m_background->setOpacity(80);
            m_gameplay->addChild(m_background, 0);
        }

        if (!m_keyboardListener)
        {
            m_keyboardListener = EventListenerKeyboard::create();
            m_keyboardListener->retain();
            Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);

            m_keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
            {
                if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
                {
                    hide();
                    m_gameplay->enableInput();
                }
            };

        }
        m_gameplay->disableInput();
        m_gameplay->setPauseMenuInput(m_keyboardListener);

        m_background->setVisible(true);
    }
}
