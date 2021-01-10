#include "GameManager.hpp"

GameManager& GameManager::get()
{
    static GameManager m;
    return m;
}

bool GameManager::isStartingPointFree(unsigned int i)
{
    return m_freeStartingPoints[i];
}

void GameManager::setPointOccupied(unsigned int i)
{
    m_freeStartingPoints[i] = false;
}

void GameManager::reset()
{
    for (auto& it : m_freeStartingPoints)
    {
        it = true;
    }
}

void GameManager::update(float delta)
{
    static float time = 0.0f;
    time += delta;

    if (time >= 1.0f)
    {
        time = 0.0f;

        for (auto& it : m_freeStartingPoints)
        {
            if (it)
            {
                it = false;
                break;
            }
        }
    }
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}
