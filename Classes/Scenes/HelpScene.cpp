#include "Scenes/HelpScene.h"

USING_NS_CC;

Scene* Help::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Help::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Help::init()
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

	Label *title = Label::createWithTTF("Help!!!!!!!!", "fonts/Marker Felt.ttf", 50);
	title->setPosition(visibleSize.width / 2, visibleSize.height / 7 * 6);
	this->addChild(title);
	
	Label *about = Label::createWithTTF("Tu tim hieu cmn de", "fonts/Marker Felt.ttf", 20);

	about->setPosition(visibleSize.width / 2, visibleSize.height / 7 * 5);
	this->addChild(about);

	MenuItemImage *ItemBack = MenuItemImage::create("Back.png", "BackSelected.png", CC_CALLBACK_1(Help::Back, this));

	ItemBack->setScale(visibleSize.width / 10 / ItemBack->getContentSize().width);
	//back->setPosition(selectlvl->getContentSize().width / 10, selectlvl->getContentSize().height / 5);

	Menu *back = Menu::create(ItemBack, NULL);
	back->setPosition(visibleSize.width / 10, visibleSize.height / 6);

	m_help1 = Sprite::create("help1.png");
	m_help1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	m_help1->setZOrder(2);

	this->addChild(m_help1);

	m_help2 = Sprite::create("help2.png");
	m_help2->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	m_help2->setZOrder(1);

	this->addChild(m_help2);

	this->addChild(back);

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = CC_CALLBACK_2 (Help :: onTouchBegan, this);
	listener1->onTouchMoved = CC_CALLBACK_2(Help::onTouchMoved, this);
	listener1->onTouchEnded = CC_CALLBACK_2(Help::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    return true;
}

bool Help::onTouchBegan(Touch* touches, Event* event)
{  
	return true; // Phải trả về True
}

void Help::onTouchMoved(Touch* touches, Event* event)
{  

// Không xử lý gì ở đây

}

void Help::onTouchEnded(Touch* touches, Event* event)
{
	if(m_help1->getZOrder() > m_help2->getZOrder())
	{
		m_help1->setZOrder(1);
		m_help2->setZOrder(2);
	}
	else
	{
		m_help1->setZOrder(2);
		m_help2->setZOrder(1);
	}
}

void Help::Back(Ref *pSender)
{
	Scene *mainmenu = MainMenu::createScene();
	Director::getInstance()->replaceScene(mainmenu);
	this->removeFromParentAndCleanup(true);
}
