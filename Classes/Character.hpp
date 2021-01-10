#pragma once
#include "cocos2d.h"
#include "GameplayKeys.hpp"

class Character
{
public:
    enum class State
    {
        Parachuting,
        OnGround
    };

    Character();
    ~Character();

    cocos2d::Sprite* getSprite() const { return m_sprite; }

    void setState(State s);
    State getState() const { return m_state; }

    void setPosition(cocos2d::Vec2 pos) { m_sprite->setPosition(pos); }
    cocos2d::Vec2 getPosition() const { return m_sprite->getPosition(); }

    void update(float delta);
    void setInput();

private:
    cocos2d::Sprite* m_sprite = nullptr;
    bool m_gameplayKeys[(unsigned int)GameplayKeys::Space] = { false };
    State m_state = State::Parachuting;
    cocos2d::Vec2 m_position = { 0.0f, 0.0f };
};