#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Define.h"

USING_NS_CC;

class Player : public Sprite
{
	public:		
		static Player*  getInstance();
		void load(); // ham init ton tai nen phai dung ham khac
		void attack(); //	ban'
		void die(); // chet
		
	private:	
		static Player* m_instance;
		Player();
		int m_HP;
		int m_damageBonus;
		bool m_isDoubleDamage;
		//BulletTypes m_bulletType;
		bool m_isSplit;
		
	//CREATE_FUNC(Player);
};

#endif
