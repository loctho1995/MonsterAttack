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

		virtual void walk();
		virtual void die();
		virtual void stun();
		virtual void done(); //ham duoc goi khi cham vao trong hinh tron cua Player
		virtual void destroyed();
		
	protected:
		int m_HP;	
		float m_speed;
		bool m_isDieing; //biến này = true khi dang chay animation die, tranh truong hop dang chay animation die thi dan ban trung animation bi cancel
		Animate *m_walk, *m_die, *m_done, *m_stun;
		MoveTo* m_move;
};

class Monster1 : public Monster
{
public:
	Monster1();
	virtual void walk();
	virtual void die();
	virtual void stun();
	virtual void done();	

private:
};

class Monster2 : public Monster
{
public:
	Monster2();
	virtual void walk();
	virtual void die();
	virtual void stun();
	virtual void done();	

private:
};


