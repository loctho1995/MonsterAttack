#pragma once
#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include "cocos2d.h"
#include "Define.h"
USING_NS_CC;

class SpriteAction : public Animation // class truu tuong 
{

public:
	~SpriteAction(void);
	virtual void loadAnimation(SpriteFrameCache* spriteFrameCache) = 0 ; // Ham nap vao bo nho cac file .list
};

class PlayerAction : public SpriteAction // Class Chua cac Animation của player
{
public:
	void loadAnimation(SpriteFrameCache* spriteFrameCache);
	Animation* getPlayerActtackAnimation() { return m_attackAnimation ;}
	static PlayerAction* getInstance()
	{
		if(m_instance == 0)
		{
			m_instance = new PlayerAction();
			return m_instance;
		}
		return m_instance;
	}
private:
	PlayerAction();
	static PlayerAction* m_instance; // Doi tuong duy nhat cua class
	Animation* m_attackAnimation; // acttack animation  player
};
class MonsterAction : public SpriteAction   // Animation cua cac con quai abstract class
{
protected:
	 Animation* m_walkAnimation; // Di
	 Animation* m_dieAnimation;  // Chet
	 Animation* m_stunAnimation; // bi stun
	 virtual Animation* getMonsterWalkAnimation() = 0; //
	 virtual Animation* getMonsterDieAnimation() = 0; //
	 virtual Animation* getMonsterStunAnimation() = 0; //
};
class Monster1Action : private MonsterAction // Animation quai 1
{
public:
	void loadAnimation(SpriteFrameCache* spriteFrameCache);
	Animation* getMonsterWalkAnimation() {return m_walkAnimation;}
	Animation* getMonsterDieAnimation() {return m_dieAnimation;}
	Animation* getMonsterStunAnimation() {return m_stunAnimation;}
	static Monster1Action* getInstance()
	{
		if(m_instance == 0)
		{
			m_instance = new Monster1Action();
			return m_instance;
		}
		return m_instance;
	}
private:
	Monster1Action() {};
	static Monster1Action* m_instance;
};
class Monster2Action : private MonsterAction // Animation quai 2
{
public:
	void loadAnimation(SpriteFrameCache* spriteFrameCache);
	Animation* getMonsterWalkAnimation() {return m_walkAnimation;}
	Animation* getMonsterDieAnimation() {return m_dieAnimation;}
	Animation* getMonsterStunAnimation() {return m_stunAnimation;}
	static Monster2Action* getInstance()
	{
		if(m_instance == 0)
		{
			m_instance = new Monster2Action();
			return m_instance;
		}
		return m_instance;
	}
private:
	Monster2Action() {};
	static Monster2Action* m_instance;
};
static class AnimationManager    // class quan li cac Animation
{
public:
	static void loadAnimationByTag(MonsterType arrMonsterType[],SpriteFrameCache* spriteFrameCache); // 1 man co cac loai quai khac nhau... Nhap vao cac loai quai va chi load animation cua cac quai do
	static Animation* getWalkAnimationByTag(MonsterType type);
	static Animation* getDieAnimationByTag(MonsterType type);
	static Animation* getStunAnimationByTag(MonsterType type);
};

#endif