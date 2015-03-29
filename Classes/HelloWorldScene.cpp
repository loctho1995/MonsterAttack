#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "Player.h"
#include "LoadData.h"
#include "Monster.h"
#include "Animation.h"
#include "Define.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));


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
    
	LoadData::loadData();
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


	m_bullet = Sprite::create("sperm.png");	
	this->addChild(m_bullet);
		
	srand(time(NULL));
	this->schedule( schedule_selector(HelloWorld::addTarget), 1 );

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

	Size winSize = Director::getInstance()->getVisibleSize(); 

	Point location =  touches->getLocationInView();
    location = Director::getInstance()->convertToGL(location); 
	
	Size wS = Director::getInstance()->getVisibleSize();
	auto projectile = Sprite::create("sperm.png");
	//projectile->setPosition(Point(30 + projectile->getContentSize().width / 2 + m_player->getContentSize().width, winSize.height / 2 ));
	projectile->setPosition(locateBullet(location));
	Point Test = projectile->getPosition();
	
	int offX = location.x - projectile->getPosition().x;
    int offY = location.y - projectile->getPosition().y;
	if (offX <= 0) return;
	
	auto projectileBody = PhysicsBody::createCircle(projectile->getContentSize().width / 2);
	projectile->setTag(BULLET_TAG);
	projectileBody->setContactTestBitmask(-1);
	projectile->setPhysicsBody(projectileBody);

	this->addChild(projectile,1);


	float realX = (winSize.width + m_bullet->getContentSize().width / 2);
	float realY = ((projectile->getPosition().y - Player::getInstance()->getPosition().y)/ (projectile->getPosition().x - Player::getInstance()->getPosition().x)) * realX + Player::getInstance()->getPosition().y ;
	float length = sqrtf( pow(realX - projectile ->getPosition().x , 2 ) + pow(realY - projectile ->getPosition().y , 2));
	auto realDest = Point(realX, realY);
	float velocity = 480/1;
	// Thời gian bay của đạn = quãng đường đạn bay chia vận tốc ở trên
	float realMoveDuration = length/velocity;

	projectile ->runAction(Sequence::create(
		MoveTo::create(realMoveDuration, realDest),
		CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this)),NULL));
}

bool HelloWorld::onContactBegin(const PhysicsContact& contact)
{
	auto sprite1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	int tag = sprite1->getTag();

	auto sprite2 = (Sprite*)contact.getShapeB()->getBody()->getNode();
	int tag1 = sprite2->getTag();

	if((tag== MONSTER_TAG && tag1== BULLET_TAG) || (tag == BULLET_TAG && tag1 == MONSTER_TAG))
    {
		if(tag == MONSTER_TAG)
		{
			sprite2->removeFromParentAndCleanup(true);
			((Monster*)sprite1)->die();
		}
		else
		{
			sprite1->removeFromParentAndCleanup(true);	
			((Monster*)sprite2)->die();
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

Point HelloWorld::locateBullet( Point touchPoint)
{	
	Point center = Player::getInstance()->getPosition();
	Point tempTouchPoint = touchPoint - center;
	float radius = Player::getInstance()->getContentSize().height / 2;
	Size size = Player::getInstance()->getContentSize();
	Point temp;
	float ratio = ( radius + m_bullet->getContentSize().width) / radius; 
	temp.y = sqrtf( pow(radius, 2) / (pow( (tempTouchPoint.x / tempTouchPoint.y) , 2 ) + 1) );
	temp.x = (tempTouchPoint.x / tempTouchPoint. y) * temp.y;

	if((pow(temp.x + tempTouchPoint.x , 2) + pow((temp.y + tempTouchPoint.y),2)) < ( pow(tempTouchPoint.x ,2) + pow(tempTouchPoint.y ,2)))
	{
		temp.y = - sqrtf( pow(radius, 2) / (pow( (tempTouchPoint.x / tempTouchPoint.y) , 2 ) + 1) );
		temp.x = (tempTouchPoint.x / tempTouchPoint. y) * temp.y;
	}
	Point locatedPoint;
	locatedPoint = temp * ratio;

	return Point(locatedPoint. x + center. x, locatedPoint.y + center. y );

}
	