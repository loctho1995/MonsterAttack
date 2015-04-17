#include "WorldMap.h"

USING_NS_CC;

Scene* WorldMap::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WorldMap::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WorldMap::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create("BackgroundMenuMain.png");

	bg->setScaleX(visibleSize.width / bg->getContentSize().width);
	bg->setScaleY(visibleSize.height / bg->getContentSize().height);
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	this->addChild(bg);

	Sprite *selectlvl = Sprite::create("Selectlvl.png");

	/*float resizeX = selectlvl->getContentSize().width;
	float resizeY = selectlvl->getContentSize().height;*/

	selectlvl->setScaleX(visibleSize.width / selectlvl->getContentSize().width);
	selectlvl->setScaleY(visibleSize.height / selectlvl->getContentSize().height);
	selectlvl->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	this->addChild(selectlvl);

	/*resizeX = selectlvl->getContentSize().width / resizeX;
	resizeY = selectlvl->getContentSize().height / resizeY;*/

	MenuItemImage *ItemBack = MenuItemImage::create("Back.png", "BackSelected.png", CC_CALLBACK_1(WorldMap::Back, this));

	ItemBack->setScale(selectlvl->getContentSize().width / 10 / ItemBack->getContentSize().width);
	//back->setPosition(selectlvl->getContentSize().width / 10, selectlvl->getContentSize().height / 5);

	Menu *back = Menu::create(ItemBack, NULL);
	back->setPosition(selectlvl->getContentSize().width / 10, selectlvl->getContentSize().height / 6);

	this->addChild(back);

	//cac item chon man
	MenuItemImage *man01 = MenuItemImage::create("manmot.png", "manmotSelected.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *man02 = MenuItemImage::create("manhai.png", "manhaiSelected.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *man03 = MenuItemImage::create("manba.png", "manbaSelected.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon1 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon2 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon3 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon4 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon5 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon6 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon7 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemFont *empty = MenuItemFont::create(" \n\n"); //tao 1 item rong de de sap xep cac itemmenu trong menu

	man01->setScale(selectlvl->getContentSize().width / 5 / man01->getContentSize().width);
	//man01->setScaleY(resizeY);
	man02->setScale(selectlvl->getContentSize().width / 5 / man02->getContentSize().width);
	//man02->setScaleY(resizeY);
	man03->setScale(selectlvl->getContentSize().width / 5 / man03->getContentSize().width);
	//man03->setScaleY(resizeY);
	comingsoon1->setScale(selectlvl->getContentSize().width / 5 / comingsoon1->getContentSize().width);
	//comingsoon->setScaleY(resizeY);
	comingsoon2->setScale(selectlvl->getContentSize().width / 5 / comingsoon2->getContentSize().width);
	comingsoon3->setScale(selectlvl->getContentSize().width / 5 / comingsoon2->getContentSize().width);
	comingsoon4->setScale(selectlvl->getContentSize().width / 5 / comingsoon2->getContentSize().width);
	comingsoon5->setScale(selectlvl->getContentSize().width / 5 / comingsoon2->getContentSize().width);
	comingsoon6->setScale(selectlvl->getContentSize().width / 5 / comingsoon2->getContentSize().width);
	comingsoon7->setScale(selectlvl->getContentSize().width / 5 / comingsoon2->getContentSize().width);
	//empty->setScale(selectlvl->getContentSize().width / 5 / comingsoon2->getContentSize().width);

	Menu *lvl = Menu::create(man01, man02, man03, comingsoon1, comingsoon2, empty, comingsoon3, comingsoon4, comingsoon5, comingsoon6, comingsoon7, NULL);
	lvl->alignItemsInColumns(5, 1, 5);

	this->addChild(lvl);

    return true;
}

void WorldMap::Back(Ref *pSender)
{
	Scene *mainmenu = MainMenu::createScene();
	Director::getInstance()->replaceScene(mainmenu);
	this->removeFromParentAndCleanup(true);
}

void WorldMap::level(Ref *pSender)
{
	Scene *Ingame = HelloWorld::createScene();
	Director::getInstance()->replaceScene(Ingame);
}


