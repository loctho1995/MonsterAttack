#include "Animation.h"
#include "Define.h"

USING_NS_CC;
//
PlayerAction* PlayerAction::m_instance = 0;
Monster1Action* Monster1Action::m_instance = 0;
Monster2Action* Monster2Action::m_instance = 0;

SpriteAction::~SpriteAction(void)
{

}

#pragma region - PlayerAction -
PlayerAction::PlayerAction()
{
	m_attackAnimate = nullptr;
}

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
Monster1Action::Monster1Action()
{
	m_walkAnimate = nullptr;
	m_dieAnimate = nullptr;
	m_stunAnimate = nullptr;
	m_doneAnimate = nullptr;
}

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

#pragma region - MONSTER1 WALK -
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
			break;
		}
	}

	m_walkAnimate = Animate::create(Animation::createWithSpriteFrames(aniFrame, MONSTER1_WALK_ANIMATION_TIME));
	m_walkAnimate->retain();
#pragma endregion

#pragma region - MONSTER1 DIE - 
	aniFrame.clear(); //dm d clear lam 2 action gop lam 1
	//2 cai duoi chua co sprite
	for (int i = 1; i <= MONSTER1_DIE_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"Monster1DieAnimation_%d.png",i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			break;
		}
	}
	m_dieAnimate = Animate::create(Monster1Action::createWithSpriteFrames(aniFrame, MONSTER1_DIE_ANIMATION_TIME));
	m_dieAnimate->retain();
#pragma endregion

#pragma region - MONSTER1 STUN -
	for (int i = 1; i < MONSTER1_STUN_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"Monster1StunAnimation_%d.png",i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			break;
		}
	}
	m_stunAnimate = Animate::create(Monster1Action::createWithSpriteFrames(aniFrame, 0,1));
	m_stunAnimate->retain();
	#pragma endregion

#pragma region -MONSTER1 DONE- 
	// DONE Animate
	aniFrame.clear();
	 for(int i = 1; i <= MONSTER1_DONE_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	 {
		 try
		 {
			 sprintf(str,"Monster1DoneAnimation_%d.png",i);
			 auto frame = spriteFrameCache->getSpriteFrameByName(str);
			 frame->setOffset(Vec2::ZERO);
			 aniFrame.pushBack(frame);
		 }
		 catch (String exc)
		 {
			 return;
		 }
	 }
	 m_doneAnimate = Animate::create(Monster1Action::createWithSpriteFrames(aniFrame, MONSTER1_DONE_ANIMATION_TIME));
	 m_doneAnimate->retain();
#pragma endregion
}

Monster2Action::Monster2Action()
{
	m_walkAnimate = nullptr;
	m_dieAnimate  = nullptr;
	m_stunAnimate = nullptr;
	m_doneAnimate = nullptr;
}

void Monster2Action :: loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	spriteFrameCache->addSpriteFramesWithFile("Monster2.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;

	if (m_walkAnimate != nullptr &&
		m_dieAnimate  != nullptr &&
		m_stunAnimate != nullptr &&
		m_doneAnimate != nullptr
		)

		return;

#pragma region - MONSTER2 WALK -
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
			break;
		}
	}
	m_walkAnimate = Animate::create(Monster2Action::createWithSpriteFrames(aniFrame, MONSTER1_WALK_ANIMATION_TIME));
	m_walkAnimate->retain();
#pragma endregion
	
	return;
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
			break;
		}
	}
	m_dieAnimate = Animate::create(Monster2Action::createWithSpriteFrames(aniFrame, 0,1 ));
	m_stunAnimate->retain();

	for (int i = 1; i < MONSTER2_WALK_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"Monster2StunAnimation_%d.png",i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			break;
		}
	}
	m_stunAnimate = Animate::create(Monster2Action::createWithSpriteFrames(aniFrame, 0,1));
	m_stunAnimate->retain();
	
}

void AnimationManager::loadAnimationByTag(MonsterType arrMonsterType[], SpriteFrameCache* spriteFrameCache)
{
	//for each ko dung duoc - bao loi
	/*for each (MonsterType c in arrMonsterType)
	{
		switch (c)	
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
	}*/
}

Animate* AnimationManager::getWalkAnimationByTag (MonsterType type)
{
	switch (type)
	{
	case MONSTER1:
		return Monster1Action::getInstance()->getMonsterWalkAnimate();
		break;
	case MONSTER2:
		return Monster2Action::getInstance()->getMonsterWalkAnimate();
		break;
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
