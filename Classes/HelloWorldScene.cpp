#include "HelloWorldScene.h"
#include "GameOverScene.h"
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
    
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background-music-aac.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background-music-aac.mp3",true); // True = lặp lại vô hạn
    Size winSize = Director::getInstance()->getWinSize(); 

	auto backGround = Sprite::create("background.jpg");
	backGround->setPosition(winSize.width/ 2 , winSize.height / 2);
	this->addChild(backGround,0);
	m_player = Sprite::create("Zues_converted.png");
	m_player->setPosition(Point(m_player -> getContentSize().width / 2,winSize.height/ 2));

	auto playerbody  = PhysicsBody::createCircle(m_player->getContentSize().width / 2);
	m_player->setTag(1);
	playerbody->setContactTestBitmask(0x1);
	playerbody->setDynamic(false);
	m_player->setPhysicsBody(playerbody);
	this ->addChild(m_player,1);


	m_bullet = Sprite::create("sperm.png");
	
	this->addChild(m_bullet);
	
	
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

	// GHOST VECTOR SP
	// Luu vao bo nho dem SpriteBatchNode , Bien spriteSheet
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Ghost.plist");
	m_spriteSheet = SpriteBatchNode :: create ("Ghost.png");
	this->addChild(m_spriteSheet);

	// Luu cac frame di vao aniFrame
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	for (int i = 1; i < 19; i++)
	{
		sprintf(str,"Ghost%d.png",i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		aniFrame.pushBack(frame);

	}
	/*auto bear = Sprite::createWithSpriteFrameName("Ghost1.png");
	bear->setPosition(Point(winSize.width / 2, winSize.height/ 2));
	this ->addChild(bear);*/

	// Tao animate
	/*auto animation = Animation::createWithSpriteFrames(aniFrame,1);
	m_walk = RepeatForever::create(Animate::create(animation));
	m_walk ->retain();*/

    return true;
}

void HelloWorld::gameLogic(float dt)
{
	 this->addTarget(dt);
}

void HelloWorld:: addTarget(float dt)
{
	auto target = Sprite :: createWithSpriteFrameName("Ghost1.png");
	m_spriteSheet->addChild(target);
	Size winSize = Director :: getInstance() ->getWinSize();

	// calculate target position
	int minY = target->getContentSize().height / 2;
	int maxY = winSize.height - target -> getContentSize().height / 2;
	int rangeY = maxY - minY;
	int actualY = (rand()% rangeY) + minY;
	
	//
	target->setPosition(Point(winSize.width + (target->getContentSize().width/2),actualY));


	auto targetBody = PhysicsBody::createCircle(target->getContentSize().width / 2);
	target->setTag(2);
	targetBody->setContactTestBitmask(0x1);
	target->setPhysicsBody(targetBody);

	target->setFlippedX(true);
    //this->addChild(target,1);


	//
	int minDuration = (int)2.0;
    int maxDuration = (int)4.0;
    int rangeDuration = maxDuration - minDuration;
    /*int actualDuration = ( rand() % rangeDuration )
                                        + minDuration;*/
	int actualDuration  = 3;
	auto actionMove =  MoveTo::create( (float)actualDuration, Point(0 - target->getContentSize().width/2, actualY) );
	auto actionMoveDone =   CallFuncN::create(CC_CALLBACK_1(HelloWorld::targetMoveFinished,this));

	auto animation = Animation::createWithSpriteFrames(aniFrame,0.1);
	auto walkAction = RepeatForever::create(Animate::create(animation));
	target->runAction(walkAction);
	target->runAction( Sequence::create(actionMove, actionMoveDone, NULL) );


	
}
void HelloWorld::targetMoveFinished(Node* sender)
{
// Hàm này có mỗi công việc là loại bỏ Target ( đang là Sprite) ra khỏi layer của game
// Ép kiểu Contrỏ Sprite của 1 Node*
  sender ->removeFromParent();
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
	Size winSize = Director::getInstance()->getWinSize(); 

	Point location =  touches->getLocationInView();
    location = Director::getInstance()->convertToGL(location); 
	
	Size wS = Director::getInstance()->getWinSize();
	auto projectile = Sprite::create("sperm.png");
	//projectile->setPosition(Point(30 + projectile->getContentSize().width / 2 + m_player->getContentSize().width, winSize.height / 2 ));
	projectile->setPosition(locateBullet(location));
	Point Test = projectile->getPosition();
	
	int offX = location.x - projectile->getPosition().x;
    int offY = location.y - projectile->getPosition().y;
	if (offX <= 0) return;
	
	auto projectileBody = PhysicsBody::createCircle(projectile->getContentSize().width / 2);
	projectile->setTag(3);
	projectileBody->setContactTestBitmask(0x1);
	projectile->setPhysicsBody(projectileBody);

	this->addChild(projectile,1);

	//int realX = winSize.width  + (projectile->getContentSize().width/2); 

	//// Tỷ lệ giữa offY và offX
	//float ratio = (float)offY / (float)offX;

	//// Tọa độ tuyệt đối realY tính dựa trên realX và tỷ lệ trên + thêm tọa độ Y ban đầu của đạn ( tính theo Talet trong tam giác, hoặc theo tính tang 1 góc)

	//int realY = (realX * ratio) + projectile->getPosition().y; // Chỗ này theo mình là chưa đúng, đúng ra phải thế này int realY = ((realX-projectile->getPosition().x) * ratio) + projectile->getPosition().y; (realX-projectile->getPosition().x mới đúng là chiều dài từ điểm đầu tới điểm cuối trên trục X

	////Tọa độ điểm cuối
	//auto realDest = Point(realX, realY);

	////Chiều dài đường đi của viên đạn, tính theo Pitago a*a = b*b + c*c, a là cạnh huyền tam giác vuông
	//int offRealX = realX - projectile->getPosition().x;
	//int offRealY = realY - projectile->getPosition().y;
	//float length = sqrtf((offRealX * offRealX)  + (offRealY*offRealY));
	float realX = (winSize.width + m_bullet->getContentSize().width / 2);
	float realY = ((projectile->getPosition().y - m_player->getPosition().y)/ (projectile->getPosition().x - m_player ->getPosition().x)) * realX + m_player->getPosition().y ;
	float length = sqrtf( pow(realX - projectile ->getPosition().x , 2 ) + pow(realY - projectile ->getPosition().y , 2));
	auto realDest = Point(realX, realY);
	float velocity = 480/1;
	// Thời gian bay của đạn = quãng đường đạn bay chia vận tốc ở trên
	float realMoveDuration = length/velocity;

	/*projectile->runAction( Sequence::create(
	MoveTo::create(realMoveDuration, realDest),
	CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished,this)), NULL) );*/
	projectile ->runAction(Sequence::create(
		MoveTo::create(realMoveDuration, realDest),
		CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished,this)),NULL));
}
bool HelloWorld::onContactBegin(const PhysicsContact& contact)
{
	auto sprite1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	int tag = sprite1->getTag();
	auto sprite2 = (Sprite*)contact.getShapeB()->getBody()->getNode();
	int tag1 = sprite2->getTag();
	if((tag==2&tag1==3) || (tag == 3 & tag1 == 2))
    {
		sprite1->removeFromParent();
		sprite2->removeFromParent();
	}
	
	if((tag== 1&tag1 == 2) || (tag==2 &tag1== 1))
	{

		auto gameOverScene = GameOverScene::create(); // Tạo 1 Scene Over của lớp GameOverScene
		gameOverScene->getLayer()->getLabel()->setString("LOSE MOTHER FUCKER =))"); // Đặt 1 dòng thông báo lên màn hình
		Director::getInstance()->replaceScene(gameOverScene); // Thay thế game Scene =  game Over Scene

	}
	if((tag== 1&tag1 == 3) || (tag==3 &tag1== 1))
	{

	}
	return true;

}
Point HelloWorld::locateBullet  ( Point touchPoint)
{
	
	Point center = m_player ->getPosition();
	Point tempTouchPoint = touchPoint - center;
	float radius = m_player ->getContentSize().height / 2;
	Size size = m_player ->getContentSize();
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
	