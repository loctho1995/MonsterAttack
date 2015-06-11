#include "Scenes/LogoScene.h"
#include "MainScene.h"

USING_NS_CC;

Scene* LogoScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LogoScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LogoScreen::init()
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

	time = 0;

	//sceneMenuMain = MainMenu::createScene();
    
    auto sprite = Sprite::create("LogoScreen.png");

	//sprite->setContentSize(this->getContentSize());
	sprite->setScaleX(visibleSize.width / sprite->getContentSize().width);
	sprite->setScaleY(visibleSize.height / sprite->getContentSize().height);

	//sprite->setAnchorPoint(origin);

	sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	this->scheduleUpdate();

    return true;
}

void LogoScreen::update(float dt)
{
	time += dt;	

	if(time > 1)
	{
		auto sceneMenuMain = MainMenu::createScene();
		Director::getInstance()->replaceScene(sceneMenuMain);
	}
}

