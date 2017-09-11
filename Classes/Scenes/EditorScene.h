//
// Created by omak on 07.09.17.
//

#ifndef MYGAME_EDITORSCENE_H
#define MYGAME_EDITORSCENE_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class EditorScene :public Layer{
public:
    bool init();
    CREATE_FUNC(EditorScene);
    static Scene *createScene();

};


#endif //MYGAME_EDITORSCENE_H
