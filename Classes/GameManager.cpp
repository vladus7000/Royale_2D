#include "GameManager.hpp"

GameManager& GameManager::get()
{
    static GameManager m;
    return m;
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}
