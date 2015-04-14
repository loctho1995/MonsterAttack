#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "Player.h"
#include "LoadData.h"
#include "Monster.h"
#include "Animation.h"
#include "Define.h"
#include "Bullet.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
	
    if ( !Layer::init() )
    {
        return false;
    }
    
	Monster1Action::getInstance()->loadAnimation(SpriteFrameCache::getInstance());
	Monster2Action::getInstance()->loadAnimation(SpriteFrameCache::getInstance());
	PlayerAction::getInstance()->loadAnimation(SpriteFrameCache::getInstance());

	//LoadData::loadData();
    m_winSize = Director::getInstance()->getVisibleSize(); 

	auto backGround = Sprite::create("background.jpg");
	backGround->setPosition(m_winSize.width/ 2 , m_winSize.height / 2);
	this->addChild(backGround,0);

	Player::getInstance()->setPosition(Vec2(Player::getInstance()->getContentSize().width / 2, m_winSize.height / 2));
	this->addChild(Player::getInstance());

	m_circle = Sprite::create("Circle.png");
	m_circle->setPosition(Player::getInstance()->getPosition());
	m_circle->setTag(CIRCLE_TAG);
	this->addChild(m_circle);
	auto circleBound = PhysicsBody::createCircle(m_circle->getContentSize().width / 2, PhysicsMaterial(0, 0, 0), Vec2::ZERO);
	circleBound->setContactTestBitmask(0x1);
	circleBound->setDynamic(false);	
	m_circle->setPhysicsBody(circleBound);
	
	srand(time(NULL));
	this->schedule( schedule_selector(HelloWorld::addTarget), 1.0f);

	auto dispatcher = Director::getInstance()-> getEventDispatcher();

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = CC_CALLBACK_2 (HelloWorld :: onTouchBegan, this);
	listener1->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener1->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	auto contactListener = EventListenerPhysicsContact :: create();
	contactListener ->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);

	dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

void HelloWorld::gameLogic(float dt)
{
	 this->addTarget(dt);
}

void HelloWorld:: addTarget(float dt)
{
	Monster *target;

	if(random() % 2 == 0)
		target = new Monster1();
	else
		target = new Monster2();		

	// calculate target position
	int minY = target->getContentSize().height / 2;
	int maxY = m_winSize.height - target -> getContentSize().height / 2;
	int rangeY = maxY - minY;
	int actualY = (rand()% rangeY) + minY;
		
	target->setPosition(Point(m_winSize.width + (target->getContentSize().width/2), actualY));
	auto targetBody = PhysicsBody::createCircle(target->getContentSize().width / 2);
	targetBody->setContactTestBitmask(0x1);	
	target->setPhysicsBody(targetBody);

	this->addChild(target, 3);	
	target->walk();
}
void HelloWorld::targetMoveFinished(Node* sender)
{
// Hàm này có mỗi công việc là loại bỏ Target ( đang là Sprite) ra khỏi layer của game
// Ép kiểu Contrỏ Sprite của 1 Node*
	//sender ->removeFromParentAndCleanup(true);
}
void HelloWorld::spriteMoveFinished(Node* sender)
{
// Hàm này có mỗi công việc là loại bỏ Target ( đang là Sprite) ra khỏi layer của game
// Ép kiểu Contrỏ Sprite của 1 Node*
  auto sprite = (Sprite *)sender;
  this->removeChild(sprite, true);    
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


bool HelloWorld::onTouchBegan(Touch* touches, Event* event)
{  

 return true; // Phải trả về True
}

void HelloWorld::onTouchMoved(Touch* touches, Event* event)
{  

// Không xử lý gì ở đây

}

void HelloWorld::onTouchEnded(Touch* touches, Event* event)
{
	if (touches->getLocation().getDistance(m_circle->getPosition()) >= m_circle->getContentSize().width / 2)
	{
		return;
	}

	Player::getInstance()->stopAllActions();
	Player::getInstance()->attack();

	auto bullet = BulletManager::create(BulletType::ICE);
	bullet->move(touches, Player::getInstance(), this);
}

bool HelloWorld::onContactBegin(const PhysicsContact& contact)
{
	auto sprite1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto sprite2 = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if(sprite1 == nullptr || sprite2 == nullptr)
		return false;

	int tag = sprite1->getTag();
	int tag1 = sprite2->getTag();

	if((tag== MONSTER_TAG && tag1== BULLET_TAG) || (tag == BULLET_TAG && tag1 == MONSTER_TAG))
    {
		if(tag == MONSTER_TAG)
		{
			((Monster*)sprite1)->attacked((Bullet*)sprite2);
		}
		else
		{
			((Monster*)sprite2)->attacked((Bullet*)sprite1);		
		}
	}

	if ((tag == CIRCLE_TAG && tag1 == MONSTER_TAG) || (tag1 == CIRCLE_TAG && tag == MONSTER_TAG) )
	{
		if (tag == MONSTER_TAG)
			((Monster*)sprite1)->done();
		else
			((Monster*)sprite2)->done();
	}
		
	return true;
}
	