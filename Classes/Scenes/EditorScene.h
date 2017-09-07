//
// Created by omak on 07.09.17.
//

#ifndef MYGAME_EDITORSCENE_H
#define MYGAME_EDITORSCENE_H

#include "cocos2d.h"
USING_NS_CC;
class EditorScene :public Layer{
public:
    bool init();
    CREATE_FUNC(EditorScene);
    static Scene *createScene();

    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
    virtual void onTouchMoved(Touch *touch, Event *unused_event) override;
    virtual void onTouchEnded(Touch *touch, Event *unused_event) override;
};


#endif //MYGAME_EDITORSCENE_H
