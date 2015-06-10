#ifndef __LOSE_SCENE_H__
#define __LOSE_SCENE_H__

#include "cocos2d.h"
#include "MainScene.h"
#include "WorldMap.h"
#include "Scenes\GamePlayScene.h"

USING_NS_CC;

class Lose : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

	void Restart(Ref *pSender);
	void BacktoMenu(Ref *pSender);
	
	CREATE_FUNC(Lose);
};

#endif // __LOSE_SCENE_H__
