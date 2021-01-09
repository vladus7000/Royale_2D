#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

enum class Language
{
    En,
    Ru
};

class LocalizationManager
{
public:
    static LocalizationManager& get();
    Language getCurrentLanguage() const { return m_language; }
    void setCurrentLanguage(Language l) { m_language = l; }

    const char* getLanguageName(Language l);
    std::string getStringForKey(const char* key);

public:
    LocalizationManager(const LocalizationManager& rhs) = delete;
    LocalizationManager(LocalizationManager&& rhs) = delete;
    LocalizationManager& operator=(const LocalizationManager& rhs) = delete;
    LocalizationManager& operator=(LocalizationManager&& rhs) = delete;

private:
    LocalizationManager();
    ~LocalizationManager();

private:
    rapidjson::Document m_document;
    Language m_language = Language::Ru;
};
