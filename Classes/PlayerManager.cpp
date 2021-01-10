#include "PlayerManager.hpp"

PlayerManager& PlayerManager::get()
{
    static PlayerManager m;
    return m;
}

void PlayerManager::reset()
{
    clear();
    m_characters.push_back(new Character());
}

void PlayerManager::update(float delta)
{
    for (auto it : m_characters)
    {
        it->update(delta);
    }
}

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
    clear();
}

void PlayerManager::clear()
{
    for (auto it : m_characters)
    {
        delete it;
    }
    m_characters.clear();
}
