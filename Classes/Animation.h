#ifndef __ANIMATION_H__
#define __ANIMATION_H__

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
	PlayerAction(){ m_attackAnimate = nullptr }
	static PlayerAction* m_instance; // Doi tuong duy nhat cua class
	Animate* m_attackAnimate; // acttack animation  player
};

class MonsterAction : public SpriteAction   // Animation cua cac con quai abstract class
{
protected:
	 Animate* m_walkAnimate; // Di
	 Animate* m_dieAnimate;  // Chet
	 Animate* m_stunAnimate; // bi stun
	 virtual Animate* getMonsterWalkAnimate() = 0; //
	 virtual Animate* getMonsterDieAnimate() = 0; //
	 virtual Animate* getMonsterStunAnimate() = 0; //
};

class Monster1Action : public MonsterAction // Animation quai 1
{
public:
	void loadAnimation(SpriteFrameCache* spriteFrameCache);
	Animate* getMonsterWalkAnimate() {return m_walkAnimate;}
	Animate* getMonsterDieAnimate() {return m_dieAnimate;}
	Animate* getMonsterStunAnimate() {return m_stunAnimate;}

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
	Monster1Action() 
	{
		m_walkAnimate = nullptr;
		m_dieAnimate  = nullptr;
		m_stunAnimate = nullptr;
	}
	
	static Monster1Action* m_instance;
};

class Monster2Action : private MonsterAction // Animation quai 2
{
public:
	void loadAnimation(SpriteFrameCache* spriteFrameCache);
	Animate* getMonsterWalkAnimate() {return m_walkAnimate;}
	Animate* getMonsterDieAnimate() {return m_dieAnimate;}
	Animate* getMonsterStunAnimate() {return m_stunAnimate;}
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
	Monster2Action() 
	{
		m_walkAnimate = nullptr;
		m_dieAnimate  = nullptr;
		m_stunAnimate = nullptr;
	}
	static Monster2Action* m_instance;
};


class EffectAnimation : public SpriteAction
{
protected :
	Animate* m_performAnimate;
	virtual Animate* getEffectPerformAnimate() = 0; //
};
class FireEffectAnimation : private EffectAnimation
{
public:
	void loadAnimation(SpriteFrameCache* spriteFrameCache);
	Animate* getEffectPerformAnimate() {return m_performAnimate;}
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
	FireEffectAnimation()
	{
		m_performAnimate = nullptr;
	}
	static FireEffectAnimation* m_instance;
};
class NormalEffectAnimation : private EffectAnimation
{
public:
	void loadAnimation(SpriteFrameCache* spriteFrameCache);
	Animate* getEffectPerformAnimate() {return m_performAnimate;}
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
	NormalEffectAnimation()
	{
		m_performAnimate = nullptr;
	}
	static NormalEffectAnimation* m_instance;
};
class LightingEffectAnimation : private EffectAnimation
{
public:
	void loadAnimation(SpriteFrameCache* spriteFrameCache);
	Animate* getEffectPerformAnimate() {return m_performAnimate;}
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
	LightingEffectAnimation()
	{
		m_performAnimate = nullptr;
	}
	static LightingEffectAnimation* m_instance;
};
class WaterEffectAnimation : private EffectAnimation
{
public:
	void loadAnimation(SpriteFrameCache* spriteFrameCache);
	Animate* getEffectPerformAnimate() {return m_performAnimate;}
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
	WaterEffectAnimation()
	{
		m_performAnimate = nullptr;
	}
	static WaterEffectAnimation* m_instance;
};



static class AnimationManager    // class quan li cac Animation
{
public:
	static void loadAnimationByTag(MonsterType arrMonsterType[],SpriteFrameCache* spriteFrameCache); // 1 man co cac loai quai khac nhau... Nhap vao cac loai quai va chi load animation cua cac quai do
	static Animate* getWalkAnimationByTag(MonsterType type);
	static Animate* getDieAnimationByTag(MonsterType type);
	static Animate* getStunAnimationByTag(MonsterType type);
	static Animate* getEffectAnimationByTag(BulletType type);
};

#endif