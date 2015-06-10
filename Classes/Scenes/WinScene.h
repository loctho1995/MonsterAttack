#ifndef __WIN_SCENE_H__
#define __WIN_SCENE_H__

#include "cocos2d.h"
#include "MainScene.h"
#include "WorldMap.h"
#include "Scenes\GamePlayScene.h"

USING_NS_CC;

class Win : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

	void Next(Ref* pSender);
	void Restart(Ref *pSender);
	void BacktoMenu(Ref *pSender);
	
	CREATE_FUNC(Win);
};

#endif // __WIN_SCENE_H__
