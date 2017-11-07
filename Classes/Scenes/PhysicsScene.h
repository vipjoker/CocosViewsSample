//
// Created by oleh on 18.07.17.
//

#ifndef PROJ_ANDROID_STUDIO_PHYSICSSCENE_H
#define PROJ_ANDROID_STUDIO_PHYSICSSCENE_H

#include "cocos2d.h"
#include "CustomNodes/UiNode.h"
#include "PhysicsDemo/PhysicsTest.h"
#include <time.h>
#include <CustomNodes/Ball.h>

USING_NS_CC;

namespace
{
    Color4F STATIC_COLOR(1.0f, 0.0f, 0.0f, 1.0f);
    const int DRAG_BODYS_TAG = 0x80;
}


class PhysicsScene : public Layer{
    clock_t lastTime;
    Node *gameRoot;
    UiNode *uiNode;
    PhysicsBody *circle;
    TMXTiledMap *tiles;
    DrawNode *drawNode;
    Ball *colorBall;
    Vec2 *lastTouch;
    std::unordered_map<int, cocos2d::Node*> _mouses;
public:
    CREATE_FUNC(PhysicsScene);
    bool init();
    PhysicsWorld *world;
    virtual void update(float dt);
    void setPhysicsWorld(PhysicsWorld *_world){world = _world;}
    static Scene *createScene();
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    void parseTmx();

    void onBackPressed(Ref *ref);
    void onSettingsPressed(Ref *ref);

    void touchUp(Touch *touch,Event *unusedEvent);
    bool touchDown(Touch *touch, Event *unusedEvent);
    void touchMove(Touch *touch,Event *unusedEvent);
    void touchCanceled(Touch *touch,Event *unusedEvent);
};

#endif