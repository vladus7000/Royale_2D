#pragma once

#include "cocos2d.h"
class GameplayScene;

class PauseMenu
{
public:
    PauseMenu(GameplayScene* scene);
    ~PauseMenu();

    void show();
    void hide();
    void toggle();
    bool isHide() const { return m_isHide; }

private:
    void updateState();

private:
    GameplayScene* m_gameplay;
    cocos2d::Sprite* m_background;
    bool m_isHide;
    cocos2d::EventListenerKeyboard* m_keyboardListener;
};
