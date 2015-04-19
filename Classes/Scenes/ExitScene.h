#ifndef __EXIT_SCENE_H__
#define __EXIT_SCENE_H__

#include "cocos2d.h"
#include "Scenes/MainScene.h"


USING_NS_CC;

class Exit : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();
	void Accept(Ref *pSender);
	void X(Ref *pSender);

	CREATE_FUNC(Exit);
};

#endif // __EXIT_SCENE_H__
