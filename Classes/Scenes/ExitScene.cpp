#include "Scenes/ExitScene.h"

USING_NS_CC;

Scene* Exit::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Exit::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Exit::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *warning = Sprite::create("ExitWarning.png");
	warning->setScale(visibleSize.width / 3 / warning->getContentSize().width);
	warning->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(warning);

	MenuItemImage *acept = MenuItemImage::create("Accept.png", "AcceptSelected.png", CC_CALLBACK_1(Exit::Accept,this));
	MenuItemImage *x = MenuItemImage::create("X.png", "XSelected.png", CC_CALLBACK_1(Exit::X,this));

	acept->setScale(warning->getContentSize().width / 6 / acept->getContentSize().width);
	x->setScale(warning->getContentSize().width / 6 / x->getContentSize().width);

	Menu *menu = Menu::create(x, acept, NULL);
	//menu->alignItemsInColumns(2);
	//menu->setPosition(visibleSize.width / 2, warning->getContentSize().height / 2 + warning->getContentSize().height);

	menu->setPosition(0,0);
	/*acept->setPosition(visibleSize.width / 2 + warning->getContentSize().width / 3, warning->getContentSize().height / 2 - warning->getContentSize().height);
	x->setPosition(visibleSize.width / 2 - warning->getContentSize().width / 3, warning->getContentSize().height / 2 - warning->getContentSize().height);*/
	acept->setPosition(visibleSize.width / 2 + warning->getContentSize().width / 5, visibleSize.height / 2 - warning->getContentSize().height / 2 + acept->getContentSize().width / 2);
	x->setPosition(visibleSize.width / 2 - warning->getContentSize().width / 5, visibleSize.height / 2 - warning->getContentSize().height / 2 + x->getContentSize().width / 2);

	this->addChild(menu);

    return true;
}

void Exit::Accept(Ref *pSender)
{
	Director::getInstance()->end();
}
void Exit::X(Ref *pSender)
{
	this->removeFromParentAndCleanup(true);
	MainMenu::EnableMenu();
}