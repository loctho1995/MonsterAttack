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

void Player::attack(Touch* touches)
{
	//lambda function 
	//http://www.stdio.vn/articles/read/56-c11-lambda

	Vec2 touch = Vec2(touches->getLocationInView().x, touches->getLocationInView().y);

	auto func = CallFunc::create([&, touch]
	{ 
		auto bullet = BulletManager::create(m_instance->getBulletType());
		bullet->move(touch, m_instance, m_instance->getParent());		

		m_instance->initWithFile("Player.png");
		m_instance->m_isFinishAction = true;
	});

	m_instance->m_isFinishAction = false;
	m_instance->runAction(Sequence::create(PlayerAction::getInstance()->getPlayerActtackAnimate(), func ,nullptr));
}

bool Player::attacked(int damage)
{
	m_HP -= damage;

	this->runAction(Sequence::create(TintTo::create(0, 255, 0, 0), DelayTime::create(0.25), TintTo::create(0, 255, 255, 255), nullptr));

	if(m_HP <= 0)
		return true;
	return false;
}

void Player::die()
{
	m_isGameOver = true;
}

bool Player::isFinishAction()
{
	return m_isFinishAction;
}

int Player::getHP()
{
	return m_HP;
}