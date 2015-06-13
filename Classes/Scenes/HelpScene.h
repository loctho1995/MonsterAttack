#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"
#include "Scenes/MainScene.h"


USING_NS_CC;

class Help : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

	void onTouchEnded (cocos2d::Touch* touches, cocos2d::Event* event);
	void onTouchMoved (cocos2d::Touch* touches, cocos2d::Event* event);
	bool onTouchBegan (cocos2d::Touch* touches, cocos2d::Event* event);

	void Back(Ref *pSender);

	CREATE_FUNC(Help);

private:
	Sprite *m_help1, *m_help2;
};

#endif // __HELP_SCENE_H__
