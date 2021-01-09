#pragma once

class SaveManager
{
public:
    static SaveManager& get();

public:
    SaveManager(const SaveManager& rhs) = delete;
    SaveManager(SaveManager&& rhs) = delete;
    SaveManager& operator=(const SaveManager& rhs) = delete;
    SaveManager& operator=(SaveManager&& rhs) = delete;

private:
    SaveManager();
    ~SaveManager();
};