#include "SaveManager.hpp"

SaveManager& SaveManager::get()
{
    static SaveManager m;
    return m;
}

SaveManager::SaveManager()
{
}


SaveManager::~SaveManager()
{
}
