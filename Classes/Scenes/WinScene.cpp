#include "WinScene.h"

USING_NS_CC;

Scene* Win::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Win::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Win::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite *win = Sprite::create("youWin.png");
	win->setScaleX(visibleSize.height / 2 * 1.5 / win->getContentSize().height);
	win->setScaleY(visibleSize.height / 2 * 1.5 / win->getContentSize().width);
	win->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(win);


	//MenuItemImage *resume = MenuItemImage::create("/Pause/Resume.png", "/Pause/ResumeSelected.png", CC_CALLBACK_1(Pause::Resume,this));
	MenuItemImage *next = MenuItemImage::create("next.png", "nextSelected.png", CC_CALLBACK_1(Win::Next,this));
	MenuItemImage *restart = MenuItemImage::create("/Pause/Restartbtp.png", "/Pause/RestartbtpSelected.png", CC_CALLBACK_1(Win::Restart,this));
	MenuItemImage *backtomenu = MenuItemImage::create("/Pause/MainMenubtp.png", "/Pause/MainMenubtpSelected.png", CC_CALLBACK_1(Win::BacktoMenu,this));

	next->setScale(win->getContentSize().height / 14 / next->getContentSize().height);
	restart->setScale(win->getContentSize().height / 14 / restart->getContentSize().height);
	backtomenu->setScale(win->getContentSize().height / 14 / backtomenu->getContentSize().height);

	Vec2 point;
	point.setPoint(0.5, 0.5);
	next->setAnchorPoint(point);
	restart->setAnchorPoint(point);
	backtomenu->setAnchorPoint(point);

	Menu *menupause = Menu::create(next, restart, backtomenu, NULL);
	menupause->setPosition(0,0);

	next->setPosition(win->getPosition().x + next->getContentSize().width, win->getPosition().y - next->getContentSize().width*0.75);
	restart->setPosition(win->getPosition().x, win->getPosition().y - next->getContentSize().width*0.75);
	backtomenu->setPosition(win->getPosition().x - next->getContentSize().width, win->getPosition().y - next->getContentSize().width*0.75);

	this->addChild(menupause);

    return true;
}



void Win::Restart(Ref *pSender)
{
	Player::getInstance()->removeFromParent();
	Scene *newgame = GamePlayScene::createScene(GamePlayScene::getState());
	Director::getInstance()->replaceScene(newgame);
	Director::sharedDirector()->resume();
}
void Win::Next(Ref* pSender)
{
	//Director::getInstance()->release();
	Scene *lvlselect = WorldMap::createScene();
	Director::getInstance()->replaceScene(lvlselect);
	Director::sharedDirector()->resume();
}
void Win::BacktoMenu(Ref *pSender)
{
	//Director::getInstance()->release();
	Scene *mainmenu = MainMenu::createScene();
	Director::getInstance()->replaceScene(mainmenu);
	Director::sharedDirector()->resume();
}