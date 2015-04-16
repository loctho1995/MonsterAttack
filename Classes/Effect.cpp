#include "Effect.h"


Sprite* EffectManager::getEffectByTag(BulletType type)
{
	switch (type)
	{
	case NORMAL:
		return NormalEffect::createWithSpriteFrameName("NormalEffect_1.png");
	case FIRE :
		return FireEffect::createWithSpriteFrameName("FireEffect_1.png");
	case LIGHTING:
		return LightingEffect::createWithSpriteFrameName("LightingEffect_1.png");
	case WATER:
		return WaterEffect::createWithSpriteFrameName("WaterEffect_1.png");
	case ICE:
		return IceEffect::createWithSpriteFrameName("IceEffect_1.png");
	default:
		return nullptr;
	}
}