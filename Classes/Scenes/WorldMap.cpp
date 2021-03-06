#include "WorldMap.h"
#include "Player.h"
#include "GamePlayScene.h"
#include "CallBackWP.h"
#include "SaveLoad.h"

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

#if CC_TARGET_PLATFORM != CC_PLATFORM_WP8
#else
	//PlatformCenter::callFunc("landscape");
#endif

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	SaveLoad::loadGame();

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
	MenuItemImage *man01 = MenuItemImage::create("manmot.png", "manmotSelected.png", "notopen.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *man02 = MenuItemImage::create("manhai.png", "manhaiSelected.png", "notopen.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *man03 = MenuItemImage::create("manba.png", "manbaSelected.png", "notopen.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon1 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", "comingsoonLock.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon2 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", "comingsoonLock.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon3 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", "comingsoonLock.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon4 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", "comingsoonLock.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon5 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", "comingsoonLock.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon6 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", "comingsoonLock.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemImage *comingsoon7 = MenuItemImage::create("comingsoon.png", "comingsoonSelected.png", "comingsoonLock.png", CC_CALLBACK_1(WorldMap::level, this));
	MenuItemFont *empty = MenuItemFont::create(" \n\n"); //tao 1 item rong de de sap xep cac itemmenu trong menu

	man01->setScale(selectlvl->getContentSize().width / 6 / man01->getContentSize().width);
	man01->setTag(1);

	man02->setScale(selectlvl->getContentSize().width / 6 / man02->getContentSize().width);
	man02->setTag(2);

	man03->setScale(selectlvl->getContentSize().width / 6 / man03->getContentSize().width);
	man03->setTag(3);

	comingsoon1->setEnabled(false);
	comingsoon2->setEnabled(false);
	comingsoon3->setEnabled(false);
	comingsoon4->setEnabled(false);
	comingsoon5->setEnabled(false);
	comingsoon6->setEnabled(false);
	comingsoon7->setEnabled(false);

	comingsoon1->setScale(selectlvl->getContentSize().width / 6 / comingsoon1->getContentSize().width);
	//comingsoon->setScaleY(resizeY);
	comingsoon2->setScale(selectlvl->getContentSize().width / 6 / comingsoon2->getContentSize().width);
	comingsoon3->setScale(selectlvl->getContentSize().width / 6 / comingsoon2->getContentSize().width);
	comingsoon4->setScale(selectlvl->getContentSize().width / 6 / comingsoon2->getContentSize().width);
	comingsoon5->setScale(selectlvl->getContentSize().width / 6 / comingsoon2->getContentSize().width);
	comingsoon6->setScale(selectlvl->getContentSize().width / 6 / comingsoon2->getContentSize().width);
	comingsoon7->setScale(selectlvl->getContentSize().width / 6 / comingsoon2->getContentSize().width);
	//empty->setScale(selectlvl->getContentSize().width / 5 / comingsoon2->getContentSize().width);

	/*Menu *lvl = Menu::create(man01, man02, man03, comingsoon1, comingsoon2, empty, comingsoon3, comingsoon4, comingsoon5, comingsoon6, comingsoon7, NULL);
	lvl->alignItemsInColumns(5, 1, 5);*/
	Menu *lvl1 = Menu::create(man01, man02, man03, comingsoon1, comingsoon2, NULL);
	lvl1->alignItemsInColumns(5);
	lvl1->setPosition(lvl1->getPosition().x, visibleSize.height/2 + man01->getContentSize().height/2);
	Menu *lvl2 = Menu::create(comingsoon3, comingsoon4, comingsoon5, comingsoon6, comingsoon7, NULL);
	lvl2->alignItemsInColumns(5);
	lvl2->setPosition(lvl2->getPosition().x, visibleSize.height/2 - man01->getContentSize().height);

	this->addChild(lvl1);
	this->addChild(lvl2);

	for (int i = 3; i > SaveLoad::getMaxState() ; i--)
	{
		switch (i)
		{
			case 2:
				man02->setEnabled(false);
				break;

			case 3:
				man03->setEnabled(false);
				break;
		}
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/sbgWorldMap.wav");

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
	
	Scene *ingame = nullptr;

	switch(((Node*)pSender)->getTag())
	{
		case 1:
			ingame = GamePlayScene::createScene(1);
			break;

		case 2:
			if(SaveLoad::getMaxState() >= 2)
			ingame = GamePlayScene::createScene(2);
			break;

		case 3:
			if(SaveLoad::getMaxState() >= 3)
			ingame = GamePlayScene::createScene(3);
			break;
	}
	
	if(ingame != nullptr)
		Director::getInstance()->replaceScene(ingame);
}


