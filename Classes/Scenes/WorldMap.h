#ifndef __WORLDMAP_SCENE_H__
#define __WORLDMAP_SCENE_H__

#include "cocos2d.h"
#include "Scenes/MainScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class WorldMap : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

	void Back(Ref *pSender);

	void level(Ref *pSender);

	CREATE_FUNC(WorldMap);
};

#endif // __WORLDMAP_SCENE_H__
