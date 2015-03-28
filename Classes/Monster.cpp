#include "Monster.h"
#include "Animation.h"
#include "Define.h"

#pragma region - Monster1 -
Monster1::Monster1()
{
	this->initWithFile("Monster1_Stand.png");
	Monster1::m_HP = 3;
	Monster1::m_speed = 20;
	this->setTag(MONSTER1_TAG);
}

void Monster1::walk()
{
	this->runAction(RepeatForever::create(Monster1Action::getInstance()->getMonsterWalkAnimate()->clone()));
	this->runAction(MoveTo::create(10, Vec2(0, this->getPosition().y)));						
}

void Monster1::die()
{

}

void Monster1::stun()
{

}
#pragma endregion

Monster::Monster()
{

}