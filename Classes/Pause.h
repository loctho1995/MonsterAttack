#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"
#include "MainMenu.h"
#include "WorldMap.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class Pause : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

	void Resume(Ref* pSender);
	void Restart(Ref *pSender);
	void Selectlvl(Ref* pSender);
	void BacktoMenu(Ref *pSender);

	CREATE_FUNC(Pause);
};

#endif // __ABOUT_SCENE_H__
