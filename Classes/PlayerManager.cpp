#include "PlayerManager.hpp"

PlayerManager& PlayerManager::get()
{
    static PlayerManager m;
    return m;
}

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
}
