#pragma once

#include <map>

#include "cocos2d.h"
#include "VisibleRect.h"
#if CC_USE_PHYSICS


//DEFINE_TEST_SUITE(PhysicsTests);
USING_NS_CC;
class PhysicsDemo : public Scene
{
public:
    PhysicsDemo();
    virtual ~PhysicsDemo();
    
    virtual bool init() override;
    virtual void onEnter() override;

    void toggleDebugCallback(cocos2d::Ref* sender);
    
    cocos2d::Sprite* addGrossiniAtPosition(cocos2d::Vec2 p, float scale = 1.0);
    cocos2d::Sprite* makeBall(cocos2d::Vec2 point, float radius, cocos2d::PhysicsMaterial material = cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
    cocos2d::Sprite* makeBox(cocos2d::Vec2 point, cocos2d::Size size, int color = 0, cocos2d::PhysicsMaterial material = cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
    cocos2d::Sprite* makeTriangle(cocos2d::Vec2 point, cocos2d::Size size, int color = 0, cocos2d::PhysicsMaterial material = cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void toggleDebug();
    
protected:
    
    cocos2d::Texture2D* _spriteTexture;
    cocos2d::SpriteBatchNode* _ball;
    std::unordered_map<int, cocos2d::Node*> _mouses;
    bool _debugDraw;
};


class PhysicsDemoJoints : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoJoints);
    
    void onEnter() override;
};

class PhysicsDemoPump : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoPump);
    
    void onEnter() override;
    void update(float delta) override;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
private:
    float _distance;
    float _rotationV;
};

class PhysicsDemoSlice : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoSlice);
    
    void onEnter() override;

    bool slice(cocos2d::PhysicsWorld& world, const cocos2d::PhysicsRayCastInfo& info, void* data);
    void clipPoly(cocos2d::PhysicsShapePolygon* shape, cocos2d::Vec2 normal, float distance);
    
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
private:
    int _sliceTag;
};


#endif // #if CC_USE_PHYSICS