#include "PauseMenu.hpp"
#include "GameplayScene.hpp"
#include "LayoutSettings.hpp"
#include "MainMenuScene.hpp"

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
std::string getStringForKey(const std::string& key);
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

            Vector<MenuItem*> labels;
            auto label = Label::createWithTTF(getStringForKey("pause_menu_resume"), LayoutSettings::menuFont, LayoutSettings::fontSize);
            auto menuItem = MenuItemLabel::create(label,
                [this](Ref* pSender)
            {
                hide();
                m_gameplay->enableInput();
            }
            );
            labels.pushBack(menuItem);

            label = Label::createWithTTF(getStringForKey("main_menu_settings"), LayoutSettings::menuFont, LayoutSettings::fontSize);
            menuItem = MenuItemLabel::create(label, [this](Ref* pSender) {});
            labels.pushBack(menuItem);

            label = Label::createWithTTF(getStringForKey("pause_menu_exit_to_menu"), LayoutSettings::menuFont, LayoutSettings::fontSize);
            menuItem = MenuItemLabel::create(label, [this](Ref* pSender)
                {
                    hide();
                    auto scene = MainMenu::createScene();
                    Director::getInstance()->replaceScene(scene);
                });
            labels.pushBack(menuItem);

            label = Label::createWithTTF(getStringForKey("pause_menu_exit_to_windows"), LayoutSettings::menuFont, LayoutSettings::fontSize);
            menuItem = MenuItemLabel::create(label, [this](Ref* pSender)
            {
                Director::getInstance()->end();
            });

            labels.pushBack(menuItem);

            for (int i = 0; i < labels.size(); i++)
            {
                MenuItemLabel* item = static_cast<MenuItemLabel*>(labels.at(i));

                float x = origin.x + m_background->getContentSize().width * LayoutSettings::PauseMenuPercentageFromLeft + item->getContentSize().width / 2;
                float y = origin.y + m_background->getContentSize().height * LayoutSettings::PauseMenuPercentageFromBottom - i * LayoutSettings::step;

                item->setPosition(Vec2(x, y));
            }

            auto menu = Menu::createWithArray(labels);

            menu->setPosition(Vec2::ZERO);
            m_background->addChild(menu, 1);


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
