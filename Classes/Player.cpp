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
	m_damageMulti = 1;
	m_isDoubleDamage = false;
	m_bulletType = BulletType::NORMAL;
	m_isSplit = false;	
}

int Player::getSouls()
{
	return m_souls;
}

int Player::getDamageBonus()
{
	return m_damageBonus;
}

int Player::getdamageMulti()
{
	return m_damageMulti;
}

BulletType Player::getBulletType()
{
	return m_bulletType;
}

void Player::setBulletType(BulletType bulletType)
{
	m_bulletType = bulletType;
}

void Player::setDamageBonus(int damage)
{
	m_damageBonus = damage;
}

void Player::setDamageMulti(int damage)
{
	m_damageMulti = damage;
}

void Player::setSouls(int souls)
{
	m_souls = souls;
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

void Player::attacked(int damage)
{
	m_HP -= damage;

	if(m_HP <= 0)
		die();
}

void Player::die()
{
	m_isGameOver = true;
}