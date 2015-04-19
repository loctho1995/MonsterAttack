#ifndef __MISSION_SCENE_H__
#define __MISSION_SCENE_H__

#include "cocos2d.h"
#include "Scenes/MainScene.h"


USING_NS_CC;

class Mission : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

	void Back(Ref *pSender);

	CREATE_FUNC(Mission);
};

#endif // __HELP_SCENE_H__
