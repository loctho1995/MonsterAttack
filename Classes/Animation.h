#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "cocos2d.h"
#include "Define.h"
USING_NS_CC;

class SpriteAction : public Animation // class truu tuong i{
{
public:
	~SpriteAction(void);
	virtual void loadAnimation(SpriteFrameCache* spriteFrameCache) = 0 ; // Ham nap vao bo nho cac file .list
};

class PlayerAction : public SpriteAction // Class Chua cac Animation của player
{
public:
	void loadAnimation(SpriteFrameCache* spriteFrameCache);
	Animate* getPlayerActtackAnimate() { return m_attackAnimate ;}

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
	Animate* m_attackAnimate; // acttack animation  player
};

class MonsterAction : public SpriteAction   // Animation cua cac con quai abstract class
{
protected:
	 Animate* m_walkAnimate; // Di
	 Animate* m_dieAnimate;  // Chet
	 Animate* m_stunAnimate; // bi freezed
	 Animate* m_doneAnimate;
	 virtual Animate* getMonsterWalkAnimate() = 0; //
	 virtual Animate* getMonsterDieAnimate() = 0; //
	 virtual Animate* getMonsterStunAnimate() = 0; //
	 virtual Animate* getMonsterDoneAnimate() = 0; 
};

class Monster1Action : public MonsterAction // Animation quai 1
{
public:
	void loadAnimation(SpriteFrameCache* spriteFrameCache);
	Animate* getMonsterWalkAnimate() {return m_walkAnimate;}
	Animate* getMonsterDieAnimate() {return m_dieAnimate;}
	Animate* getMonsterStunAnimate() {return m_stunAnimate;}
	Animate* getMonsterDoneAnimate() { return m_doneAnimate; }

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
	Monster1Action();
	static Monster1Action* m_instance;
};

class Monster2Action : private MonsterAction // Animation quai 2
{
public:
	void loadAnimation(SpriteFrameCache* spriteFrameCache);
	Animate* getMonsterWalkAnimate() {return m_walkAnimate;}
	Animate* getMonsterDieAnimate() {return m_dieAnimate;}
	Animate* getMonsterStunAnimate() {return m_stunAnimate;}
	Animate* getMonsterDoneAnimate() { return m_doneAnimate; }

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
	Monster2Action();
	static Monster2Action* m_instance;
};

static class AnimationManager    // class quan li cac Animation
{
public:
	static void loadAnimationByTag(MonsterType arrMonsterType[],SpriteFrameCache* spriteFrameCache); // 1 man co cac loai quai khac nhau... Nhap vao cac loai quai va chi load animation cua cac quai do
	static Animate* getWalkAnimationByTag(MonsterType type);
	static Animate* getDieAnimationByTag(MonsterType type);
	static Animate* getStunAnimationByTag(MonsterType type);
};

#endif