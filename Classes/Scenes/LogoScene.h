#ifndef __LOGOSCREEN_SCENE_H__
#define __LOGOSCREEN_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class LogoScreen : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

	void update(float dt) override;

	void loadResource();

	float _time;

	bool _loadResource;

	CREATE_FUNC(LogoScreen);
};

#endif // __LOGOSCREEN_SCENE_H__
