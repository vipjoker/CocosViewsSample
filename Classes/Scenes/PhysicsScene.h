//
// Created by oleh on 18.07.17.
//

#ifndef PROJ_ANDROID_STUDIO_PHYSICSSCENE_H
#define PROJ_ANDROID_STUDIO_PHYSICSSCENE_H

#include "cocos2d.h"
USING_NS_CC;
class PhysicsScene : public Layer {
    PhysicsBody *circle;
    TMXTiledMap *tiles;
    DrawNode *drawNode;
public:
    CREATE_FUNC(PhysicsScene);
    bool init();
    PhysicsWorld *world;
    void setPhysicsWorld(PhysicsWorld *_world){world = _world;}
    static Scene *createScene();
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    bool onTouchUp(Touch *touch,Event *unusedEvent);
};


#endif //PROJ_ANDROID_STUDIO_PHYSICSSCENE_H
