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

	//virtual void move(cocos2d::Touch* touch);

};

class Fire: public Bullet
{

public:
	Fire()
	{
		this->initWithFile("Fire.png");
		m_isCleave = false;
		m_isThrough = false;
		m_damage = 2;
		m_bullettype = FIRE;
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
		this->initWithFile("Lighting.png");
		m_isCleave = true;
		m_isThrough = false;
		m_damage = 1;
		m_radius = 50;
		m_bullettype = LIGHTING;
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
		this->initWithFile("Ice.png");
		m_isCleave = false;
		m_isThrough = false;
		m_damage = 1;
		m_stunTime = 1;
		m_bullettype = ICE;
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
		this->initWithFile("Water.png");
		m_isCleave = false;
		m_isThrough = true;
		m_damage = 1;
		m_bullettype = WATER;
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