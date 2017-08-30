//
// Created by oleh on 04.08.17.
//

#ifndef MYGAME_CUSTOMMENUBUTTON_H
#define MYGAME_CUSTOMMENUBUTTON_H

#include "cocos2d.h"
#include "Scenes/StartScene.h"
USING_NS_CC;
class UiNode:public Node {

    DrawNode *drawNode;
    Label *label;
    LayerColor *colorLayer;

    void onBackPressed(Ref *ref);
    void onSettingsPressed(Ref *ref);
    void setupButtons();
public:
    virtual bool init() override;
    virtual void onEnter() override;

    CREATE_FUNC(UiNode);
};


#endif //MYGAME_CUSTOMMENUBUTTON_H
