#pragma once

#include "cocos2d.h"
#include "PauseMenu.hpp"

enum class MatchState
{
    Parachuting,
    OnGround
};

enum class GameplayKeys
{
    W, A, S, D, Space
};

class GameplayScene : public cocos2d::Scene
{
public:
    GameplayScene();
    ~GameplayScene();
    static cocos2d::Scene* createScene();

    virtual bool init();

    void enableInput();
    void disableInput();

    void setPauseMenuInput(cocos2d::EventListenerKeyboard* k);
    void removePauseMenuInput(cocos2d::EventListenerKeyboard* k);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameplayScene);

private:
    virtual void update(float delta) override;

private:
    cocos2d::Label* m_status;
    PauseMenu m_pauseMenu;
    cocos2d::EventListenerKeyboard* m_keyboardListener;
    cocos2d::EventListenerMouse* m_mouseListener;
    MatchState m_matchState = MatchState::Parachuting;
    cocos2d::Sprite* m_character = nullptr;
    cocos2d::Vec2 m_velocity = {0.0f, 0.0f};
    bool m_gameplayKeys[(unsigned int)GameplayKeys::Space] = {false};
};