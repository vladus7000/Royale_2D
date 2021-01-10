#pragma once
#include <vector>
#include "Character.hpp"

class PlayerManager
{
public:
    static PlayerManager& get();

    Character* getPlayerCharacter() { return m_characters[0]; }
    void addCharacter(Character* character) { m_characters.push_back(character); }
    Character* getCharacter(size_t i) { return m_characters[i]; }
    size_t getCharacterCount() const { return m_characters.size(); }

    void reset();

public:
    PlayerManager(const PlayerManager& rhs) = delete;
    PlayerManager(PlayerManager&& rhs) = delete;
    PlayerManager& operator=(const PlayerManager& rhs) = delete;
    PlayerManager& operator=(PlayerManager&& rhs) = delete;

    void update(float delta);

private:
    PlayerManager();
    ~PlayerManager();
    void clear();

private:
    std::vector<Character*> m_characters;
};