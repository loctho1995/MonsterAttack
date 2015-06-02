#ifndef __MONSTER__H__
#define __MONSTER__H__

#include "cocos2d.h"
#include "Define.h"
#include "Player.h"
#include "Bullet.h"
#include "Item.h"

USING_NS_CC;

class Monster : public Sprite
{
	public:
		Monster();

		static int getTotalCurrentMonster();

		int getHP()
		{
			return m_HP;
		};		

		void setHP(int hp)
		{
			m_HP = hp;
		};

		float getSpeed()
		{
			return m_speed;
		};

		float setSpeed(float speed)
		{
			m_speed = speed;
		};

		int setDamage(int damage)
		{
			m_damage = damage;
		}

		virtual void walk();
		virtual void die();
		virtual void freezed();
		virtual void burned();
		virtual void done(); //ham duoc goi khi cham vao trong hinh tron cua Player
		virtual bool attacked(Bullet* bullet);
		virtual bool attackedByLightingCircle();
		virtual void destroyed();		 
		virtual void addBody();
		virtual Item* dropItem();
		virtual void setTimeDelay(float time);
		
	protected:
		int m_HP, m_damage;	
		float m_speed, m_timeDelay;
		bool m_isDieing; //biến này = true khi dang chay animation die, tranh truong hop dang chay animation die thi dan ban trung animation bi cancel
		Animate *m_walk, *m_die, *m_done, *m_stun;
		MoveTo* m_move;
		static int m_totalCurrentMonster;
};

class Monster1 : public Monster
{
public:
	Monster1();
	virtual void walk();
	virtual void die();
	virtual void done();	

private:
};

class Monster2 : public Monster
{
public:
	Monster2();
	virtual void walk();
	virtual void die();
	virtual void done();	

private:
};

class Monster3 : public Monster
{
public:
	Monster3();
	virtual void walk();
	virtual void die();
	virtual void done();	

private:
};

class Monster4 : public Monster
{
public:
	Monster4();
	virtual void walk();
	virtual void die();
	virtual void done();	

private:
};

class Monster5 : public Monster
{
public:
	Monster5();
	virtual void walk();
	virtual void die();
	virtual void done();	

private:
};
#endif

