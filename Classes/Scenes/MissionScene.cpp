#include "Scenes/MissionScene.h"

USING_NS_CC;

Scene* Mission::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Mission::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Mission::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//sceneMenuMain = MainMenu::createScene();
    
    auto bg = Sprite::create("BackgroundMenuMain.png");

	bg->setScaleX(visibleSize.width / bg->getContentSize().width);
	bg->setScaleY(visibleSize.height / bg->getContentSize().height);
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    this->addChild(bg);

	Label *title = Label::createWithTTF("Mission", "fonts/Marker Felt.ttf", 70);
	title->setPosition(visibleSize.width / 2, visibleSize.height / 7 * 6);
	this->addChild(title);
	
	Label *about = Label::createWithTTF("COMING SOON :D", "fonts/Marker Felt.ttf", 50);

	about->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(about);

	MenuItemImage *ItemBack = MenuItemImage::create("Back.png", "BackSelected.png", CC_CALLBACK_1(Mission::Back, this));

	ItemBack->setScale(visibleSize.width / 10 / ItemBack->getContentSize().width);
	//back->setPosition(selectlvl->getContentSize().width / 10, selectlvl->getContentSize().height / 5);

	Menu *back = Menu::create(ItemBack, NULL);
	back->setPosition(visibleSize.width / 10, visibleSize.height / 6);

	this->addChild(back);

    return true;
}

void Mission::Back(Ref *pSender)
{
	Scene *mainmenu = MainMenu::createScene();
	Director::getInstance()->replaceScene(mainmenu);
	this->removeFromParentAndCleanup(true);
}
