//
// Created by omak on 07.09.17.
//

#ifndef MYGAME_EDITORSCENE_H
#define MYGAME_EDITORSCENE_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CustomNodes/Shape.h"
USING_NS_CC;

struct EditRect{
    Rect rect;
    bool isPressed;
};


class EditorScene :public Layer{
    Vector<Shape*> shapes;
    DrawNode *drawNode;
    std::vector<EditRect> rects;
public:
    bool init();
    CREATE_FUNC(EditorScene);
    static Scene *createScene();
    void update(float dt);

};


#endif //MYGAME_EDITORSCENE_H
