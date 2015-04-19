#include "PauseMenu.h"
#include "Player.h"
#include "cocos2d.h"

USING_NS_CC;
PauseMenu* PauseMenu::m_instance = 0;

PauseMenu::PauseMenu()
{
	initMenu();	
}

PauseMenu* PauseMenu::getInstance()
{
	if(!m_instance)
	{
		m_instance = new PauseMenu();		
		m_instance->setResumeFunc(&PauseMenu::Resume);
		return m_instance;
	}
	else 
		return m_instance;
}

void PauseMenu::initMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *paused = Sprite::create("/Pause/PauseSprite.png");
	paused->setScaleX(visibleSize.height / 2 * 1.5 / paused->getContentSize().height);
	paused->setScaleY(visibleSize.height / 2 * 1.5 / paused->getContentSize().width);
	paused->setPosition(visibleSize.width / 2, visibleSize.height / 2);	

	Sprite *resumeIcon = Sprite::create("/Pause/Playbtp.png");
	Sprite *restartIcon = Sprite::create("/Pause/Restartbtp.png");
	Sprite *selectlvlIcon = Sprite::create("/Pause/LvlSelectbtp.png");
	Sprite *backtomenuIcon = Sprite::create("/Pause/MainMenubtp.png");

	resumeIcon->setPosition(visibleSize.width / 2 - paused->getContentSize().width / 4, visibleSize.height / 2 + paused->getContentSize().height /6);
	restartIcon->setPosition(visibleSize.width / 2 - paused->getContentSize().width / 4, visibleSize.height / 2);
	selectlvlIcon->setPosition(visibleSize.width / 2 - paused->getContentSize().width / 4, visibleSize.height / 2 - paused->getContentSize().height /6 );
	backtomenuIcon->setPosition(visibleSize.width / 2 - paused->getContentSize().width / 4, visibleSize.height / 2 - paused->getContentSize().height /6 * 2);

	resumeIcon->setScale( paused->getContentSize().height / 7 / resumeIcon->getContentSize().width);
	restartIcon->setScale( paused->getContentSize().height / 7 / restartIcon->getContentSize().width);
	selectlvlIcon->setScale( paused->getContentSize().height / 7 / selectlvlIcon->getContentSize().width);
	backtomenuIcon->setScale( paused->getContentSize().height / 7 / backtomenuIcon->getContentSize().width);

	MenuItemImage *resume = MenuItemImage::create("/Pause/Resume.png", "/Pause/ResumeSelected.png", CC_CALLBACK_1(PauseMenu::Resume, m_instance));
	MenuItemImage *restart = MenuItemImage::create("/Pause/Restart.png", "/Pause/RestartSelected.png", CC_CALLBACK_1(PauseMenu::Restart,m_instance));
	MenuItemImage *selectlvl = MenuItemImage::create("/Pause/Selectlvl.png", "/Pause/SelectlvlSelected.png", CC_CALLBACK_1(PauseMenu::Selectlvl,m_instance));
	MenuItemImage *backtomenu = MenuItemImage::create("/Pause/BacktoMenu.png", "/Pause/BacktoMenuSelected.png", CC_CALLBACK_1(PauseMenu::BacktoMenu,m_instance));

	//resume->setScaleX(paused->getContentSize().height / 7 / resume->getContentSize().width);
	resume->setScaleY(paused->getContentSize().height / 9 / resume->getContentSize().height);
	//restart->setScaleX(paused->getContentSize().height / 7 / restart->getContentSize().width);
	restart->setScaleY(paused->getContentSize().height / 9 / restart->getContentSize().height);
	//selectlvl->setScaleX(paused->getContentSize().height / 7 / selectlvl->getContentSize().width);
	selectlvl->setScaleY(paused->getContentSize().height / 9 / selectlvl->getContentSize().height);
	//backtomenu->setScaleX(paused->getContentSize().height / 7 / backtomenu->getContentSize().width);
	backtomenu->setScaleY(paused->getContentSize().height / 9 / backtomenu->getContentSize().height);

	Vec2 point;
	point.setPoint(0, 0.5);
	resume->setAnchorPoint(point);
	restart->setAnchorPoint(point);
	selectlvl->setAnchorPoint(point);
	backtomenu->setAnchorPoint(point);

	resume->setPosition(visibleSize.width / 2 - resumeIcon->getContentSize().width, visibleSize.height / 2 + paused->getContentSize().height /6);
	restart->setPosition(visibleSize.width / 2 - resumeIcon->getContentSize().width, visibleSize.height / 2);
	selectlvl->setPosition(visibleSize.width / 2 - resumeIcon->getContentSize().width, visibleSize.height / 2 - paused->getContentSize().height /6);
	backtomenu->setPosition(visibleSize.width / 2 - resumeIcon->getContentSize().width, visibleSize.height / 2 - paused->getContentSize().height /6 * 2);

	Vector<MenuItem*> listMenuItem;
	listMenuItem.pushBack(resume);
	listMenuItem.pushBack(restart);
	listMenuItem.pushBack(selectlvl);
	listMenuItem.pushBack(backtomenu);
	//Menu *menupause = Menu::create(resume, restart, selectlvl, backtomenu, NULL);
	//menupause->setPosition(0,0);	
	m_instance->initWithArray(listMenuItem);
}

void PauseMenu::setResumeFunc(funcResume func)
{
	this->m_funcPtr = func;
}

void PauseMenu::Resume(Ref* pSender)
{
	Director::getInstance()->popScene();
	Director::sharedDirector()->resume();
	this->removeFromParentAndCleanup(true);
}

void PauseMenu::Restart(Ref *pSender)
{

}

void PauseMenu::Selectlvl(Ref* pSender)
{
	Scene *lvlselect = WorldMap::createScene();
	Director::getInstance()->replaceScene(lvlselect);
}
void PauseMenu::BacktoMenu(Ref *pSender)
{
	Player::getInstance()->removeFromParentAndCleanup(true);
	Scene *mainmenu = MainMenu::createScene();
	Director::getInstance()->replaceScene(mainmenu);
}