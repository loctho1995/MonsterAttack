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

void Monster1::done()
{
	m_done = Monster1Action::getInstance()->getMonsterDoneAnimate()->clone();
	Monster::done();
}

bool Monster1::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}

bool Monster1::attackedByLightingCircle()
{
	return Monster::attackedByLightingCircle();
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

}

void Monster2::walk()
{
	m_walk = Monster2Action::getInstance()->getMonsterWalkAnimate()->clone();
	Monster::walk();
	/*m_move = MoveTo::create(this->getPosition().x / m_speed, Vec2(0, this->getPosition().y));
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(Monster2::done, this));
	this->runAction(RepeatForever::create(m_walk));
	this->runAction(Sequence::create(m_move, func, nullptr));*/
}

void Monster2::die()
{
	m_die = Monster1Action::getInstance()->getMonsterDieAnimate()->clone();
	Monster::die();
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

bool Monster2::attackedByLightingCircle()
{
	return Monster::attackedByLightingCircle();
}

#pragma endregion

#pragma region - Monster 3 -
Monster3::Monster3()
{
	m_HP = 4;
	m_damage = 1;
	m_speed = 80;
}

void Monster3::walk()
{

}

void Monster3::die()
{

}

void Monster3::done()
{
	
}

bool Monster3::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}

bool Monster3::attackedByLightingCircle()
{
	return Monster::attackedByLightingCircle();
}
#pragma endregion

#pragma region - Monster 4 -
Monster4::Monster4()
{
	m_HP = 6;
	m_damage = 1;
	m_speed = 90;
}

void Monster4::walk()
{

}

void Monster4::die()
{

}

void Monster4::done()
{
	
}

bool Monster4::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}

bool Monster4::attackedByLightingCircle()
{
	return Monster::attackedByLightingCircle();
}
#pragma endregion

#pragma region - Monster 5 -
Monster5::Monster5()
{
	m_HP = 1;
	m_damage = 2;
	m_speed = 120;
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

bool Monster5::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}

bool Monster5::attackedByLightingCircle()
{
	return Monster::attackedByLightingCircle();
}
#pragma endregion

#pragma region - Monster 6 -
Monster6::Monster6()
{
	m_HP = 1;
	m_damage = 3;
	m_speed = 140;
}

void Monster6::walk()
{

}

void Monster6::die()
{

}

void Monster6::done()
{
	
}

bool Monster6::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}

bool Monster6::attackedByLightingCircle()
{
	return Monster::attackedByLightingCircle();
}
#pragma endregion

#pragma region - Monster 7 -
Monster7::Monster7()
{
	m_HP = 3;
	m_damage = 2;
	m_speed = 120;
}

void Monster7::walk()
{

}

void Monster7::die()
{

}

void Monster7::done()
{
	
}

bool Monster7::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}

bool Monster7::attackedByLightingCircle()
{
	return Monster::attackedByLightingCircle();
}
#pragma endregion

#pragma region - Monster 8 -
Monster8::Monster8()
{
	m_HP = 5;
	m_damage = 3;
	m_speed = 120;
}

void Monster8::walk()
{

}

void Monster8::die()
{

}

void Monster8::done()
{
	
}

bool Monster8::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}

bool Monster8::attackedByLightingCircle()
{
	return Monster::attackedByLightingCircle();
}
#pragma endregion

#pragma region - Monster 9 -
Monster9::Monster9()
{
	m_HP = 6;
	m_damage = 3;
	m_speed = 100;
}

void Monster9::walk()
{

}

void Monster9::die()
{

}

void Monster9::done()
{
	
}

bool Monster9::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}

bool Monster9::attackedByLightingCircle()
{
	return Monster::attackedByLightingCircle();
}
#pragma endregion

#pragma region - Monster 10 -
Monster10::Monster10()
{
	m_HP = 7;
	m_damage = 3;
	m_speed = 110;
}

void Monster10::walk()
{

}

void Monster10::die()
{

}

void Monster10::done()
{
	
}

bool Monster10::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}

bool Monster10::attackedByLightingCircle()
{
	return Monster::attackedByLightingCircle();
}

#pragma endregion

#pragma region - Monster -
Monster::Monster()
{

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

Monster::~Monster()
{
	
}
#pragma endregion
