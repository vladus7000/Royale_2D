#pragma once
#include "cocos2d.h"

class GameManager
{
public:
    static GameManager& get();

    void setPlayerStartingCoord(const cocos2d::Vec2& p) { m_startingCoord = p; }
    cocos2d::Vec2 getPlayerStartingCoord() const { return m_startingCoord; }

    unsigned int getNumberStartingPoints() { return m_numStartingPoints; }
    bool isStartingPointFree(unsigned int i);
    void setPointOccupied(unsigned int i);

    void reset();
    void update(float delta);

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
    static const unsigned int m_numStartingPoints = 8;
    bool m_freeStartingPoints[m_numStartingPoints] = { true };
};