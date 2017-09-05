//
// Created by oleh on 04.08.17.
//

#ifndef MYGAME_CUSTOMMENUBUTTON_H
#define MYGAME_CUSTOMMENUBUTTON_H

#include "cocos2d.h"
#include "Scenes/StartScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class UiNode:public Node {

    Node *dialog;
    CC_SYNTHESIZE(bool,isOpen,IsOpen);
    CC_SYNTHESIZE(LayerColor*,dialogLayer,DialogLayer);
    CC_SYNTHESIZE(Button*,btnBack,BtnBack);
    CC_SYNTHESIZE(Button*, btnSettings,BtnSettings);


    void setupButtons();
public:
    virtual bool init() override;
    virtual void onEnter() override;
    void openDialog();
    void closeDialog();
    CREATE_FUNC(UiNode);
};


#endif //MYGAME_CUSTOMMENUBUTTON_H
