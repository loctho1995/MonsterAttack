#include "GamePlayScene.h"
#include "Player.h"
#include "LoadData.h"
#include "Monster.h"
#include "Animation.h"
#include "Define.h"
#include "Bullet.h"
#include "Scenes\WinScene.h"
#include "Scenes\LoseScene.h"
#include "State.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;

Menu* GamePlayScene::m_mnPause = nullptr;
int GamePlayScene::m_State = 0;

Scene* GamePlayScene::createScene(int state)
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
    auto layer = GamePlayScene::create();
	layer->setState(state);
	m_State = state;
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
	//PlatformCenter::callFunc("landscape");
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
	this->addChild(backGroundprt);

	Player::getInstance()->reset();
	Monster::resetTotalCurrentMonster();

	m_HP = new Sprite *[Player::getInstance()->getHP()];

	//LoadData::loadData();
    m_winSize = Director::getInstance()->getVisibleSize(); 
	m_isWinGame = false;
	m_isPause = false;
	m_isShowWingame = false;

	auto backGround = Sprite::create("background.jpg");
	backGround->setPosition(m_winSize.width/ 2 , m_winSize.height / 2);
	backGround->setScaleX(m_winSize.width / backGround->getContentSize().width);
	backGround->setScaleY(m_winSize.height / backGround->getContentSize().height);
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
	m_btPause->setPosition(m_winSize.width - m_btPause->getContentSize().width/2, m_winSize.height - m_btPause->getContentSize().height/2);
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
	
	//ve hp len man hinh
	for(int i = 0; i < Player::getInstance()->getHP(); i++)
	{
		m_HP[i] = Sprite::create("HP.png");
		m_HP[i]->setPosition(m_circle->getPosition().x + m_circle->getContentSize().height/2 + 10 + i*m_HP[i]->getContentSize().width/2, m_winSize.height- m_HP[i]->getContentSize().height/2);
		this->addChild(m_HP[i]);
	}

	initMenu();
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

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/sbgFighting.wav");

    return true;
}

void GamePlayScene::gameLogic(float dt)
{
	if(m_isWinGame && !m_isShowWingame)
	{
		showWinGame();
		m_isShowWingame = true;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/wingame.wav");

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
	}		
}

bool GamePlayScene::onContactBegin(const PhysicsContact& contact)
{
	auto sprite1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto sprite2 = (Sprite*)contact.getShapeB()->getBody()->getNode();

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
		if(Player::getInstance()->getHP() > 0)
			m_HP[Player::getInstance()->getHP()-1]->removeFromParentAndCleanup(true);

		if (tag == MONSTER_TAG)
		{
			((Monster*)sprite1)->done();
			((Sprite*)sprite2)->runAction(Sequence::create(TintTo::create(0, 200, 200, 200), DelayTime::create(0.25), TintTo::create(0, 255, 255, 255), nullptr));

			if(Player::getInstance()->attacked(((Monster*)sprite1)->getDamage()))
			{
				m_isLoseGame = true;
				
				Director::getInstance()->pause();
				showLoseGame();
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/gameover.wav");
			}
		}
		else
		{
			((Monster*)sprite2)->done();
			((Sprite*)sprite1)->runAction(Sequence::create(TintTo::create(0, 200, 200, 200), DelayTime::create(0.25), TintTo::create(0, 255, 255, 255), nullptr));

			if(Player::getInstance()->attacked(((Monster*)sprite2)->getDamage()))
			{
				m_isLoseGame = true;				
				Director::getInstance()->pause();
				showLoseGame();
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/gameover.wav");
			}
		}
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
	Director::getInstance()->pause();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	m_isPause = true;
	showPause();
}

int GamePlayScene::getState()
{
	return m_State;
}

void GamePlayScene::initMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_pausePanel = Sprite::create("/Pause/PauseSprite.png");
	m_pausePanel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	m_pausePanel->setZOrder(MENU_ZORDER);
	this->addChild(m_pausePanel);

	m_losePanel = Sprite::create("losepanel.png");
	m_losePanel->setPosition(m_pausePanel->getPosition());
	m_losePanel->setVisible(false);
	m_losePanel->setZOrder(MENU_ZORDER);
	this->addChild(m_losePanel);

	m_winPanel = Sprite::create("winpanel.png");
	m_winPanel->setPosition(m_pausePanel->getPosition());
	m_winPanel->setVisible(false);
	m_winPanel->setZOrder(MENU_ZORDER);
	this->addChild(m_winPanel);

	m_resume = MenuItemImage::create("/Pause/resumenormal.png", "/Pause/resumeselected.png", CC_CALLBACK_1(GamePlayScene::onMenuItemClicked,this));
	m_restart = MenuItemImage::create("/Pause/restartnormal.png", "/Pause/restartselected.png", CC_CALLBACK_1(GamePlayScene::onMenuItemClicked,this));
	m_selectlvl = MenuItemImage::create("/Pause/selectlevelnormal.png", "/Pause/selectlevelselected.png", CC_CALLBACK_1(GamePlayScene::onMenuItemClicked,this));
	m_backtomenu = MenuItemImage::create("/Pause/backtomenunormal.png", "/Pause/backtomenuselected.png", CC_CALLBACK_1(GamePlayScene::onMenuItemClicked,this));

	m_resume->setTag(MENUITEM_RESUME_TAG);
	m_restart->setTag(MENUITEM_RESTART_TAG);
	m_selectlvl->setTag(MENUITEM_SELECTLV_TAG);
	m_backtomenu->setTag(MENUITEM_BACKMENU_TAG);

	Vec2 point;
	point.setPoint(0, 0.5);
	m_resume->setAnchorPoint(point);
	m_restart->setAnchorPoint(point);
	m_selectlvl->setAnchorPoint(point);
	m_backtomenu->setAnchorPoint(point);

	m_menupause = Menu::create(m_resume, m_restart, m_selectlvl, m_backtomenu, NULL);
	m_menupause->setPosition(0,0);

	int menuSize = m_resume->getContentSize().height - 10;
	m_resume->setPosition(m_pausePanel->getPosition().x - 100, m_pausePanel->getPosition().y + menuSize);
	m_restart->setPosition(m_pausePanel->getPosition().x - 100, m_resume->getPosition().y - menuSize);
	m_selectlvl->setPosition(m_pausePanel->getPosition().x - 100, m_restart->getPosition().y - menuSize);
	m_backtomenu->setPosition(m_pausePanel->getPosition().x - 100, m_selectlvl->getPosition().y - menuSize);	
	
	m_menupause->setZOrder(MENU_ZORDER);
	this->addChild(m_menupause);

	m_menupause->setVisible(false);
	m_pausePanel->setVisible(false);
}

void GamePlayScene::showPause()
{
	int menuSize = m_resume->getContentSize().height + 10;

	m_resume->setPosition(m_pausePanel->getPosition().x - 100, m_pausePanel->getPosition().y + menuSize);
	m_restart->setPosition(m_pausePanel->getPosition().x - 100, m_resume->getPosition().y - menuSize);
	m_selectlvl->setPosition(m_pausePanel->getPosition().x - 100, m_restart->getPosition().y - menuSize);
	m_backtomenu->setPosition(m_pausePanel->getPosition().x - 100, m_selectlvl->getPosition().y - menuSize);	

	m_menupause->setVisible(true);
	m_pausePanel->setVisible(true);
}

void GamePlayScene::hideMenu()
{
	m_menupause->setVisible(false);
	m_pausePanel->setVisible(false);
}

void GamePlayScene::showWinGame()
{
	int menuSize = m_resume->getContentSize().height;

	m_restart->setPosition(m_pausePanel->getPosition().x - 100, m_winGame->getPosition().y - menuSize + 40);
	m_selectlvl->setPosition(m_pausePanel->getPosition().x - 100, m_restart->getPosition().y - menuSize);
	m_backtomenu->setPosition(m_pausePanel->getPosition().x - 100, m_selectlvl->getPosition().y - menuSize);
	
	m_winPanel->setVisible(true);
	m_menupause->setVisible(true);
	m_winGame->setVisible(true);
	m_resume->setVisible(false);
}

void GamePlayScene::showLoseGame()
{
	int menuSize = m_resume->getContentSize().height;
	m_restart->setPosition(m_pausePanel->getPosition().x - 100, m_losePanel->getPosition().y - menuSize + 40);
	m_selectlvl->setPosition(m_pausePanel->getPosition().x - 100, m_restart->getPosition().y - menuSize);
	m_backtomenu->setPosition(m_pausePanel->getPosition().x - 100, m_selectlvl->getPosition().y - menuSize);

	m_menupause->setVisible(true);
	m_losePanel->setVisible(true);
	m_resume->setVisible(false);
}

void GamePlayScene::onMenuItemClicked(Ref *ref)
{
	switch(((MenuItem*)ref)->getTag())
	{
		case MENUITEM_RESUME_TAG:
			m_isPause = false;
			Director::getInstance()->resume();
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();			
			hideMenu();
			break;

		case MENUITEM_RESTART_TAG:
			Director::getInstance()->resume();
			Director::getInstance()->replaceScene(GamePlayScene::createScene(m_State));
			m_menupause->setVisible(false);
			break;

		case MENUITEM_BACKMENU_TAG:
			Director::getInstance()->replaceScene(MainMenu::createScene());
			Player::getInstance()->removeFromParent();
			Director::getInstance()->resume();
			m_menupause->setVisible(false);
			break;
			
		case MENUITEM_SELECTLV_TAG:
			Director::getInstance()->replaceScene(WorldMap::createScene());
			Player::getInstance()->removeFromParent();
			Director::getInstance()->resume();
			m_menupause->setVisible(false);
			break;
	}
}
	

void GamePlayScene::onBackPressed()
{
#if CC_TARGET_PLATFORM_PLATFORM == CC_PLATFORM_WP8
	PlatformCenter::callFunc("exit");
#else
#endif
}