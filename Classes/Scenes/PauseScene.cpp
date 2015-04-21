#include "PauseScene.h"

USING_NS_CC;

Scene* Pause::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Pause::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Pause::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Sprite *bg = Sprite::create("background.jpg");
	/*bg->setScaleX(visibleSize.width / bg->getContentSize().width);
	bg->setScaleY(visibleSize.height / bg->getContentSize().height);*/
	//bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//this->addChild(bg);

	Sprite *paused = Sprite::create("/Pause/PauseSprite.png");
	paused->setScaleX(visibleSize.height / 2 * 1.5 / paused->getContentSize().height);
	paused->setScaleY(visibleSize.height / 2 * 1.5 / paused->getContentSize().width);
	paused->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(paused);

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

	this->addChild(resumeIcon);
	this->addChild(restartIcon);
	this->addChild(selectlvlIcon);
	this->addChild(backtomenuIcon);

	MenuItemImage *resume = MenuItemImage::create("/Pause/Resume.png", "/Pause/ResumeSelected.png", CC_CALLBACK_1(Pause::Resume,this));
	MenuItemImage *restart = MenuItemImage::create("/Pause/Restart.png", "/Pause/RestartSelected.png", CC_CALLBACK_1(Pause::Restart,this));
	MenuItemImage *selectlvl = MenuItemImage::create("/Pause/Selectlvl.png", "/Pause/SelectlvlSelected.png", CC_CALLBACK_1(Pause::Selectlvl,this));
	MenuItemImage *backtomenu = MenuItemImage::create("/Pause/BacktoMenu.png", "/Pause/BacktoMenuSelected.png", CC_CALLBACK_1(Pause::BacktoMenu,this));

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

	Menu *menupause = Menu::create(resume, restart, selectlvl, backtomenu, NULL);
	menupause->setPosition(0,0);

	resume->setPosition(visibleSize.width / 2 - resumeIcon->getContentSize().width, visibleSize.height / 2 + paused->getContentSize().height /6);
	restart->setPosition(visibleSize.width / 2 - resumeIcon->getContentSize().width, visibleSize.height / 2);
	selectlvl->setPosition(visibleSize.width / 2 - resumeIcon->getContentSize().width, visibleSize.height / 2 - paused->getContentSize().height /6);
	backtomenu->setPosition(visibleSize.width / 2 - resumeIcon->getContentSize().width, visibleSize.height / 2 - paused->getContentSize().height /6 * 2);

	this->addChild(menupause);

    return true;
}


void Pause::Resume(Ref* pSender)
{
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent());
	this->removeFromParentAndCleanup(true);
	HelloWorld::EnablePausebt();
	Director::sharedDirector()->resume();
}
void Pause::Restart(Ref *pSender)
{

}
void Pause::Selectlvl(Ref* pSender)
{
	//Director::getInstance()->release();
	Scene *lvlselect = WorldMap::createScene();
	Director::getInstance()->replaceScene(lvlselect);
	Director::sharedDirector()->resume();
}
void Pause::BacktoMenu(Ref *pSender)
{
	//Director::getInstance()->release();
	Scene *mainmenu = MainMenu::createScene();
	Director::getInstance()->replaceScene(mainmenu);
	Director::sharedDirector()->resume();
}