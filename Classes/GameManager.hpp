#pragma once

class GameManager
{
public:
    static GameManager& get();

public:
    GameManager(const GameManager& rhs) = delete;
    GameManager(GameManager&& rhs) = delete;
    GameManager& operator=(const GameManager& rhs) = delete;
    GameManager& operator=(GameManager&& rhs) = delete;

private:
    GameManager();
    ~GameManager();
};