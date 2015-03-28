#include "Animation.h"
#include "Define.h"

USING_NS_CC;
//
PlayerAction* PlayerAction::m_instance = 0;
Monster1Action* Monster1Action::m_instance = 0;
Monster2Action* Monster2Action::m_instance = 0;
FireEffectAnimation* FireEffectAnimation ::m_instance = 0;
LightingEffectAnimation* FireEffectAnimation ::m_instance = 0;
WaterEffectAnimation* FireEffectAnimation ::m_instance = 0;
NormalEffectAnimation* FireEffectAnimation ::m_instance = 0;
SpriteAction::~SpriteAction(void)
{

}

#pragma region - PlayerAction -

void PlayerAction::loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	if (m_attackAnimate !=nullptr)
		return;
	spriteFrameCache->addSpriteFramesWithFile("PlayerAttack.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;

	for (int i = 1; i <= PLAYER_ATTACK_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"PlayerAttack_%d.png", i);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			return;
		}
	}

	m_attackAnimate = Animate::create(Animation::createWithSpriteFrames(aniFrame, PLAYER_ATTACK_ANIMATION_TIME));
	m_attackAnimate->retain();
}
#pragma endregion

#pragma region - Monster1 Action -

void Monster1Action :: loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	if (m_walkAnimate != nullptr &&
		m_dieAnimate  != nullptr &&
		m_stunAnimate != nullptr &&
		m_doneAnimate != nullptr
		)
		return;
	spriteFrameCache->addSpriteFramesWithFile("Monster1.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;

	for (int i = 1; i <= MONSTER1_WALK_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"Monster1WalkAnimation_%d.png",i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			return;
		}
	}

	m_walkAnimate = Animate::create(Animation::createWithSpriteFrames(aniFrame, MONSTER1_WALK_ANIMATION_TIME));
	m_walkAnimate->retain();
	
	
	
	// DONE Animate
	// for (int i = 1; i <= MONSTER1_DONE_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	// {
		// try
		// {
			// sprintf(str,"Monster1DoneAnimation_%d.png",i);
			// auto frame = spriteFrameCache->getSpriteFrameByName(str);
			// aniFrame.pushBack(frame);
		// }
		// catch (String exc)
		// {
			// return;
		// }
	// }
	// m_doneAnimate = Animate::create(Monster1Action::createWithSpriteFrames(aniFrame, MONSTER1_DONE_ANIMATION_TIME));
	// m_doneAnimate->retain();
	
	
	
	
	
	
	
	/*
	//2 cai duoi chua co sprite
	for (int i = 1; i < 10; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"Monster1DieAnimation_%d.png",i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			return;
		}
	}
	m_dieAnimate = Animate::create(Monster1Action::createWithSpriteFrames(aniFrame, 0,1 ));
	m_dieAnimate->retain();

	for (int i = 1; i < 10; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"Monster1StunAnimation_%d.png",i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			return;
		}
	}
	m_stunAnimate = Animate::create(Monster1Action::createWithSpriteFrames(aniFrame, 0,1));
	m_stunAnimate->retain();
	*/
}
#pragma endregion

Monster2Action::Monster2Action()
{
	Monster2Action::loadAnimation(SpriteFrameCache::getInstance());
}

void Monster2Action :: loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	if (m_walkAnimate != nullptr &&
		m_dieAnimate  != nullptr &&
		m_stunAnimate != nullptr &&
		m_doneAnimate != nullptr )
		return;
	spriteFrameCache->addSpriteFramesWithFile("Monster2.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;
	for (int i = 1; i < MONSTER2_WALK_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"Monster2WalkAnimation_%d.png",i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			return;
		}
	}
	m_walkAnimate = Animate::create(Monster2Action::createWithSpriteFrames(aniFrame, MONSTER2_WALK_ANIMATION_TIME ));
	m_walkAnimate->retain();
	
	
	
	// DONE Animate
	// for (int i = 1; i <= MONSTER2_DONE_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	// {
		// try
		// {
			// sprintf(str,"Monster2DoneAnimation_%d.png",i);
			// auto frame = spriteFrameCache->getSpriteFrameByName(str);
			// aniFrame.pushBack(frame);
		// }
		// catch (String exc)
		// {
			// return;
		// }
	// }
	// m_doneAnimate = Animate::create(Monster1Action::createWithSpriteFrames(aniFrame, MONSTER2_DONE_ANIMATION_TIME));
	// m_doneAnimate->retain();
	
	
	/*
	for (int i = 1; i < 10; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"Monster2DieAnimation_%d.png",i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			return;
		}
	}
	m_dieAnimate = Animate::create(Monster2Action::createWithSpriteFrames(aniFrame, MONSTER2_DIE_ANIMATION_TIME ));
	m_dieAnimate->retain();

	for (int i = 1; i < MONSTER2_DIE_ANIMATION_TIME; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"Monster2StunAnimation_%d.png",i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			return;
		}
	}
	m_stunAnimate = Animate::create(Monster2Action::createWithSpriteFrames(aniFrame, MONSTER2_STUN_ANIMATION_TIME));
	m_stunAnimate->retain(); */
	
}

void FireEffectAnimation :: loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	if( m_performAnimate != nullptr)
		return;
	spriteFrameCache->addSpriteFramesWithFile("FireEffect.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;

	for (int i = 1; i <= FIRE_EFFECT_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"FireEffect_%d.png", i);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			return;
		}
	}

	m_performAnimate = Animate::create(Animation::createWithSpriteFrames(aniFrame, FIRE_EFFECT_ANIMATION_TIME));
	m_performAnimate->retain();
}

void NormalEffectAnimation :: loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	if( m_performAnimate != nullptr)
		return;
	spriteFrameCache->addSpriteFramesWithFile("NormalEffect.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;

	for (int i = 1; i <= NORMAL_EFFECT_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"NormalEffect_%d.png", i);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			return;
		}
	}

	m_performAnimate = Animate::create(Animation::createWithSpriteFrames(aniFrame, NORMAL_EFFECT_ANIMATION_TIME));
	m_performAnimate->retain();
}
void LightingEffectAnimation :: loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	if( m_performAnimate != nullptr)
		return;
	spriteFrameCache->addSpriteFramesWithFile("NormalEffect.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;

	for (int i = 1; i <= NORMAL_EFFECT_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"LightingEffect_%d.png", i);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			return;
		}
	}

	m_performAnimate = Animate::create(Animation::createWithSpriteFrames(aniFrame, LIGHTING_EFFECT_ANIMATION_TIME));
	m_performAnimate->retain();
}
void WaterEffectAnimation :: loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	if( m_performAnimate != nullptr)
		return;
	spriteFrameCache->addSpriteFramesWithFile("NormalEffect.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;

	for (int i = 1; i <= WATER_EFFECT_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"WaterEffect_%d.png", i);
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			return;
		}
	}

	m_performAnimate = Animate::create(Animation::createWithSpriteFrames(aniFrame, WATER_EFFECT_ANIMATION_TIME));
	m_performAnimate->retain();
}


void AnimationManager::loadAnimationByTag(MonsterType arrMonsterType[], SpriteFrameCache* spriteFrameCache)
{
	//for each ko dung duoc - bao loi
	PlayerAction::getInstance()->loadAnimation(spriteFrameCache);
	FireEffectAnimation::getInstance()->loadAnimation(spriteFrameCache);
	LightingEffectAnimation::getInstance()->loadAnimation(spriteFrameCache);
	NormalEffectAnimation::getInstance()->loadAnimation(spriteFrameCache);
	WaterEffectAnimation::getInstance()->loadAnimation(spriteFrameCache);
	for (int i = 0; i < 10 , i++)
	{
		MonsterType type = arrMonsterType[i];
		switch (type)
		{
		case MONSTER1:
			Monster1Action::getInstance()->loadAnimation(spriteFrameCache);
			break;
		case MONSTER2:
			Monster2Action::getInstance()->loadAnimation(spriteFrameCache);
			break;
		default:
			break;
		}
	}
	*/
}

Animate* AnimationManager::getWalkAnimationByTag (MonsterType type)
{
	switch (type)
	{
	case MONSTER1:
		return Monster1Action::getInstance()->getMonsterWalkAnimate();
	case MONSTER2:
		return Monster2Action::getInstance()->getMonsterWalkAnimate();
	default:
		break;
	}
}

Animate* AnimationManager::getDieAnimationByTag (MonsterType type)
{
	switch (type)
	{
	case MONSTER1:
		//return Monster1Action::getInstance()->getMonsterDieAnimation();
		break;
	case MONSTER2:
		//return Monster2Action::getInstance()->getMonsterDieAnimation();
		break;
	default:
		break;
	}

	return nullptr;
}
Animate* AnimationManager::getStunAnimationByTag (MonsterType type)
{
	switch (type)
	{
	case MONSTER1:
		//return Monster1Action::getInstance()->getMonsterDieAnimation();
	case MONSTER2:
		//return Monster2Action::getInstance()->getMonsterDieAnimation();
	default:
		break;
	}

	return nullptr;
}
Animate* AnimationManager::getEffectAnimationByTag(BulletType type)
{
	switch (type)
	{
	case FIRE:
		return FireEffectAnimation::getInstance()->getEffectPerformAnimate();
	case NORMAL:
		return NormalEffectAnimation::getInstance()->getEffectPerformAnimate();
	case LIGHTING:
		return LightingEffectAnimation::getInstance()->getEffectPerformAnimate();
	case WATER:
		return WaterEffectAnimation::getInstance()->getEffectPerformAnimate();
	default:
		break;
	}
}
