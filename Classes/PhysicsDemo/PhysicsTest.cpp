#include "PhysicsTest.h"

#if CC_USE_PHYSICS

#include <cmath>
#include "ui/CocosGUI.h"
#include "PhysicsTest.h"

USING_NS_CC;

namespace
{
    Color4F STATIC_COLOR(1.0f, 0.0f, 0.0f, 1.0f);
    const int DRAG_BODYS_TAG = 0x80;
}

void PhysicsDemo::toggleDebug()
{
#if CC_USE_PHYSICS
    _debugDraw = !_debugDraw;
    _physicsWorld->setDebugDrawMask(_debugDraw ? PhysicsWorld::DEBUGDRAW_ALL : PhysicsWorld::DEBUGDRAW_NONE);
#endif
}


PhysicsDemo::PhysicsDemo()
: _spriteTexture(nullptr)
, _ball(nullptr)
, _debugDraw(false)
{
}

bool PhysicsDemo::init()
{
    Scene::init();
    return initWithPhysics();
}

PhysicsDemo::~PhysicsDemo()
{
}


void PhysicsDemo::onEnter()
{
    Scene::onEnter();
    
    _spriteTexture = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 100)->getTexture();
    
    // menu for debug layer
    MenuItemFont::setFontSize(18);
    auto item = MenuItemFont::create("Toggle debug", CC_CALLBACK_1(PhysicsDemo::toggleDebugCallback, this));
    
    auto menu = Menu::create(item, nullptr);
    this->addChild(menu);
    menu->setPosition(Vec2(VisibleRect::right().x - item->getContentSize().width / 2 - 10, VisibleRect::top().y - item->getContentSize().height / 2 - 10));
}

Sprite* PhysicsDemo::addGrossiniAtPosition(Vec2 p, float scale/* = 1.0*/)
{
    CCLOG("Add sprite %0.2f x %02.f", p.x, p.y);
    
    int posx, posy;
    
    posx = CCRANDOM_0_1() * 200.0f;
    posy = CCRANDOM_0_1() * 200.0f;
    
    posx = (posx % 4) * 85;
    posy = (posy % 3) * 121;
    
    auto sp = Sprite::createWithTexture(_spriteTexture, Rect(posx, posy, 85, 121));
    
    sp->setScale(scale);
    sp->setPosition(p);
    sp->addComponent(PhysicsBody::createBox(Size(48.0f, 108.0f)));
    this->addChild(sp);
    
    return sp;
}

void PhysicsDemo::toggleDebugCallback(Ref* /*sender*/)
{
    toggleDebug();
}

namespace
{
    const int LOGO_WIDTH = 188;
    const int LOGO_HEIGHT = 35;
    const int LOGO_RAW_LENGTH = 24;
    const int LOGO_IMAGE[] =
    {
        15, -16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, -64, 15, 63, -32, -2, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, -64, 15, 127, -125, -1, -128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 127, -64, 15, 127, 15, -1, -64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, -64, 15, -2,
        31, -1, -64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, -64, 0, -4, 63, -1, -32, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, -64, 15, -8, 127, -1, -32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, -1, -64, 0, -8, -15, -1, -32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -31, -1, -64, 15, -8, -32,
        -1, -32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, -15, -1, -64, 9, -15, -32, -1, -32, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, -15, -1, -64, 0, -15, -32, -1, -32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 63, -7, -1, -64, 9, -29, -32, 127, -61, -16, 63, 15, -61, -1, -8, 31, -16, 15, -8, 126, 7, -31,
        -8, 31, -65, -7, -1, -64, 9, -29, -32, 0, 7, -8, 127, -97, -25, -1, -2, 63, -8, 31, -4, -1, 15, -13,
        -4, 63, -1, -3, -1, -64, 9, -29, -32, 0, 7, -8, 127, -97, -25, -1, -2, 63, -8, 31, -4, -1, 15, -13,
        -2, 63, -1, -3, -1, -64, 9, -29, -32, 0, 7, -8, 127, -97, -25, -1, -1, 63, -4, 63, -4, -1, 15, -13,
        -2, 63, -33, -1, -1, -32, 9, -25, -32, 0, 7, -8, 127, -97, -25, -1, -1, 63, -4, 63, -4, -1, 15, -13,
        -1, 63, -33, -1, -1, -16, 9, -25, -32, 0, 7, -8, 127, -97, -25, -1, -1, 63, -4, 63, -4, -1, 15, -13,
        -1, 63, -49, -1, -1, -8, 9, -57, -32, 0, 7, -8, 127, -97, -25, -8, -1, 63, -2, 127, -4, -1, 15, -13,
        -1, -65, -49, -1, -1, -4, 9, -57, -32, 0, 7, -8, 127, -97, -25, -8, -1, 63, -2, 127, -4, -1, 15, -13,
        -1, -65, -57, -1, -1, -2, 9, -57, -32, 0, 7, -8, 127, -97, -25, -8, -1, 63, -2, 127, -4, -1, 15, -13,
        -1, -1, -57, -1, -1, -1, 9, -57, -32, 0, 7, -1, -1, -97, -25, -8, -1, 63, -1, -1, -4, -1, 15, -13, -1,
        -1, -61, -1, -1, -1, -119, -57, -32, 0, 7, -1, -1, -97, -25, -8, -1, 63, -1, -1, -4, -1, 15, -13, -1,
        -1, -61, -1, -1, -1, -55, -49, -32, 0, 7, -1, -1, -97, -25, -8, -1, 63, -1, -1, -4, -1, 15, -13, -1,
        -1, -63, -1, -1, -1, -23, -49, -32, 127, -57, -1, -1, -97, -25, -1, -1, 63, -1, -1, -4, -1, 15, -13,
        -1, -1, -63, -1, -1, -1, -16, -49, -32, -1, -25, -1, -1, -97, -25, -1, -1, 63, -33, -5, -4, -1, 15,
        -13, -1, -1, -64, -1, -9, -1, -7, -49, -32, -1, -25, -8, 127, -97, -25, -1, -1, 63, -33, -5, -4, -1,
        15, -13, -1, -1, -64, -1, -13, -1, -32, -49, -32, -1, -25, -8, 127, -97, -25, -1, -2, 63, -49, -13,
        -4, -1, 15, -13, -1, -1, -64, 127, -7, -1, -119, -17, -15, -1, -25, -8, 127, -97, -25, -1, -2, 63,
        -49, -13, -4, -1, 15, -13, -3, -1, -64, 127, -8, -2, 15, -17, -1, -1, -25, -8, 127, -97, -25, -1,
        -8, 63, -49, -13, -4, -1, 15, -13, -3, -1, -64, 63, -4, 120, 0, -17, -1, -1, -25, -8, 127, -97, -25,
        -8, 0, 63, -57, -29, -4, -1, 15, -13, -4, -1, -64, 63, -4, 0, 15, -17, -1, -1, -25, -8, 127, -97,
        -25, -8, 0, 63, -57, -29, -4, -1, -1, -13, -4, -1, -64, 31, -2, 0, 0, 103, -1, -1, -57, -8, 127, -97,
        -25, -8, 0, 63, -57, -29, -4, -1, -1, -13, -4, 127, -64, 31, -2, 0, 15, 103, -1, -1, -57, -8, 127,
        -97, -25, -8, 0, 63, -61, -61, -4, 127, -1, -29, -4, 127, -64, 15, -8, 0, 0, 55, -1, -1, -121, -8,
        127, -97, -25, -8, 0, 63, -61, -61, -4, 127, -1, -29, -4, 63, -64, 15, -32, 0, 0, 23, -1, -2, 3, -16,
        63, 15, -61, -16, 0, 31, -127, -127, -8, 31, -1, -127, -8, 31, -128, 7, -128, 0, 0
    };
    
    int getPixel(int x, int y)
    {
        return (LOGO_IMAGE[(x >> 3) + y * LOGO_RAW_LENGTH] >> (~x & 0x7)) & 1;
    }
    
    float frand(void)
    {
        return rand() / RAND_MAX;
    }
}

Sprite* PhysicsDemo::makeBall(Vec2 point, float radius, PhysicsMaterial material)
{
    Sprite* ball = nullptr;
    if (_ball != nullptr)
        ball = Sprite::createWithTexture(_ball->getTexture());
    else
        ball = Sprite::create("Images/ball.png");
    
    ball->setScale(0.13f * radius);
    
    ball->addComponent(PhysicsBody::createCircle(ball->getContentSize().width / 2, material));
    ball->setPosition(Vec2(point.x, point.y));
    
    return ball;
}

Sprite* PhysicsDemo::makeBox(Vec2 point, Size size, int color, PhysicsMaterial material)
{
    bool yellow = false;
    if (color == 0)
    {
        yellow = CCRANDOM_0_1() > 0.5f;
    }
    else
    {
        yellow = color == 1;
    }
    
    auto box = yellow ? Sprite::create("Images/YellowSquare.png") : Sprite::create("Images/CyanSquare.png");
    box->setScaleX(size.width / 100.0f);
    box->setScaleY(size.height / 100.0f);
    
    box->addComponent(PhysicsBody::createBox(box->getContentSize(), material));
    
    box->setPosition(Vec2(point.x, point.y));
    
    return box;
}

Sprite* PhysicsDemo::makeTriangle(Vec2 point, Size size, int color, PhysicsMaterial material)
{
    bool yellow = false;
    if (color == 0)
    {
        yellow = CCRANDOM_0_1() > 0.5f;
    }
    else
    {
        yellow = color == 1;
    }
    
    auto triangle = yellow ? Sprite::create("Images/YellowTriangle.png") : Sprite::create("Images/CyanTriangle.png");
    
    if (size.height == 0)
    {
        triangle->setScale(size.width / 100.0f);
    }
    else
    {
        triangle->setScaleX(size.width / 50.0f);
        triangle->setScaleY(size.height / 43.5f);
    }
    
    Vec2 vers[] = { Vec2(0, triangle->getContentSize().height / 2), Vec2(triangle->getContentSize().width / 2, -triangle->getContentSize().height / 2), Vec2(-triangle->getContentSize().width / 2, -triangle->getContentSize().height / 2) };
    
    triangle->addComponent(PhysicsBody::createPolygon(vers, 3, material));
    triangle->setPosition(Vec2(point.x, point.y));
    
    return triangle;
}

bool PhysicsDemo::onTouchBegan(Touch* touch, Event* event)
{
     auto location = touch->getLocation();
    auto arr = _physicsWorld->getShapes(location);
    
    PhysicsBody* body = nullptr;
    for (auto& obj : arr)
    {
        if ((obj->getBody()->getTag() & DRAG_BODYS_TAG) != 0)
        {
            body = obj->getBody();
            break;
        }
    }
    
    if (body != nullptr)
    {
        Node* mouse = Node::create();
        auto physicsBody = PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY);
        physicsBody->setDynamic(false);
        mouse->addComponent(physicsBody);
        mouse->setPosition(location);
        this->addChild(mouse);
        PhysicsJointPin* joint = PhysicsJointPin::construct(physicsBody, body, location);
        joint->setMaxForce(5000.0f * body->getMass());
        _physicsWorld->addJoint(joint);
        _mouses.insert(std::make_pair(touch->getID(), mouse));
        
        return true;
    }
    
    return false;
}

void PhysicsDemo::onTouchMoved(Touch* touch, Event* /*event*/)
{
    auto it = _mouses.find(touch->getID());
    
    if (it != _mouses.end())
    {
        it->second->setPosition(touch->getLocation());
    }
}

void PhysicsDemo::onTouchEnded(Touch* touch, Event* /*event*/)
{
    auto it = _mouses.find(touch->getID());
    
    if (it != _mouses.end())
    {
        this->removeChild(it->second);
        _mouses.erase(it);
    }
}


// implementation of PhysicsDemoJoints


void PhysicsDemoJoints::onEnter()
{
    PhysicsDemo::onEnter();
    toggleDebug();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(PhysicsDemo::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(PhysicsDemo::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(PhysicsDemo::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    float width = (VisibleRect::getVisibleRect().size.width - 10) / 4;
    float height = (VisibleRect::getVisibleRect().size.height - 50) / 4;
    
    Node* node = Node::create();
    PhysicsBody* box = PhysicsBody::create();
    node->addComponent(box);
    
    box->setDynamic(false);
    node->setPosition(Point::ZERO);
    this->addChild(node);
    
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            Vec2 offset(VisibleRect::leftBottom().x + 5 + j * width + width/2, VisibleRect::leftBottom().y + 50 + i * height + height/2);
            box->addShape(PhysicsShapeEdgeBox::create(Size(width, height), PHYSICSSHAPE_MATERIAL_DEFAULT, 1, offset));
            
            switch (i*4 + j)
            {
                case 0:
                {
                    auto sp1 = makeBall(offset - Vec2(30, 0), 10);
                    auto sp1PhysicsBody = sp1->getPhysicsBody();
                    sp1PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    auto sp2 = makeBall(offset + Vec2(30, 0), 10);
                    auto sp2PhysicsBody = sp2->getPhysicsBody();
                    sp2PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    PhysicsJointPin* joint = PhysicsJointPin::construct(sp1PhysicsBody, sp2PhysicsBody, offset);
                    getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 1:
                {
                    
                    auto sp1 = makeBall(offset - Vec2(30, 0), 10);
                    auto sp1PhysicsBody = sp1->getPhysicsBody();
                    sp1PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    auto sp2PhysicsBody = sp2->getPhysicsBody();
                    sp2PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    PhysicsJointFixed* joint = PhysicsJointFixed::construct(sp1PhysicsBody, sp2PhysicsBody, offset);
                    getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 2:
                {
                    auto sp1 = makeBall(offset - Vec2(30, 0), 10);
                    auto sp1PhysicsBody = sp1->getPhysicsBody();
                    sp1PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    auto sp2PhysicsBody = sp2->getPhysicsBody();
                    sp2PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    PhysicsJointDistance* joint = PhysicsJointDistance::construct(sp1PhysicsBody, sp2PhysicsBody, Point::ZERO, Point::ZERO);
                    getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 3:
                {
                    auto sp1 = makeBall(offset - Vec2(30, 0), 10);
                    auto sp1PhysicsBody = sp1->getPhysicsBody();
                    sp1PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    auto sp2PhysicsBody = sp2->getPhysicsBody();
                    sp2PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    PhysicsJointLimit* joint = PhysicsJointLimit::construct(sp1PhysicsBody, sp2PhysicsBody, Point::ZERO, Point::ZERO, 30.0f, 60.0f);
                    getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 4:
                {
                    auto sp1 = makeBall(offset - Vec2(30, 0), 10);
                    auto sp1PhysicsBody = sp1->getPhysicsBody();
                    sp1PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    auto sp2PhysicsBody = sp2->getPhysicsBody();
                    sp2PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    PhysicsJointSpring* joint = PhysicsJointSpring::construct(sp1PhysicsBody, sp2PhysicsBody, Point::ZERO, Point::ZERO, 500.0f, 0.3f);
                    getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 5:
                {
                    auto sp1 = makeBall(offset - Vec2(30, 0), 10);
                    auto sp1PhysicsBody = sp1->getPhysicsBody();
                    sp1PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    auto sp2PhysicsBody = sp2->getPhysicsBody();
                    sp2PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    PhysicsJointGroove* joint = PhysicsJointGroove::construct(sp1PhysicsBody, sp2PhysicsBody, Vec2(30, 15), Vec2(30, -15), Vec2(-30, 0));
                    getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 6:
                {
                    auto sp1 = makeBox(offset - Vec2(30, 0), Size(30, 10));
                    auto sp1PhysicsBody = sp1->getPhysicsBody();
                    sp1PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    auto sp2PhysicsBody = sp2->getPhysicsBody();
                    sp2PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1PhysicsBody, box, sp1->getPosition()));
                    getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp2PhysicsBody, box, sp2->getPosition()));
                    PhysicsJointRotarySpring* joint = PhysicsJointRotarySpring::construct(sp1PhysicsBody, sp2PhysicsBody, 3000.0f, 60.0f);
                    getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 7:
                {
                    auto sp1 = makeBox(offset - Vec2(30, 0), Size(30, 10));
                    auto sp1PhysicsBody = sp1->getPhysicsBody();
                    sp1PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    auto sp2PhysicsBody = sp2->getPhysicsBody();
                    sp2PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1PhysicsBody, box, sp1->getPosition()));
                    getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp2PhysicsBody, box, sp2->getPosition()));
                    PhysicsJointRotaryLimit* joint = PhysicsJointRotaryLimit::construct(sp1PhysicsBody, sp2PhysicsBody, 0.0f,(float) M_PI_2);
                    getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 8:
                {
                    auto sp1 = makeBox(offset - Vec2(30, 0), Size(30, 10));
                    auto sp1PhysicsBody = sp1->getPhysicsBody();
                    sp1PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    auto sp2PhysicsBody = sp2->getPhysicsBody();
                    sp2PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1PhysicsBody, box, sp1->getPosition()));
                    getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp2PhysicsBody, box, sp2->getPosition()));
                    PhysicsJointRatchet* joint = PhysicsJointRatchet::construct(sp1PhysicsBody, sp2PhysicsBody, 0.0f, (float)M_PI_2);
                    getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 9:
                {
                    auto sp1 = makeBox(offset - Vec2(30, 0), Size(30, 10));
                    auto sp1PhysicsBody = sp1->getPhysicsBody();
                    sp1PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    auto sp2PhysicsBody = sp2->getPhysicsBody();
                    sp2PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1PhysicsBody, box, sp1->getPosition()));
                    getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp2PhysicsBody, box, sp2->getPosition()));
                    PhysicsJointGear* joint = PhysicsJointGear::construct(sp1PhysicsBody, sp2PhysicsBody, 0.0f, 2.0f);
                    getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 10:
                {
                    auto sp1 = makeBox(offset - Vec2(30, 0), Size(30, 10));
                    auto sp1PhysicsBody = sp1->getPhysicsBody();
                    sp1PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    auto sp2PhysicsBody = sp2->getPhysicsBody();
                    sp2PhysicsBody->setTag(DRAG_BODYS_TAG);
                    
                    getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1PhysicsBody, box, sp1->getPosition()));
                    getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp2PhysicsBody, box, sp2->getPosition()));
                    PhysicsJointMotor* joint = PhysicsJointMotor::construct(sp1PhysicsBody, sp2PhysicsBody, (float)M_PI_2);
                    getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                default:
                    break;
            }
        }
    }
}





















































































void PhysicsDemoPump::onEnter()
{
    PhysicsDemo::onEnter();
    toggleDebug();
    
    _distance = 0.0f;
    _rotationV = 0.0f;
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PhysicsDemoPump::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PhysicsDemoPump::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PhysicsDemoPump::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    scheduleUpdate();
    
    auto node = Node::create();
    auto nodeBody = PhysicsBody::create();
    node->addComponent(nodeBody);
    nodeBody->setDynamic(false);
    
    PhysicsMaterial staticMaterial(PHYSICS_INFINITY, 0, 0.5f);
    nodeBody->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(50, 0), VisibleRect::leftTop() + Vec2(50, -130), staticMaterial, 2.0f));
    nodeBody->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(190, 0), VisibleRect::leftTop() + Vec2(100, -50), staticMaterial, 2.0f));
    nodeBody->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(100, -50), VisibleRect::leftTop() + Vec2(100, -90), staticMaterial, 2.0f));
    nodeBody->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(50, -130), VisibleRect::leftTop() + Vec2(100, -145), staticMaterial, 2.0f));
    nodeBody->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(100, -145), VisibleRect::leftBottom() + Vec2(100, 80), staticMaterial, 2.0f));
    nodeBody->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(150, -80), VisibleRect::leftBottom() + Vec2(150, 80), staticMaterial, 2.0f));
    nodeBody->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(150, -80), VisibleRect::rightTop() + Vec2(-100, -150), staticMaterial, 2.0f));
    
    nodeBody->setCategoryBitmask(0x01);
    node->setPosition(Vec2::ZERO);
    this->addChild(node);
    
    // balls
    for (int i = 0; i < 6; ++i)
    {
        auto ball = makeBall(VisibleRect::leftTop() + Vec2(75 + CCRANDOM_0_1() * 90, 0), 22, PhysicsMaterial(0.05f, 0.0f, 0.1f));
        ball->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
        addChild(ball);
    }
    
    Vec2 vec[4] =
    {
        VisibleRect::leftTop() + Vec2(102, -148),
        VisibleRect::leftTop() + Vec2(148, -161),
        VisibleRect::leftBottom() + Vec2(148, 20),
        VisibleRect::leftBottom() + Vec2(102, 20)
    };
    
    // pump
    auto pump = Node::create();
    auto center = PhysicsShape::getPolygonCenter(vec, 4);
    pump->setPosition(center);
    auto pumpBody = PhysicsBody::createPolygon(vec, 4, PHYSICSBODY_MATERIAL_DEFAULT, -center);
    pump->addComponent(pumpBody);
    this->addChild(pump);
    pumpBody->setCategoryBitmask(0x02);
    pumpBody->setGravityEnable(false);
    
    // small gear 
    auto sgearBody = PhysicsBody::createCircle(44);
    sgearBody->setCategoryBitmask(0x04);
    sgearBody->setCollisionBitmask(0x04);
    sgearBody->setTag(1);
    auto sgear = Node::create();
    sgear->addComponent(sgearBody);
    sgear->setPosition(VisibleRect::leftBottom() + Vec2(125, 0));
    this->addChild(sgear);
    
    _physicsWorld->addJoint(PhysicsJointPin::construct(nodeBody, sgearBody, sgear->getPosition()));
    _physicsWorld->addJoint(PhysicsJointDistance::construct(pumpBody, sgearBody, Vec2(0, 0), Vec2(0, -44)));
    
    // big gear 
    auto bgearBody = PhysicsBody::createCircle(100);
    bgearBody->setCategoryBitmask(0x04);
    auto bgear = Node::create();
    bgear->addComponent(bgearBody);
    bgear->setPosition(VisibleRect::leftBottom() + Vec2(275, 0));
    this->addChild(bgear);
    
    _physicsWorld->addJoint(PhysicsJointPin::construct(bgearBody, nodeBody, bgear->getPosition()));
    _physicsWorld->addJoint(PhysicsJointGear::construct(sgearBody, bgearBody, (float)-M_PI_2, -2.0f));
    
    // plugger
    Vec2 seg[] = { VisibleRect::leftTop() + Vec2(75, -120), VisibleRect::leftBottom() + Vec2(75, -100) };
    Vec2 segCenter = (seg[1] + seg[0]) / 2;
    seg[1] -= segCenter;
    seg[0] -= segCenter;
    
    auto pluggerBody = PhysicsBody::createEdgeSegment(seg[0], seg[1], PhysicsMaterial(0.01f, 0.0f, 0.5f), 20);
    pluggerBody->setDynamic(true);
    pluggerBody->setMass(30);
    pluggerBody->setMoment(100000);
    pluggerBody->setCategoryBitmask(0x02);
    auto plugger = Node::create();
    plugger->addComponent(pluggerBody);
    plugger->setPosition(segCenter);
    this->addChild(plugger);
    
    sgearBody->setCollisionBitmask(0x04 | 0x01);
    _physicsWorld->addJoint(PhysicsJointPin::construct(nodeBody, pluggerBody, VisibleRect::leftBottom() + Vec2(75, -90)));
    _physicsWorld->addJoint(PhysicsJointDistance::construct(pluggerBody, sgearBody, Vec2::ZERO, Vec2(44, 0)));
}

void PhysicsDemoPump::update(float delta)
{
    for (const auto& body : _physicsWorld->getAllBodies())
    {
        if (body->getTag() == DRAG_BODYS_TAG && body->getPosition().y < 0.0f)
        {
            if (body->getNode()!=nullptr)
            {
                body->getNode()->setPosition(VisibleRect::leftTop() + Vec2(75 + CCRANDOM_0_1() * 90, 0));
            }
            
            body->setVelocity(Vec2(0, 0));
        }
    }
    
    PhysicsBody* gear = _physicsWorld->getBody(1);
    
    if (gear != nullptr)
    {
        if (_distance != 0.0f)
        {
            _rotationV += _distance / 2500.0f;
            
            if (_rotationV > 30) _rotationV = 30.0f;
            if (_rotationV < -30) _rotationV = -30.0f;
        }
        
        gear->setAngularVelocity(_rotationV);
        _rotationV *= 0.995f;
    }
}

bool PhysicsDemoPump::onTouchBegan(Touch* touch, Event* event)
{
    PhysicsDemo::onTouchBegan(touch, event);
    
    _distance = touch->getLocation().x - VisibleRect::center().x;
    
    return true;
}

void PhysicsDemoPump::onTouchMoved(Touch* touch, Event* event)
{
    PhysicsDemo::onTouchMoved(touch, event);
    
    _distance = touch->getLocation().x - VisibleRect::center().x;
}

void PhysicsDemoPump::onTouchEnded(Touch* touch, Event* event)
{
    PhysicsDemo::onTouchEnded(touch, event);
    
    _distance = 0;
}



void PhysicsDemoSlice::onEnter()
{
    PhysicsDemo::onEnter();
    toggleDebug();
    
    _sliceTag = 1;
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [](Touch* /*touch*/, Event* /*event*/)->bool{ return true; };
    touchListener->onTouchEnded = CC_CALLBACK_2(PhysicsDemoSlice::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto ground = Node::create();
    ground->addComponent(PhysicsBody::createEdgeSegment(VisibleRect::leftBottom() + Vec2(0, 50), VisibleRect::rightBottom() + Vec2(0, 50)));
    this->addChild(ground);
    
    auto box = Node::create();
    Vec2 points[4] = {Vec2(-100, -100), Vec2(-100, 100), Vec2(100, 100), Vec2(100, -100)};
    box->addComponent(PhysicsBody::createPolygon(points, 4));
    box->setPosition(VisibleRect::center());
    box->getPhysicsBody()->setTag(_sliceTag);
    addChild(box);
}

bool PhysicsDemoSlice::slice(PhysicsWorld &/*world*/, const PhysicsRayCastInfo& info, void* /*data*/)
{
    if (info.shape->getBody()->getTag() != _sliceTag)
    {
        return true;
    }
    
    if (!info.shape->containsPoint(info.start) && !info.shape->containsPoint(info.end))
    {
        Vec2 normal = info.end - info.start;
        normal = normal.getPerp().getNormalized();
        float dist = info.start.dot(normal);
        
        clipPoly(dynamic_cast<PhysicsShapePolygon*>(info.shape), normal, dist);
        clipPoly(dynamic_cast<PhysicsShapePolygon*>(info.shape), -normal, -dist);
        
        info.shape->getBody()->removeFromWorld();
    }
    
    return true;
}

void PhysicsDemoSlice::clipPoly(PhysicsShapePolygon* shape, Vec2 normal, float distance)
{
    PhysicsBody* body = shape->getBody();
    int count = shape->getPointsCount();
    int pointsCount = 0;
    Vec2* points = new (std::nothrow) Vec2[count + 1];
    
    for (int i=0, j=count-1; i<count; j=i, ++i)
    {
        Vec2 a = body->local2World(shape->getPoint(j));
        float aDist = a.dot(normal) - distance;
        
        if (aDist < 0.0f)
        {
            points[pointsCount] = a;
            ++pointsCount;
        }
        
        Vec2 b = body->local2World(shape->getPoint(i));
        float bDist = b.dot(normal) - distance;
        
        if (aDist*bDist < 0.0f)
        {
            float t = std::fabs(aDist)/(std::fabs(aDist) + std::fabs(bDist));
            points[pointsCount] = a.lerp(b, t);
            ++pointsCount;
        }
    }
    
    Vec2 center = PhysicsShape::getPolygonCenter(points, pointsCount);
    Node* node = Node::create();
    PhysicsBody* polygon = PhysicsBody::createPolygon(points, pointsCount, PHYSICSBODY_MATERIAL_DEFAULT, -center);
    node->setPosition(center);
    node->addComponent(polygon);
    polygon->setVelocity(body->getVelocityAtWorldPoint(center));
    polygon->setAngularVelocity(body->getAngularVelocity());
    polygon->setTag(_sliceTag);
    addChild(node);
    
    delete[] points;
}

void PhysicsDemoSlice::onTouchEnded(Touch *touch, Event* /*event*/)
{
    auto func = CC_CALLBACK_3(PhysicsDemoSlice::slice, this);
    getPhysicsWorld()->rayCast(func, touch->getStartLocation(), touch->getLocation(), nullptr);
}





#endif
