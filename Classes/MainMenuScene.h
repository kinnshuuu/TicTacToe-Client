#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;

using namespace ui;

USING_NS_CC_EXT;

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainMenuScene);
private:
    void touchEvent(Ref *sender, Widget::TouchEventType type);
};
