//
// Created by oleh on 18.07.17.
//

#include <cocos/ui/UIPageViewIndicator.h>
#include "MenuScene.h"

using namespace ui;
typedef ui::Layout::Type ltype;

bool MenuScene::init() {
    if (!Layer::init()) {
        return false;
    }
    this->setupToolbar();
    auto size = Director::getInstance()->getVisibleSize();
    pageView = ui::PageView::create();
//    auto indicator = PageViewIndicator::create();
    pageView->setIndicatorEnabled(true);
    pageView->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    pageView->setIndicatorSelectedIndexColor(Color3B::WHITE);
    pageView->setContentSize(size);
    pageView->setIndicatorIndexNodesScale(0.5);
    pageView->setIndicatorSpaceBetweenIndexNodes(5);
    pageView->addPage(this->createPage(1));
    pageView->addPage(this->createPage(21));
    pageView->addPage(this->createPage(41));
    this->addChild(pageView);


    return true;
}


Scene *MenuScene::createScene() {
    auto scene = Scene::create();
    MenuScene *layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}


void MenuScene::setupToolbar() {

    Size size = Director::getInstance()->getVisibleSize();
    Layout *layout = Layout::create();
    layout->setContentSize(Size(size.width, 70));
    layout->setPosition(Vec2(0, size.height));
    layout->setAnchorPoint(Vec2(0, 1));
//    layout->setBackGroundColorType(Layout::BackGroundColorType::GRADIENT);
//    layout->setBackGroundColor(Color3B::BLUE,Color3B::RED);
    addChild(layout,3);
    Button *btn = Button::create("arrow.png");
    btn->setPositionType(Widget::PositionType::PERCENT);
    btn->setScale(-0.3f,0.3f);
    btn->setPositionPercent(Vec2(.1,.5));
    btn->addClickEventListener(CC_CALLBACK_1(MenuScene::onBackClicked,this));
    layout->addChild(btn);

}

ui::Layout *MenuScene::createPage(int startIndex) {
    Size size = Director::getInstance()->getVisibleSize();

    auto layout = ui::Layout::create();
    layout->setBackGroundColor(Color3B(1, 7, 39), Color3B(9, 48, 103));
    layout->setBackGroundColorType(ui::Layout::BackGroundColorType::GRADIENT);
//    layout->setLayoutType(ltype::VERTICAL);
    LinearLayoutParameter *p = LinearLayoutParameter::create();
    p->setMargin(Margin(10, 10, 10, 10));
    p->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
    auto gridContainer = Node::create();


    for (float i = 1; i > 0.2f; i = i - 0.2f)
        for (float j = 0.2f; j < 1; j = j + 0.2f) {
            auto button = Button::create("menu_item.png");
            button->setAnchorPoint(Vec2(.5, .5));

            button->setPosition(Vec2(j * size.width, i * size.width));
            button->addClickEventListener(CC_CALLBACK_1(MenuScene::onMenuItemClicked, this));
            button->setTag(startIndex);
            button->setTitleText(std::to_string(startIndex++));

            button->setTitleFontSize(40);
            button->setTitleFontName("fonts/Marker.ttf");
            gridContainer->addChild(button);
        }

    float diff = size.height - size.width;
    gridContainer->setPosition(0, diff / 2);

    layout->addChild(gridContainer);


    return layout;
}

void MenuScene::onMenuItemClicked(Ref *ref) {
    auto button = dynamic_cast<ui::Button*>(ref);
    int tag = button->getTag();
    std::stringstream ss;
    ss << "Item tag "  << tag;
    log(ss.str().c_str());
}

void MenuScene::onBackClicked(Ref *ref) {
    Director::getInstance()->popScene();
}

