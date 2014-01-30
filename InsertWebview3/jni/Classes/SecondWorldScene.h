#ifndef __SECONDWORLD_SCENE_H__
#define __SECONDWORLD_SCENE_H__

#include "cocos2d.h"

class SecondWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    void menuCloseCallback(Object* pSender);
    
    CREATE_FUNC(SecondWorld);

    void openDailogInJni(Object* pSender);

    void insertOtherLayoutByResourceId(Object* pSender);

    void openOtherActivity(Object* pSender);
    void backToFirst(Object* pSender);
};

#endif // __SECONDWORLD_SCENE_H__
