//
// Created by oleh on 07.08.17.
//

#ifndef MYGAME_LETTERNODE_H
#define MYGAME_LETTERNODE_H

#include "cocos2d.h"
USING_NS_CC;

class LetterNode :public Sprite{
std::string *letterName;
public:
    LetterNode();
    ~LetterNode();
    virtual bool init() override;
    bool onTouchDown(Touch *touch,Event *event);
    static LetterNode *createWithFileAndName(const std::string &fileName, std::string *letterName);
};


#endif
