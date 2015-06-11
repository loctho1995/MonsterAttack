#include "GamePlayScene.h"
#include "Player.h"
#include "LoadData.h"
#include "Monster.h"
#include "Animation.h"
#include "Define.h"
#include "Bullet.h"
#include "Scenes/PauseScene.h"
#include "State.h"

USING_NS_CC;
using namespace std;

Menu* GamePlayScene::m_mnPause = nullptr;

Scene* GamePlayScene::createScene(int state)
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
    auto layer = GamePlayScene::create();
	layer->setState(state);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool GamePlayScene::init()
{
    //////////////////////////////
    // 1. super init first
	
    if ( !Layer::init() )
    {
        return false;
    }
#if CC_TARGET_PLATFORM != CC_PLATFORM_WP8
#else
	PlatformCenter::callFunc("landscape");
#endif
	srand(time(0));
	m_timeWave = WAVE_TIME;

	Monster1Action::getInstance()->loadAnimation(SpriteFrameCache::getInstance());
	Monster2Action::getInstance()->loadAnimation(SpriteFrameCache::getInstance());
	Monster3Action::getInstance()->loadAnimation(SpriteFrameCache::getInstance());
	Monster4Action::getInstance()->loadAnimation(SpriteFrameCache::getInstance());
	PlayerAction::getInstance()->loadAnimation(SpriteFrameCache::getInstance());

	//Tao hieu ung particle cho man hinh
	ParticleSystemQuad *backGroundprt = ParticleSystemQuad::create("/BulletParticle/LeaveStorm.plist");
	this->addChild(backGroundprt,200);

	//LoadData::loadData();
    m_winSize = Director::getInstance()->getVisibleSize(); 
	m_isWinGame = false;
	/*Draw by pixels on
	auto draw = DrawNode::create();
	this->addChild(draw);
	draw->drawDot(Vec2(m_winSize.width / 2, m_winSize.height / 2), 1.0f, Color4F(1,1,1,0.2f));*/

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
	circleBound->setContactTestBitmask(CIRCLE_CONTACT_TEST_BITMASK);
	//circleBound->setContactTestBitmask(0x1);
	circleBound->setDynamic(false);
	circleBound->setCollisionBitmask(CIRCLE_CONLLISION_BITMASK);
	circleBound->setCategoryBitmask(CIRCLE_CONTACT_CATEGORY);
	m_circle->setPhysicsBody(circleBound);
	
	//tao nut pause
	m_btPause = MenuItemImage::create("/Pause/Pause.png", "/Pause/PauseSelected.png", CC_CALLBACK_1(GamePlayScene::Pause, this));
	m_btPause->setScale(m_winSize.height / 10 / m_btPause->getContentSize().width);
	m_mnPause = Menu::create(m_btPause, NULL);
	m_mnPause->setPosition(0, 0);
	m_btPause->setPosition(m_winSize.width - m_winSize.width / 10, m_winSize.height - m_winSize.height / 10);
	this->addChild(m_mnPause);

	//hinh next wave
	m_nextWave = Sprite::create("NextWave.png");
	m_nextWave->setPosition(Vec2(m_winSize.width / 2, m_winSize.height / 2));
	m_nextWave->setVisible(false);
	this->addChild(m_nextWave);

	//hinh final wave
	m_finalWave = Sprite::create("FinalWave.png");
	m_finalWave->setPosition(Vec2(m_winSize.width / 2, m_winSize.height / 2));
	m_finalWave->setVisible(false);
	this->addChild(m_finalWave);

	m_winGame = Sprite::create("WinGame.png");
	m_winGame->setPosition(Vec2(m_winSize.width / 2, m_winSize.height / 2));
	m_winGame->setVisible(false);
	this->addChild(m_winGame);
	
	

	this->schedule( schedule_selector(GamePlayScene::gameLogic), 2.0f);

	auto dispatcher = Director::getInstance()-> getEventDispatcher();

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = CC_CALLBACK_2 (GamePlayScene :: onTouchBegan, this);
	listener1->onTouchMoved = CC_CALLBACK_2(GamePlayScene::onTouchMoved, this);
	listener1->onTouchEnded = CC_CALLBACK_2(GamePlayScene::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	auto contactListener = EventListenerPhysicsContact :: create();
	contactListener ->onContactBegin = CC_CALLBACK_1(GamePlayScene::onContactBegin, this);

	dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	srand(time(NULL));

    return true;
}

void GamePlayScene::gameLogic(float dt)
{
	if(m_isWinGame)
	{
		m_winGame->setVisible(true);
		return;
	}

	if(m_timeWave >= 0)
	{
		m_state->addTarget(this, dt);
		m_timeWave -= dt;

		if(m_state->isRunning())
		{
			m_nextWave->setVisible(false);
			m_finalWave->setVisible(false);
		}			
	}
	else
	{
		CCLOG("%d", Monster::getTotalCurrentMonster());
		if(m_state->isEndWave())
		{						
			if(Monster::getTotalCurrentMonster() <= 0)		
				m_isWinGame = true;
		}
		else
		{			
			if(Monster::getTotalCurrentMonster() <= 0)
			{
				m_timeWave = WAVE_TIME + NEXTWAVE_DELAY_TIME;
				m_state->nextWave();
				m_state->pause(NEXTWAVE_DELAY_TIME);

				if(m_state->isEndWave())
					m_finalWave->setVisible(true);
				else
					m_nextWave->setVisible(true);
			}
		}
	}
}

void GamePlayScene::setState(int state)
{
	switch(state)
	{
		case 1:
			m_state = new State1();
			break;

		case 2:
			m_state = new State2();
			break;

		case 3:
			m_state = new State3();
			break;
	}
}

void GamePlayScene::menuCloseCallback(Ref* pSender)
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

bool GamePlayScene::onTouchBegan(Touch* touches, Event* event)
{  
	return true; // Phải trả về True
}

void GamePlayScene::onTouchMoved(Touch* touches, Event* event)
{  

// Không xử lý gì ở đây

}

void GamePlayScene::onTouchEnded(Touch* touches, Event* event)
{
	for (int i = 0; i < ItemManager::getInstacce()->getItems().size(); i++)
	{
		if (ItemManager::getInstacce()->getItems().at(i)->checkTouch(touches->getLocation()))
		{
			Player::getInstance()->setBulletType(ItemManager::getInstacce()->getItems().at(i)->getType());
			ItemManager::getInstacce()->eraseItem(i);
			return;
		}	
	}

	if (touches->getLocation().getDistance(m_circle->getPosition()) >= m_circle->getContentSize().width / 2)
	{		
		return;
	}

	//Player::getInstance()->stopAllActions();

	if(Player::getInstance()->isFinishAction())
	{
		Player::getInstance()->attack(touches);
		//auto bullet = BulletManager::create(Player::getInstance()->getBulletType());
		//bullet->move(touches->getLocation(), Player::getInstance(), Player::getInstance()->getParent());
	}		
}

bool GamePlayScene::onContactBegin(const PhysicsContact& contact)
{
	/*if((contact.getShapeA()->getBody()->getCollisionBitmask() & contact.getShapeB()->getBody()->getCategoryBitmask() == 0) 
		|| (contact.getShapeB()->getBody()->getCollisionBitmask() & contact.getShapeA()->getBody()->getCategoryBitmask()) == 0)
		return false;*/

	auto sprite1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto sprite2 = (Sprite*)contact.getShapeB()->getBody()->getNode();

	/*if(sprite1 == nullptr || sprite2 == nullptr)
		return false;*/

	int tag = sprite1->getTag();
	int tag1 = sprite2->getTag();

	if((tag== MONSTER_TAG && tag1== BULLET_TAG) || (tag == BULLET_TAG && tag1 == MONSTER_TAG))
    {
		if(tag == MONSTER_TAG)
		{
			if(((Monster*)sprite1)->attacked((Bullet*)sprite2))
				((Monster*)sprite1)->die();
		}
		else
		{
			if(((Monster*)sprite2)->attacked((Bullet*)sprite1))
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
	
	if((tag == MONSTER_TAG && tag1 == LIGHTINGCIRCLE_TAG) || (tag1 == MONSTER_TAG && tag == LIGHTINGCIRCLE_TAG))
	{
		if(tag == MONSTER_TAG)
		{
			if(((Monster*)sprite1)->attackedByLightingCircle())
				((Monster*)sprite1)->die();
		}
		else
			if(((Monster*)sprite2)->attackedByLightingCircle())
				((Monster*)sprite2)->die();
	}

	return true;
}
	
void GamePlayScene::Pause(Ref *pSender)
{	
	Director::sharedDirector()->pause();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
	DisablePausebt();
	Layer *m_sPause = Pause::create();
	this->addChild(m_sPause, 100);
}

void GamePlayScene::EnablePausebt()
{
	m_mnPause->setEnabled(true);
}

void GamePlayScene::DisablePausebt()
{
	m_mnPause->setEnabled(false);
}

void GamePlayScene::onBackPressed()
{
#if CC_TARGET_PLATFORM_PLATFORM == CC_PLATFORM_WP8
	PlatformCenter::callFunc("exit");
#else
#endif
}