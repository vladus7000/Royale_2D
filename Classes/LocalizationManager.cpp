#include "LocalizationManager.hpp"
#include <map>

using namespace rapidjson;

USING_NS_CC;

LocalizationManager::LocalizationManager()
{
    std::string filename("localization.json");
    Data d = FileUtils::getInstance()->getDataFromFile(filename);
    m_document.Parse((char*)d.getBytes(), d.getSize());
}

LocalizationManager::~LocalizationManager()
{
}

LocalizationManager& LocalizationManager::get()
{
    static LocalizationManager mgr;
    return mgr;
}

const char* LocalizationManager::getLanguageName(Language l)
{
    static std::map<Language, const char*> m = { {Language::En, "en"}, {Language::Ru, "ru"} };
    return m[l];
}

std::string LocalizationManager::getStringForKey(const char* key)
{
    const auto& localized = m_document[getLanguageName(m_language)];
    auto it = localized.FindMember(key);
    if (it != localized.MemberEnd())
    {
        return it->value.GetString();
    }
    else
    {
        return std::string("#") + key;
    }
}
