#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class PreLandingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void update(float delta) override;

    CREATE_FUNC(PreLandingScene);

private:
    cocos2d::ui::LoadingBar* m_loadingBar;
    cocos2d::Vec2 m_startCoord = { 0.0f, 0.0f };
    float m_selectTimer = 0.0f;
    const float m_timeToSelect = 7.0f;
    bool m_selected = false;
};