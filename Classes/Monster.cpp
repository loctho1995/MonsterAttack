#include "Monster.h"
#include "Animation.h"
#include "Define.h"
#include "Item.h"

#pragma region - Monster 1 -

Monster1::Monster1()
{
	this->initWithFile("Monster1_Stand.png");
	this->setTag(MONSTER_TAG);

	m_isDieing = false;
	m_HP = 1;
	m_speed = 100;
	m_damage = 1;

	Monster::Monster();
}

void Monster1::walk()
{
	m_walk = Monster1Action::getInstance()->getMonsterWalkAnimate()->clone();	
	Monster::walk();
}

void Monster1::die()
{
	m_die = Monster1Action::getInstance()->getMonsterDieAnimate()->clone();
	Monster::die();
}

void Monster1::freezed()
{
	Monster::freezed();
}

void Monster1::done()
{
	m_done = Monster1Action::getInstance()->getMonsterDoneAnimate()->clone();
	Monster::done();
}

bool Monster1::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}
#pragma endregion

#pragma region - Monster 2 -

Monster2::Monster2()
{
	this->initWithFile("Monster1_Stand.png");	
	this->setTag(MONSTER_TAG);

	m_isDieing = false;
	m_HP = 2;
	m_speed = 100;
	m_damage = 1;
	m_walk = Monster2Action::getInstance()->getMonsterWalkAnimate()->clone();
	
	Monster::Monster();
}

void Monster2::walk()
{
	m_move = MoveTo::create(this->getPosition().x / m_speed, Vec2(0, this->getPosition().y));
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(Monster2::done, this));
	this->runAction(RepeatForever::create(m_walk));
	this->runAction(Sequence::create(m_move, func, nullptr));
}

void Monster2::die()
{
	m_die = Monster1Action::getInstance()->getMonsterDieAnimate()->clone();
	Monster::die();
}

void Monster2::freezed()
{

}

void Monster2::done()
{	
	m_done = Monster1Action::getInstance()->getMonsterDoneAnimate()->clone();
	Monster::done();
}

bool Monster2::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}
#pragma endregion

#pragma region - Monster 3 -
Monster3::Monster3()
{
	m_speed - 160;
	m_damage = 1;
	m_HP = 1;
}

void Monster3::walk()
{
	Monster::walk();
}

void Monster3::die()
{
	Monster::die();
}

void Monster3::freezed()
{
	Monster::freezed();
}

void Monster3::done()
{
	Monster::done();
}

bool Monster3::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}
#pragma endregion

#pragma region - Monster 4 -
Monster4::Monster4()
{
	m_HP = 10;
	m_speed = 80;
	m_damage = 2;
}

void Monster4::walk()
{
	Monster::walk();
}

void Monster4::die()
{
	Monster::die();
}

void Monster4::freezed()
{
	Monster::freezed();
}

void Monster4::done()
{
	Monster::done();
}

bool Monster4::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}
#pragma endregion

#pragma region - Monster 5 -
Monster5::Monster5()
{
	m_HP = 2;
	m_speed = 100;
	m_damage = 3;
}

void Monster5::walk()
{
	Monster::walk();
}

void Monster5::die()
{
	Monster::die();
}

void Monster5::freezed()
{
	Monster::freezed();
}

void Monster5::done()
{
	Monster::done();
}

bool Monster5::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}
#pragma endregion

#pragma region - Monster -
Monster::Monster()
{
	initPhySicBody();
}

void Monster::initPhySicBody()
{
	auto targetBody = PhysicsBody::createCircle(this->getContentSize().width / 2, PhysicsMaterial(0.1f, 1.0f, 0.0f));
	targetBody->setContactTestBitmask(0x1);
	//targetBody->setCollisionBitmask(MONSTER_COLLISION_BITMASK);
	//targetBody->setCategoryBitmask(MONSTER_CONTACT_CATEGORY);
	this->setPhysicsBody(targetBody);
}

void Monster::walk()
{
	m_move = MoveTo::create(this->getPosition().x/ m_speed, Vec2(0, this->getPosition().y));
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(Monster::done, this));
	this->runAction(RepeatForever::create(m_walk));
	this->runAction(Sequence::create(m_move, func, nullptr));
}

void Monster::die()
{
	this->getPhysicsBody()->removeFromWorld();
	this->setPosition(Vec2(this->getPosition().x, this->getPosition().y - this->getContentSize().height / 2 + this->getContentSize().width / 2));
	this->stopAllActions();

	CallFunc *func = CallFunc::create(CC_CALLBACK_0(Monster1::destroyed, this));

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
	this->runAction(Sequence::create(m_die, func, fun2, nullptr));
}

void Monster::freezed()
{
	this->pauseSchedulerAndActions();

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
	//prtBurning->setScaleX(0.25);
	//prtBurning->setScaleY(0.25);
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
	this->runAction(Sequence::create(m_done, func2, func, nullptr));
}

//return true la monster chet
bool Monster::attacked(Bullet* bullet)
{
	m_HP -= ((bullet->getdamage() + Player::getInstance()->getDamageBonus()) * Player::getInstance()->getdamageMulti());
	
	#pragma region -Bullet Types-
	switch (bullet->getBullettype())
	{
		case NORMAL:
			this->runAction(Sequence::create(TintTo::create(0, 255, 0, 0), DelayTime::create(0.25), 
												TintTo::create(0, 255, 255, 255), nullptr));
			break;

		case FIRE:
			this->burned();
			this->runAction(Sequence::create(TintTo::create(0, 255, 0, 0), DelayTime::create(0.25), 
												TintTo::create(0, 255, 255, 255), nullptr));
			break;

		case LIGHTING:	
			//this->runAction(Sequence::create(TintTo::create(0, 255, 0, 0), DelayTime::create(0.25), 
													//TintTo::create(0, 255, 255, 255), nullptr));
			break;

		case WATER:
			this->runAction(Sequence::create(TintTo::create(0, 255, 0, 0), DelayTime::create(0.25), 
													TintTo::create(0, 255, 255, 255), nullptr));
			break;

		case ICE:
			this->freezed();
			this->runAction(Sequence::create(TintTo::create(0, 255, 0, 0), DelayTime::create(0.25), 
													TintTo::create(0, 255, 255, 255), nullptr));
			break;
	}
	#pragma endregion

	if(!bullet->isthrough())
	{
		if(bullet->isCleave())
		{
			Sprite *LightingCircle = Sprite::create("thunderCircle.png");
			LightingCircle->setTag(LIGHTINGCIRCLE_TAG);
			bullet->getParent()->addChild(LightingCircle);
			LightingCircle->setPosition(bullet->getPosition().x, bullet->getPosition().y);
			//LightingCircle->setVisible(false);

			bullet->removeFromParentAndCleanup(true);

			////particle
			//ParticleSystemQuad *prtmid = ParticleSystemQuad::create("thunderCircleprt.plist");
			////ParticleSystemQuad *prttopleft = ParticleSystemQuad::create("thunderCircleprt.plist");
			////ParticleSystemQuad *prttopright = ParticleSystemQuad::create("thunderCircleprt.plist");
			////ParticleSystemQuad *prtbotleft = ParticleSystemQuad::create("thunderCircleprt.plist");
			////ParticleSystemQuad *prtbotright = ParticleSystemQuad::create("thunderCircleprt.plist");
			////prtmid->setLife(0.01);
			////prttopleft->setLife(0.01);
			////prttopright->setLife(0.01);
			////prtbotleft->setLife(0.01);
			////prtbotright->setLife(0.01);
			//LightingCircle->addChild(prtmid);
			////thunderCircle->addChild(prttopleft);
			////thunderCircle->addChild(prttopright);
			////thunderCircle->addChild(prtbotleft);
			////thunderCircle->addChild(prtbotright);
			//prtmid->setPosition(LightingCircle->getContentSize().width / 2, LightingCircle->getContentSize().height / 2);
			////prttopleft->setPosition(thunderCircle->getContentSize().width / 4, thunderCircle->getContentSize().height / 4 * 3);
			////prttopright->setPosition(thunderCircle->getContentSize().width / 4 * 3, thunderCircle->getContentSize().height / 4 * 3);
			////prtbotleft->setPosition(thunderCircle->getContentSize().width / 4, thunderCircle->getContentSize().height / 4);
			////prtbotright->setPosition(thunderCircle->getContentSize().width / 4 * 3, thunderCircle->getContentSize().height / 4);

			//physics
			PhysicsBody *LightingCircleBody = PhysicsBody::createCircle(0.1 * bullet->getContentSize().width * 4 / 2, PhysicsMaterial(0, 0, 0), Vec2::ZERO);
			LightingCircleBody->setDynamic(false);
			LightingCircleBody->setContactTestBitmask(0x1);
			//LightingCircleBody->setCategoryBitmask(0x00); // va cham
			LightingCircleBody->setCollisionBitmask(0x00); //chat lieu

			LightingCircle->setScale(0.1 * bullet->getContentSize().width * 4 / LightingCircle->getContentSize().width);
			LightingCircle->runAction(ScaleTo::create(0.5, bullet->getContentSize().width * 4 / LightingCircle->getContentSize().width));
			//thunderCircle->setScale(bullet->getContentSize().width * 4 / thunderCircle->getContentSize().width);
			
			LightingCircle->setPhysicsBody(LightingCircleBody);

			LightingCircle->runAction(RepeatForever::create(RotateBy::create(3, 360)));


			CallFuncN* func = CallFuncN::create([&, LightingCircle](Node* monster)
			{
				((Monster*)monster)->removeFromParentAndCleanup(true); 
			});

			LightingCircle->runAction(Sequence::create(DelayTime::create(LIGHTINGCIRCLE_TIME), func, nullptr));

		}
		else
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

	this->runAction(Sequence::create(TintTo::create(0, 255, 0, 0), DelayTime::create(0.25), 
											TintTo::create(0, 255, 255, 255), nullptr));
	return false;
}

void Monster::destroyed()
{
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
#pragma endregion
