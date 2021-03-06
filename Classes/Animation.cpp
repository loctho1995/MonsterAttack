#include "Animation.h"
#include "Define.h"

USING_NS_CC;
//
PlayerAction* PlayerAction::m_instance = 0;
Monster1Action* Monster1Action::m_instance = 0;
Monster2Action* Monster2Action::m_instance = 0;
Monster3Action* Monster3Action::m_instance = 0;
Monster4Action* Monster4Action::m_instance = 0;

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
	for (int i = 1; i <= MONSTER2_WALK_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
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
	
}

Monster3Action::Monster3Action()
{
	m_walkAnimate = nullptr;
	m_dieAnimate  = nullptr;
	m_stunAnimate = nullptr;
	m_doneAnimate = nullptr;
}

void Monster3Action :: loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	spriteFrameCache->addSpriteFramesWithFile("Monster3.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;

	if (m_walkAnimate != nullptr &&
		m_dieAnimate  != nullptr &&
		m_stunAnimate != nullptr &&
		m_doneAnimate != nullptr
		)
		return;

#pragma region - MONSTER3 WALK -

	for (int i = 1; i <= MONSTER3_WALK_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"Monster3WalkAnimation_%d.png", i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);	
			if(frame != nullptr)
				aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			break;
		}
	}

	m_walkAnimate = Animate::create(Monster3Action::createWithSpriteFrames(aniFrame, MONSTER1_WALK_ANIMATION_TIME));
	m_walkAnimate->retain();
#pragma endregion
}

Monster4Action::Monster4Action()
{
	m_walkAnimate = nullptr;
	m_dieAnimate  = nullptr;
	m_stunAnimate = nullptr;
	m_doneAnimate = nullptr;
}

void Monster4Action :: loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	spriteFrameCache->addSpriteFramesWithFile("Monster4.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;

	if (m_walkAnimate != nullptr &&
		m_dieAnimate  != nullptr &&
		m_stunAnimate != nullptr &&
		m_doneAnimate != nullptr
		)
		return;

#pragma region - MONSTER4 WALK -

	for (int i = 1; i <= MONSTER4_WALK_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"Monster4WalkAnimation_%d.png", i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);	
			if(frame != nullptr)
				aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			break;
		}
	}

	m_walkAnimate = Animate::create(Monster4Action::createWithSpriteFrames(aniFrame, MONSTER1_WALK_ANIMATION_TIME));
	m_walkAnimate->retain();
#pragma endregion

#pragma region - MONSTER4 DIE - 
	aniFrame.clear(); //dm d clear lam 2 action gop lam 1
	//2 cai duoi chua co sprite
	for (int i = 1; i <= MONSTER4_DIE_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"Monster4DieAnimation_%d.png", i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			break;
		}
	}

	m_dieAnimate = Animate::create(Monster1Action::createWithSpriteFrames(aniFrame, MONSTER4_DIE_ANIMATION_TIME));
	m_dieAnimate->retain();
#pragma endregion
}

Monster5Action::Monster5Action()
{
	m_walkAnimate = nullptr;
	m_dieAnimate  = nullptr;
	m_stunAnimate = nullptr;
	m_doneAnimate = nullptr;
}

void Monster5Action :: loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	spriteFrameCache->addSpriteFramesWithFile("Monster5.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;

	if (m_walkAnimate != nullptr &&
		m_dieAnimate  != nullptr &&
		m_stunAnimate != nullptr &&
		m_doneAnimate != nullptr
		)
		return;

#pragma region - MONSTER5 WALK -
	for (int i = 1; i <= MONSTER5_WALK_ANIMATION_FRAMES; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"Monster5WalkAnimation_%d.png", i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);	
			if(frame != nullptr)
				aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			break;
		}
	}

	m_walkAnimate = Animate::create(Monster5Action::createWithSpriteFrames(aniFrame, MONSTER1_WALK_ANIMATION_TIME));
	m_walkAnimate->retain();
#pragma endregion
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
