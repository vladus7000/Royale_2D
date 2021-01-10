#pragma once
#include "cocos2d.h"

class GameManager
{
public:
    static GameManager& get();

    void setStartingCoord(const cocos2d::Vec2& p) { m_startingCoord = p; }
    cocos2d::Vec2 getStartingCoord() const { return m_startingCoord; }

public:
    GameManager(const GameManager& rhs) = delete;
    GameManager(GameManager&& rhs) = delete;
    GameManager& operator=(const GameManager& rhs) = delete;
    GameManager& operator=(GameManager&& rhs) = delete;

private:
    GameManager();
    ~GameManager();

private:
    cocos2d::Vec2 m_startingCoord = {0.0f, 0.0f};
};