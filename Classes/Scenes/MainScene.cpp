#include "Scenes/MainScene.h"
#include "CallBackWP.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

Menu* MainMenu::menu = nullptr;

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
#if CC_TARGET_PLATFORM != CC_PLATFORM_WP8
#else
	PlatformCenter::callFunc("portrait");
#endif

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create("BackgroundMenuMain.png");

	bg->setScaleX(visibleSize.width / bg->getContentSize().width);
	bg->setScaleY(visibleSize.height / bg->getContentSize().height);
	bg->setPosition(visibleSize.width  / 2, visibleSize.height / 2);

	this->addChild(bg);

	Sprite *title = Sprite::create("TitleGame.png");

	title->setScaleX(visibleSize.width / 5 * 2 / title->getContentSize().width);
	title->setScaleY(visibleSize.height / 7 / title->getContentSize().height);
	title->setPosition(visibleSize.width / 2, visibleSize.height / 10 * 9);

	this->addChild(title);

	auto ItemPlay = MenuItemImage::create("Play.png", "PlaySelected.png", CC_CALLBACK_1(MainMenu::Play,this));

	auto ItemContinue = MenuItemImage::create("Continue.png", "ContinueSelected.png", CC_CALLBACK_1(MainMenu::Continue,this));

	auto ItemMission = MenuItemImage::create("Mission.png", "MissionSelected.png", CC_CALLBACK_1(MainMenu::Mission,this));

	auto ItemAbout = MenuItemImage::create("About.png", "AboutSelected.png", CC_CALLBACK_1(MainMenu::About,this));

	auto ItemHelp = MenuItemImage::create("Help.png", "HelpSelected.png", CC_CALLBACK_1(MainMenu::Help,this));

	auto ItemExit = MenuItemImage::create("Exit.png", "ExitSelected.png", CC_CALLBACK_1(MainMenu::Exit,this));
    

	menu = Menu::create(ItemPlay, ItemContinue, ItemMission, ItemAbout, ItemHelp, ItemExit, NULL);

	menu->alignItemsVerticallyWithPadding(15.0f);
	//menu->alignItemsInColumns(2,2,2);
	menu->setScaleY(visibleSize.height * 0.75 / menu->getContentSize().height);

	menu->setPosition(visibleSize.width / 2, visibleSize.height / 10 * 3);

	this->addChild(menu);

    return true;
}

void MainMenu::Play(Ref *pSender)
{
	Scene *wordlmap = WorldMap::createScene();
	Director::getInstance()->replaceScene(wordlmap);
}

void MainMenu::Continue(Ref *pSender)
{

}

void MainMenu::Mission(Ref *pSender)
{
	Scene *mission = Mission::createScene();
	Director::getInstance()->replaceScene(mission);
}

void MainMenu::About(Ref *pSender)
{
	Scene *about = About::createScene();
	Director::getInstance()->replaceScene(about);
}

void MainMenu::Help(Ref *pSender)
{
	Scene *help = Help::createScene();
	Director::getInstance()->replaceScene(help);
}

void MainMenu::Exit(Ref *pSender)
{
	Scene *exit = Exit::createScene();
	this->addChild(exit);
	DisableMenu();
}

void MainMenu::DisableMenu()
{
	menu->setEnabled(false);
}

void MainMenu::EnableMenu()
{
#if CC_TARGET_PLATFORM != CC_PLATFORM_WP8
#else
	PlatformCenter::callFunc("exit");
#endif

	menu->setEnabled(true);
}