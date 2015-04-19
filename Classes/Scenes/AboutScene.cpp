#include "Scenes/AboutScene.h"

USING_NS_CC;

Scene* About::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = About::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool About::init()
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

	Label *title = Label::createWithTTF("Monster Attack", "fonts/Marker Felt.ttf", 50);
	title->setPosition(visibleSize.width / 2, visibleSize.height / 7 * 6);
	this->addChild(title);
	
	Label *about = Label::createWithTTF("Nhin clgt\n\n\nphan nay chua cai cai long gi dau\n\n\nlol", "fonts/Marker Felt.ttf", 20);

	about->setPosition(visibleSize.width / 2, visibleSize.height / 7 * 3);
	this->addChild(about);

	MenuItemImage *ItemBack = MenuItemImage::create("Back.png", "BackSelected.png", CC_CALLBACK_1(About::Back, this));

	ItemBack->setScale(visibleSize.width / 10 / ItemBack->getContentSize().width);
	//back->setPosition(selectlvl->getContentSize().width / 10, selectlvl->getContentSize().height / 5);

	Menu *back = Menu::create(ItemBack, NULL);
	back->setPosition(visibleSize.width / 10, visibleSize.height / 6);

	this->addChild(back);

    return true;
}

void About::Back(Ref *pSender)
{
	Scene *mainmenu = MainMenu::createScene();
	Director::getInstance()->replaceScene(mainmenu);
	this->removeFromParentAndCleanup(true);
}
