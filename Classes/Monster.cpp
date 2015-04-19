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
	m_HP = 3;
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
	m_HP = 3;
	m_speed = 100;
	m_damage = 1;
	m_walk = Monster2Action::getInstance()->getMonsterWalkAnimate()->clone();
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

}

void Monster3::walk()
{

}

void Monster3::die()
{

}

void Monster3::freezed()
{

}

void Monster3::done()
{
	
}

bool Monster3::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}
#pragma endregion

#pragma region - Monster 4 -
Monster4::Monster4()
{

}

void Monster4::walk()
{

}

void Monster4::die()
{

}

void Monster4::freezed()
{

}

void Monster4::done()
{
	
}

bool Monster4::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
}
#pragma endregion

#pragma region - Monster 5 -
Monster5::Monster5()
{

}

void Monster5::walk()
{

}

void Monster5::die()
{

}

void Monster5::freezed()
{

}

void Monster5::done()
{
	
}

bool Monster5::attacked(Bullet* bullet)
{
	return Monster::attacked(bullet);
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

	Monster* sprite = new Monster();
	sprite->setVisible(false);
	this->addChild(sprite);
	CallFuncN* func = CallFuncN::create([&, sprite](Node* monster)
	{
		((Monster*)monster)->removeFromParentAndCleanup(true); 
		this->resumeSchedulerAndActions(); 
	});

	sprite->runAction(Sequence::create(DelayTime::create(BULLET_ICE_TIME), func, nullptr));
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

	m_HP -= ((bullet->getdamage() + Player::getInstance()->getDamageBonus()) * Player::getInstance()->getdamageMulti());

	if(m_HP <= 0)
	{
		return true;
	}
	
	#pragma region -Bullet Types-
	switch (bullet->getBullettype())
	{
		case NORMAL:
			break;

		case FIRE:
			break;

		case LIGHTING:			
			break;

		case WATER:

			break;

		case ICE:
			this->freezed();
			break;
	}
	#pragma endregion

	bullet->removeFromParentAndCleanup(true);
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
