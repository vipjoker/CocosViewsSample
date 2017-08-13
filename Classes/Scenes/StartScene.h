//
// Created by oleh on 03.08.17.
//

#ifndef PROJ_ANDROID_STUDIO_STARTSCENE_H
#define PROJ_ANDROID_STUDIO_STARTSCENE_H

#include "cocos2d.h"
USING_NS_CC;
class StartScene :public Layer{

    void setupButton();

public:
    static Scene *createScene();
    bool init();
    CREATE_FUNC(StartScene);

};


#endif //PROJ_ANDROID_STUDIO_STARTSCENE_H
