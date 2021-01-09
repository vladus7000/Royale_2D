#pragma once

class PlayerManager
{
public:
    static PlayerManager& get();

public:
    PlayerManager(const PlayerManager& rhs) = delete;
    PlayerManager(PlayerManager&& rhs) = delete;
    PlayerManager& operator=(const PlayerManager& rhs) = delete;
    PlayerManager& operator=(PlayerManager&& rhs) = delete;

private:
    PlayerManager();
    ~PlayerManager();
};