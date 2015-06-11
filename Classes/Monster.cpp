#include "Monster.h"
#include "Animation.h"
#include "Define.h"
#include "Item.h"

int Monster::m_totalCurrentMonster = 0;

#pragma region - Monster 1 -

Monster1::Monster1()
{
	this->initWithSpriteFrameName("Monster1WalkAnimation_1.png");
	this->setTag(MONSTER_TAG);

	m_isDieing = false;
	m_HP = 1;
	m_speed = 100;
	m_damage = 1;

	Monster::addBody();
}

void Monster1::walk()
{
	m_walk = Monster1Action::getInstance()->getMonsterWalkAnimate()->clone();	
	Monster::walk();
}

void Monster1::die()
{
	//m_die = Monster1Action::getInstance()->getMonsterDieAnimate()->clone();
	Monster::die();
}

void Monster1::done()
{
	//m_done = Monster1Action::getInstance()->getMonsterDoneAnimate()->clone();
	Monster::done();
}

#pragma endregion

#pragma region - Monster 2 -

Monster2::Monster2()
{
	this->initWithSpriteFrameName("Monster2WalkAnimation_1.png");	
	this->setTag(MONSTER_TAG);

	m_isDieing = false;
	m_HP = 2;
	m_speed = 90;
	m_damage = 1;

	Monster::addBody();
}

void Monster2::walk()
{
	m_walk = Monster2Action::getInstance()->getMonsterWalkAnimate()->clone();	
	Monster::walk();
}

void Monster2::die()
{
	Monster::die();
}

void Monster2::done()
{	
	//m_done = Monster1Action::getInstance()->getMonsterDoneAnimate()->clone();
	Monster::done();
}

#pragma endregion

#pragma region - Monster 3 -
Monster3::Monster3()
{
	this->initWithFile("Monster1_Stand.png");	
	this->setTag(MONSTER_TAG);

	m_isDieing = false;
	m_HP = 3;
	m_speed = 80;
	m_damage = 1;	

	Monster::addBody();
}

void Monster3::walk()
{
	m_walk = Monster3Action::getInstance()->getMonsterWalkAnimate()->clone();
	Monster::walk();
}

void Monster3::die()
{
	Monster::die();
}

void Monster3::done()
{
	Monster::done();
}

#pragma endregion

#pragma region - Monster 4 -
Monster4::Monster4()
{
	this->initWithFile("Monster1_Stand.png");	
	this->setTag(MONSTER_TAG);

	m_isDieing = false;
	m_HP = 4;
	m_speed = 50;
	m_damage = 1;

	Monster::addBody();
}

void Monster4::walk()
{
	m_walk = Monster4Action::getInstance()->getMonsterWalkAnimate()->clone();
	Monster::walk();
}

void Monster4::die()
{
	m_die = Monster4Action::getInstance()->getMonsterDieAnimate()->clone();
	Monster::die();
}

void Monster4::done()
{
	Monster::done();
}

#pragma endregion

#pragma region - Monster 5 -
Monster5::Monster5()
{
	Monster::addBody();
}

void Monster5::walk()
{

}

void Monster5::die()
{

}

void Monster5::done()
{
	
}

#pragma endregion

#pragma region - Monster -
Monster::Monster()
{
	m_timeDelay = 0;
	m_totalCurrentMonster++;


	m_walk = m_die = m_done = nullptr;
	addBody();
}

void Monster::walk()
{
	m_move = MoveTo::create(this->getPosition().x/ m_speed, Vec2(0, this->getPosition().y));
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(Monster::done, this));
	this->runAction(RepeatForever::create(m_walk));
	this->runAction(Sequence::create(DelayTime::create(m_timeDelay) ,m_move, func, nullptr));
}

void Monster::die()
{
	this->getPhysicsBody()->removeFromWorld();
	this->setPosition(Vec2(this->getPosition().x, this->getPosition().y - this->getContentSize().height / 2 + this->getContentSize().width / 2));
	this->stopAllActions();

	CallFunc *func = CallFunc::create(CC_CALLBACK_0(Monster::destroyed, this));

	CallFunc *fun2 = CallFunc::create([&] 
	{
		Player::getInstance()->setSouls(Player::getInstance()->getSouls() + 1);
		auto item = dropItem();

		if(item != nullptr)
		{
			item->setPosition(this->getPosition());
			item->animate();
			ItemManager::getInstacce()->addItem(item);
			Director::getInstance()->getRunningScene()->addChild(item);
		}
	});

	m_isDieing = true;

	if(m_die != nullptr)
		this->runAction(Sequence::create(m_die, func, fun2, nullptr));
	else
		this->runAction(Sequence::create(func, fun2, nullptr));
}

void Monster::freezed()
{
	this->pauseSchedulerAndActions();

	//Monster* sprite = new Monster();
	//sprite->setVisible(false);
	Sprite* sprite = Sprite::create("iced.png");
	sprite->setScaleX(this->getContentSize().height / sprite->getContentSize().width);
	sprite->setScaleY(this->getContentSize().height / sprite->getContentSize().height);
	sprite->setOpacity((int)(0.5*255));
	sprite->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(sprite);
	CallFuncN* func = CallFuncN::create([&, sprite](Node* monster)
	{
		((Monster*)monster)->removeFromParentAndCleanup(true); 
		this->resumeSchedulerAndActions(); 
	});

	sprite->runAction(Sequence::create(DelayTime::create(BULLET_ICE_TIME), func, nullptr));
}

void Monster::burned()
{
	ParticleSystemQuad *prtBurning = ParticleSystemQuad::create("burning.plist"); //particle tu tao
	//ParticleFire *prtBurning = ParticleFire::create();//particle cua cocos
	prtBurning->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);

	prtBurning->setLife(0.01);
	this->addChild(prtBurning);
	CallFuncN* func = CallFuncN::create([&, prtBurning](Node* monster)
	{
		((Monster*)monster)->removeFromParentAndCleanup(true); 
	});

	prtBurning->runAction(Sequence::create(DelayTime::create(0.5), func, nullptr));
}

void Monster::done()
{
	this->getPhysicsBody()->removeFromWorld();
	this->stopAllActions();
	CallFunc *func = CallFunc::create(CC_CALLBACK_0(Monster::destroyed, this));
	CallFunc *func2 = CallFunc::create([&]{Player::getInstance()->attacked(this->m_damage); });
	this->runAction(Sequence::create(func2, func, nullptr));
	this->destroyed();
}

//return true la monster chet
bool Monster::attacked(Bullet* bullet)
{
	//auto sprite = Sprite::create("LightingItem_1.png");
	//sprite->setPosition(this->getPosition());
	//parent->addChild(sprite);

	if(bullet->getBullettype() != LIGHTING)
		m_HP -= ((bullet->getdamage() + Player::getInstance()->getDamageBonus()) * Player::getInstance()->getdamageMulti());
	
	#pragma region -Bullet Types-
	switch (bullet->getBullettype())
	{
		case NORMAL:
			this->runAction(Sequence::create(TintTo::create(0, 255, 0, 0), DelayTime::create(0.25), TintTo::create(0, 255, 255, 255), nullptr));
			break;

		case FIRE:
			this->burned();
			this->runAction(Sequence::create(TintTo::create(0, 255, 0, 0), DelayTime::create(0.25), TintTo::create(0, 255, 255, 255), nullptr));
			break;

		case LIGHTING:		
			//this->runAction(Sequence::create(TintTo::create(0, 255, 0, 0), DelayTime::create(0.25), TintTo::create(0, 255, 255, 255), nullptr));
			((Lighting*)bullet)->createLightingCircle(this);
			break;

		case WATER:
			this->runAction(Sequence::create(TintTo::create(0, 255, 0, 0), DelayTime::create(0.25), TintTo::create(0, 255, 255, 255), nullptr));
			break;

		case ICE:
			this->freezed();
			this->runAction(Sequence::create(TintTo::create(0, 255, 0, 0), DelayTime::create(0.25), TintTo::create(0, 255, 255, 255), nullptr));
			break;
	}
	#pragma endregion
	if(!bullet->isthrough())
	{
		/*if(bullet->isCleave())
		{
			((Lighting*)bullet)->createLightingCircle(this);
			bullet->removeFromParentAndCleanup(true);
		}
		else*/
			bullet->removeFromParentAndCleanup(true);
	}

	if(m_HP <= 0)
	{
		return true;
	}
	
	return false;
}

bool Monster::attackedByLightingCircle()
{
	m_HP -= 1;

	if(m_HP <= 0)
	{
		return true;
	}

	this->runAction(Sequence::create(TintTo::create(0, 255, 0, 0), DelayTime::create(0.25), TintTo::create(0, 255, 255, 255), nullptr));

	return false;
}

void Monster::destroyed()
{
	m_totalCurrentMonster--;
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);
}

Item* Monster::dropItem()
{
	/*
	- Thunder: 10% - 1 11 21 31 41 51 61 71 81 91 || ( 0 - 9)
	- Ice: 10% - 0 10 20 30 40 50 60 70 80 90  || ( 10 - 19)
	- Fire: 10% - 2 12 22 32 42 52 62 72 82 92 || (20 - 29)
	- Water: 10% - 3 13 23 33 43 53 63 73 83 93 || (30 - 39)
	- Double Damage: x2 Damage during x time: 10% - 4 14 24 34 44 54 64 74 84 94 || (40 - 49)
	- Bonus Damage: +1 Damage during the game: 15%  - 5 15 25 35 45 55 65 75 85 95 6 16 26 36 46 || (50 - 64)
	- 3 tia: 5% - 56 66 76 86 96 || (65 - 69)
	- Heal:  +1 HP: 5%  (70 - 74)
	*/
	int goon = rand() % 2;
	if(goon == 0)
		return nullptr;

	int num = rand() % 100; // 0 -> 99

	if (num >= 0 && num < 10)
	{
		//return Thuner Item
		return new LightingItem();
	}
	else if (num < 20)
	{
		//return Ice item
		return new IceItem();
	}
	else if(num < 30)
	{
		//return Fire item
		return new FireItem();
	}
	else if(num < 40)
	{
		//return Water item
		return new WaterItem();
	}
	else if(num < 50)
	{
		//return Double damage item
	}
	else if(num < 65)
	{
		//return Bonus damage item
	}
	else if(num < 70)
	{
		//return Three ray item
	}
	else if(num < 75)
	{
		//return heal item
	}
	
	return nullptr;
}

void Monster::setTimeDelay(float time)
{
	m_timeDelay = time;
}

int Monster::getTotalCurrentMonster()
{
	return m_totalCurrentMonster;
}

void Monster::addBody()
{
	auto targetBody = PhysicsBody::createBox(Size(this->getContentSize().width * 0.9f, this->getContentSize().height * 0.9f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	targetBody->setContactTestBitmask(MONSTER_CONTACT_TEST_BITMASK);
	targetBody->setCollisionBitmask(MONSTER_COLLISION_BITMASK);
	targetBody->setCategoryBitmask(MONSTER_CONTACT_CATEGORY);	
	this->setPhysicsBody(targetBody);
}
#pragma endregion
