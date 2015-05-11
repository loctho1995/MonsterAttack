#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "WorldMap.h"
#include "Scenes/AboutScene.h"
#include "Scenes/HelpScene.h"
#include "Mission.h"
#include "Scenes/ExitScene.h"


USING_NS_CC;

#if CC_TARGET_PLATFORM != CC_PLATFORM_WP8
class MainMenu : public cocos2d::Layer
#else
class MainMenu : public cocos2d::Layer, BackButtonPressed
#endif
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

	void Play(Ref *pSender);

	void Continue(Ref *pSender);

	void Mission(Ref *pSender);

	void About(Ref *pSender);

	void Help(Ref *pSender);

	void Exit(Ref *pSender);

	static void DisableMenu();

	static void EnableMenu();

private:
	static Menu *menu;


	CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__
