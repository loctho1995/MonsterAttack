#include "Player.h"
#include "cocos2d.h"
#include "Animation.h"


USING_NS_CC;
Player* Player::m_instance = 0;

Player::Player()
{
	//this->initWithSpriteFrameName("Player.png");
	this->initWithFile("Player.png");
	this->setTag(PLAYER_TAG);
	m_HP = 10;
	m_damageBonus = 0;
	m_isDoubleDamage = false;
	//m_bulletType = Normal;
	m_isSplit = false;	
}

Player* Player::getInstance()
{
	if(m_instance == 0)
	{
		m_instance = new Player();
		return m_instance;
	}
	else
		return m_instance;
}

void Player::load()
{
	m_HP = 10;
	m_damageBonus = 0;
	m_isDoubleDamage = false;
	m_isSplit = false;
}

void Player::attack()
{
	//lambda function 
	//http://www.stdio.vn/articles/read/56-c11-lambda
	auto func = CallFunc::create([]
	{ 
		m_instance->initWithFile("Player.png");
	});

	m_instance->runAction(Sequence::create(PlayerAction::getInstance()->getPlayerActtackAnimate(), func ,nullptr));
}

void Player::die()
{
	
}