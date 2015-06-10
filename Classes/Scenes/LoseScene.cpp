#include "LoseScene.h"

USING_NS_CC;

Scene* Lose::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Lose::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Lose::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite *win = Sprite::create("youLose.png");
	win->setScaleX(visibleSize.height / 2 * 1.5 / win->getContentSize().height);
	win->setScaleY(visibleSize.height / 2 * 1.5 / win->getContentSize().width);
	win->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(win);

	MenuItemImage *restart = MenuItemImage::create("/Pause/Restartbtp.png", "/Pause/RestartbtpSelected.png", CC_CALLBACK_1(Lose::Restart,this));
	MenuItemImage *backtomenu = MenuItemImage::create("/Pause/MainMenubtp.png", "/Pause/MainMenubtpSelected.png", CC_CALLBACK_1(Lose::BacktoMenu,this));

	restart->setScale(win->getContentSize().height / 14 / restart->getContentSize().height);
	backtomenu->setScale(win->getContentSize().height / 14 / backtomenu->getContentSize().height);

	Vec2 point;
	point.setPoint(0.5, 0.5);
	restart->setAnchorPoint(point);
	backtomenu->setAnchorPoint(point);

	Menu *menupause = Menu::create(restart, backtomenu, NULL);
	menupause->setPosition(0,0);

	restart->setPosition(win->getPosition().x + restart->getContentSize().width*0.75, win->getPosition().y - restart->getContentSize().width*0.75);
	backtomenu->setPosition(win->getPosition().x - backtomenu->getContentSize().width*0.75, win->getPosition().y - backtomenu->getContentSize().width*0.75);

	this->addChild(menupause);

    return true;
}



void Lose::Restart(Ref *pSender)
{

}

void Lose::BacktoMenu(Ref *pSender)
{
	//Director::getInstance()->release();
	Scene *mainmenu = MainMenu::createScene();
	Director::getInstance()->replaceScene(mainmenu);
	Director::sharedDirector()->resume();
}