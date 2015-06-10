#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Define.h"
#include "Bullet.h"

USING_NS_CC;

class Player : public Sprite
{
	public:		
		static Player*  getInstance();

		void		load(); // ham init ton tai nen phai dung ham khac
		void		attack(Touch* touches); //	ban'
		void		die(); // chet
		bool		attacked(int damage); // bi tan cong
		void		setDamageBonus(int damage); 
		void		setDamageMulti(int damage);
		void		setSouls(int souls);
		void		setBulletType(BulletType bulletType);
		int			getdamageMulti();
		int			getDamageBonus();
		int			getSouls();
		int			getHP();
		BulletType	getBulletType();
		bool		isFinishAction();

	private:			
		Player();

		static Player* m_instance;
		BulletType m_bulletType;

		int m_HP,
			m_damageBonus,
			m_damageMulti,
			m_souls;			
		
		bool m_isSplit,
			 m_isDoubleDamage,
			 m_isGameOver,//gameover va wingame khong can cho player
			 m_isFinishAction,
			 m_isWinGame; // true khi thua

		Node* m_parent;
			
		
	//CREATE_FUNC(Player);
};

#endif
