#include "Monster.h"
#include "Animation.h"
#include "Define.h"

#pragma region - Monster1 -

Monster1::Monster1()
{
	this->initWithFile("Monster1_Stand.png");
	this->setTag(MONSTER_TAG);

	m_isDieing = false;
	m_HP = 3;
	m_speed = 20;
	//m_stun = Monster1Action::getInstance()->getMonsterStunAnimate()->clone();
}

void Monster1::walk()
{
	m_walk = Monster1Action::getInstance()->getMonsterWalkAnimate()->clone();
	m_move = MoveTo::create(10, Vec2(0, this->getPosition().y));
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(Monster1::done, this));
	this->runAction(RepeatForever::create(m_walk));
	this->runAction(Sequence::create(m_move, func, nullptr));
}

void Monster1::die()
{
	if(m_isDieing)
		return;

	this->setPosition(Vec2(this->getPosition().x, this->getPosition().y - this->getContentSize().height / 2 + this->getContentSize().width / 2));
	this->stopAllActions();
	m_die = Monster1Action::getInstance()->getMonsterDieAnimate()->clone();
	CallFunc *func = CallFunc::create(CC_CALLBACK_0(Monster1::destroyed, this));
	m_isDieing = true;
	this->runAction(Sequence::create(m_die, func, nullptr));
}

void Monster1::stun()
{

}

void Monster1::done()
{
	this->setAnchorPoint(Vec2(0, 0.5));
	this->stopAllActions();
	m_done = Monster1Action::getInstance()->getMonsterDoneAnimate()->clone();
	CallFunc *func = CallFunc::create(CC_CALLBACK_0(Monster1::destroyed, this));
	this->runAction(Sequence::create(m_done, func, nullptr));
}

#pragma endregion

#pragma region - Monster2 -

Monster2::Monster2()
{
	this->initWithFile("Monster1_Stand.png");	
	this->setTag(MONSTER_TAG);

	m_isDieing = false;
	m_HP = 3;
	m_speed = 20;
	m_walk = Monster2Action::getInstance()->getMonsterWalkAnimate()->clone();
	//m_die = Monster1Action::getInstance()->getMonsterDieAnimate()->clone();
	//m_stun = Monster1Action::getInstance()->getMonsterStunAnimate()->clone();
	//m_move = MoveTo::create(10, Vec2(0, this->getPosition().y));

}

void Monster2::walk()
{
	m_move = MoveTo::create(10, Vec2(0, this->getPosition().y));
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(Monster2::done, this));
	this->runAction(RepeatForever::create(m_walk));
	this->runAction(Sequence::create(m_move, func, nullptr));
}

void Monster2::die()
{
	destroyed();
}

void Monster2::stun()
{

}

void Monster2::done()
{
	destroyed();
}

#pragma endregion

#pragma region - Monster -
Monster::Monster()
{

}

void Monster::walk()
{

}

void Monster::die()
{

}

void Monster::stun()
{

}

void Monster::done()
{

}

void Monster::destroyed()
{
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);
}
#pragma endregion
