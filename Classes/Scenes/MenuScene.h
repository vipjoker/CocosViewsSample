//
// Created by oleh on 18.07.17.
//

#ifndef PROJ_ANDROID_STUDIO_MENUSCENE_H
#define PROJ_ANDROID_STUDIO_MENUSCENE_H

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "PhysicsScene.h"
#include <string>
USING_NS_CC;
class MenuScene :public Layer{
    ui::PageView *pageView;
    CREATE_FUNC(MenuScene);
    ui::Layout *createPage(int startIndex);
    void setupToolbar();

    bool init();
public:
    static Scene *createScene();
    void onBackClicked(Ref *ref);
    void onMenuItemClicked(Ref *ref);
};


#endif //PROJ_ANDROID_STUDIO_MENUSCENE_H
