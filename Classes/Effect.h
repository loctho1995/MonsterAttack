#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "cocos2d.h"
#include "Define.h"
#include "Animation.h"
USING_NS_CC;
class Effect : public Sprite
{
public:
	Effect() {};
	virtual void perform(BulletType type)
	{
		auto action = AnimationManager::getEffectAnimationByTag(type);
		this->runAction(action);
	}
	virtual void done()
	{
		this->removeFromParent();
	}
};
class FireEffect : public Effect
{
public:
	FireEffect() {}
};
class NormalEffect : public Effect
{
public:
	NormalEffect() {}
};
class WaterEffect : public Effect
{
public:
	WaterEffect() {}
};
class LightingEffect : public Effect
{
public:
	LightingEffect() {}
};


class EffectManager
{
public:
	Sprite* getEffectByTag(BulletType type);
};
#endif