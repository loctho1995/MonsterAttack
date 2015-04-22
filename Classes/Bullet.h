#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"
#include "Define.h"

USING_NS_CC;

class Bullet: public Sprite
{
protected:
	int m_damage;
	bool m_isCleave;
	bool m_isThrough;
	BulletType m_bullettype;
	ParticleSystemQuad *prt;// paticle va bullet chua resize

public:
	Bullet()
	{
		this->initWithFile("Normal.png");
		m_isCleave = false;
		m_isThrough = false;
		m_damage = 1;
		m_bullettype = NORMAL;
	}

	virtual bool isCleave()
	{
		return this->m_isCleave;
	}

	virtual bool isthrough()
	{
		return this->m_isThrough;
	}

	virtual int getdamage()
	{
		return this->m_damage;
	}

	virtual BulletType getBullettype()
	{
		return this->m_bullettype;
	}

	//move(touches, sprite, layer);
	void move(cocos2d::Touch* touch, cocos2d::Sprite* sprite, cocos2d::Layer* layer);
};

class Normal: public Bullet
{

public:
	Normal()
	{
		this->initWithFile("BulletParticle/Normal.png");
		prt = ParticleSystemQuad::create("BulletParticle/Normal.plist");
		this->addChild(prt);
		prt->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
		prt->setScale(0.75f);
		prt->setLife(0.01f);
		m_isCleave = false;
		m_isThrough = false;
		m_damage = 1;
	}

	virtual bool isCleave()
	{
		return this->m_isCleave;
	}

	virtual bool isthrough()
	{
		return this->m_isThrough;
	}

	virtual int getdamage()
	{
		return this->m_damage;
	}

	virtual BulletType getBullettype()
	{
		return this->m_bullettype;
	}

	//virtual void move(cocos2d::Touch* touch);

};

class Fire: public Bullet
{

public:
	Fire()
	{
		this->initWithFile("BulletParticle/Fire.png");
		prt = ParticleSystemQuad::create("BulletParticle/Fire.plist");
		this->addChild(prt);
		prt->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
		//prt->setScale(0.5f);
		prt->setLife(0.05f);
		m_isCleave = false;
		m_isThrough = false;
		m_damage = 2;
	}

	virtual bool isCleave()
	{
		return this->m_isCleave;
	}

	virtual bool isthrough()
	{
		return this->m_isThrough;
	}

	virtual int getdamage()
	{
		return this->m_damage;
	}

	virtual BulletType getBullettype()
	{
		return this->m_bullettype;
	}

	//virtual void move(cocos2d::Touch* touch);

};

class Lighting: public Bullet
{
private:
	float m_radius;

public:
	Lighting()
	{
		this->initWithFile("BulletParticle/Lighting.png");
		prt = ParticleSystemQuad::create("BulletParticle/Lighting.plist");
		this->addChild(prt);
		prt->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
		prt->setScale(0.75f);
		prt->setLife(0.01f);
		m_isCleave = true;
		m_isThrough = false;
		m_damage = 1;
	}

	virtual bool isCleave()
	{
		return this->m_isCleave;
	}

	virtual bool isthrough()
	{
		return this->m_isThrough;
	}

	virtual int getdamage()
	{
		return this->m_damage;
	}

	virtual BulletType getBullettype()
	{
		return this->m_bullettype;
	}

	float getradius()
	{
		return this->m_radius;
	}

	//virtual void move(cocos2d::Touch* touch);
};

class Ice: public Bullet
{
private:
	float m_stunTime;

public:
	Ice()
	{
		this->initWithFile("BulletParticle/Ice.png");
		prt = ParticleSystemQuad::create("BulletParticle/Ice.plist");
		this->addChild(prt);
		prt->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
		prt->setScale(0.75f);
		prt->setLife(0.05f);
		m_isCleave = false;
		m_isThrough = false;
		m_damage = 1;
	}

	virtual bool isCleave()
	{
		return this->m_isCleave;
	}

	virtual bool isthrough()
	{
		return this->m_isThrough;
	}

	virtual int getdamage()
	{
		return this->m_damage;
	}

	virtual BulletType getBullettype()
	{
		return this->m_bullettype;
	}

	float getstunTime()
	{
		return this->m_stunTime;
	}

	//virtual void move(cocos2d::Touch* touch);

};

class Water: public Bullet
{

public:
	Water()
	{
		this->initWithFile("BulletParticle/Water.png");
		prt = ParticleSystemQuad::create("BulletParticle/Water.plist");
		this->addChild(prt);
		prt->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
		//prt->setScale(0.5f);
		prt->setLife(0.01f);
		m_isCleave = false;
		m_isThrough = true;
		m_damage = 1;
	}

	virtual bool isCleave()
	{
		return this->m_isCleave;
	}

	virtual bool isthrough()
	{
		return this->m_isThrough;
	}

	virtual int getdamage()
	{
		return this->m_damage;
	}

	virtual BulletType getBullettype()
	{
		return this->m_bullettype;
	}

	//virtual void move(cocos2d::Touch* touch);

};

class BulletManager
{
public:
	static Bullet* create(BulletType tag)
	{
		Bullet* bullet;

		switch(tag)
		{
		case NORMAL:
			bullet = new Normal();
			return bullet;

		case FIRE:
			bullet = new Fire();
			return bullet;

		case LIGHTING:
			bullet = new Lighting();
			return bullet;

		case ICE:
			bullet = new Ice();
			return bullet;

		case WATER:
			bullet = new Water();
			return bullet;
			
		default:
			bullet = new Bullet();
			return bullet;
		}
	}
	
	//ham nay dung de xac dinh diem dat dan truoc khi ban(return ve vi tri dat dan truoc khi ban)
	static Point findPosition(Sprite* sprite, Touch* touch);
};
#endif