//
// Created by oleh on 04.08.17.
//

#ifndef MYGAME_CUSTOMMENUBUTTON_H
#define MYGAME_CUSTOMMENUBUTTON_H

#include "cocos2d.h"
USING_NS_CC;
class CustomMenuButton:public Node {

    DrawNode *drawNode;
    Label *label;
public:
    virtual bool init() override;
    virtual void onEnter() override;
    CREATE_FUNC(CustomMenuButton);
};


#endif //MYGAME_CUSTOMMENUBUTTON_H
