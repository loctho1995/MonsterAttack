#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"
#include "MainMenu.h"


USING_NS_CC;

class Help : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

	void Back(Ref *pSender);

	CREATE_FUNC(Help);
};

#endif // __HELP_SCENE_H__
