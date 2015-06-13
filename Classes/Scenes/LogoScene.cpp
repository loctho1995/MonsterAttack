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
    //PlatformCenter::callFunc("portrait");
#endif
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_time = 0;
	_loadResource = false;

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
	_time += dt;	

	/*if(!_loadResource)
	{
		loadResource();
	}*/

	if(_time > 1)
	{
		loadResource();
		auto sceneMenuMain = MainMenu::createScene();
		Director::getInstance()->replaceScene(sceneMenuMain);
	}
}

void LogoScreen::loadResource()
{
	//nhac nen
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/sbgMenu.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/sbgFighting.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/sbgWorldMap.wav");
	//Bullet
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Bullet/Normal.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Bullet/Ice.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Bullet/Fire.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Bullet/Lightning.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Bullet/Water.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Bullet/Circle.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Bullet/Burning.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Bullet/Freezing.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.75);

	_loadResource = true;
}

