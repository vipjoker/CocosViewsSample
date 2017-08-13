#include "Box2dScene.h"
#include "GLES-Render.h"
#include "external/Box2D/Box2D.h"

USING_NS_CC;



Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->scheduleUpdate();
    
    
    b2Vec2 gravity;
    gravity.Set(0.0f, -9.8f);//No gravity
    
    world = new b2World(gravity);
    

    
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(5, 5);
    myBodyDef.angle = 0;

    b2Body* dynamicBody = world->CreateBody(&myBodyDef);



    myBodyDef.position.Set(10,5);
    b2Body *circle = world->CreateBody(&myBodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 2;
    circle->CreateFixture(&circleShape,1);




    b2PolygonShape boxShape;
    boxShape.SetAsBox(2,2);


    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.restitution = 1;
    boxFixtureDef.friction = 1;





    dynamicBody->CreateFixture(&boxFixtureDef);


    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set(0 ,1);

    b2ChainShape chainShape;
    const int size = 6;
    b2Vec2 chainVec[size];
    chainVec[0].Set(0,0);
    chainVec[1].Set(5,2);
    chainVec[2].Set(10,0);
    chainVec[3].Set(20,0);
    chainVec[4].Set(30,0);
    chainVec[5].Set(40,5);
    chainShape.CreateChain(chainVec,size);


    world->CreateBody(&groundDef)->CreateFixture(&chainShape,1);
    
    b2BodyDef bodyDef;
    m_groundBody = world->CreateBody(&bodyDef);
    



    drawNode = DrawNode::create();
    auto debugDraw = new GLESDebugDraw(32,drawNode);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
    flags += b2Draw::e_aabbBit;
    flags += b2Draw::e_pairBit;
    flags += b2Draw::e_centerOfMassBit;
    flags += b2Draw::e_aabbBit;
    debugDraw->SetFlags(flags);

    auto colorLayer = LayerColor::create(Color4B::WHITE);
    colorLayer->setContentSize(Director::getInstance()->getVisibleSize());
    drawNode->setContentSize(Director::getInstance()->getVisibleSize());
    addChild(colorLayer);
    addChild(drawNode);
    world->SetDebugDraw(debugDraw);














    EventListenerTouchOneByOne *listenerMouse = EventListenerTouchOneByOne::create();
    listenerMouse->onTouchBegan = [](Touch* touch, Event* event){
        // your code
        log("touch begun");
        return true; // if you are consuming it
    };
    listenerMouse->onTouchEnded = CC_CALLBACK_2(HelloWorld::onMouseDown,this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerMouse,this);



    return true;
}
void HelloWorld::onMouseDown(Touch *touch, Event *event) {
    Vec2 v = touch->getLocation();
    log("x = %f y = %f",v.x,v.y);

    Vec2 b = v/32;
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(b.x,b.y);
    b2Body *circle = world->CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 2;
    circle->CreateFixture(&circleShape,1);



}


void HelloWorld::update(float delta) {
    drawNode->clear();

    world->DrawDebugData();

    int velocityIterations = 8;
    int positionIterations = 3;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(delta, velocityIterations, positionIterations);
    
    // Iterate over the bodies in the physics world
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            // Synchronize the AtlasSprites position and rotation with the corresponding body
//            Sprite* myActor = (Sprite*)b->GetUserData();
//            myActor->setPosition( Vec2( b->GetPosition().x * 32, b->GetPosition().y * 32) );
//            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );}
        }
    }
}



