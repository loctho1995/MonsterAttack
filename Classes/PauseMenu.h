#ifndef __PAUSE_MENU_H__
#define __PAUSE_MENU_H__

#include "cocos2d.h"
#include "Scenes/MainScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class PauseMenu : public Menu
{

public:
	typedef void (*PauseMenu::funcResume)(Ref*);
	void initMenu();
	void Restart(Ref *pSender);
	void Selectlvl(Ref* pSender);
	void BacktoMenu(Ref *pSender);
	void Resume(Ref* pSender);
	void setResumeFunc(funcResume func);
	static PauseMenu* getInstance();	

private:
	static PauseMenu *m_instance;
	funcResume m_funcPtr;
	PauseMenu();
};

#endif // __ABOUT_SCENE_H__
