#include "cocos2d.h"
#include "Define.h"

USING_NS_CC;

class Monster : public Sprite
{
	public:
		Monster();

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

		void walk();
		void die();
		void stun();
		
	protected:
		int m_HP;	
		float m_speed;
};

class Monster1 : public Monster
{
public:
	Monster1();
	void walk();
	void die();
	void stun();
private:
};


