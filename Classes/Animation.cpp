#include "Animation.h"
USING_NS_CC;
//
PlayerAction* PlayerAction::m_instance = 0;
Monster1Action* Monster1Action::m_instance = 0;
Monster2Action* Monster2Action::m_instance = 0;
void PlayerAction::loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	spriteFrameCache->addSpriteFramesWithFile("Player.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;
	for (int i = 1; i < 10; i++) // Vong lap tao sprite attack
	{
		try
		{
			sprintf(str,"PlayerAttack_%d.png",i);
			auto frame = spriteFrameCache->getSpriteFrameByName(str);
			aniFrame.pushBack(frame);
		}
		catch (String exc)
		{
			break;
		}
	}
	m_attackAnimation = PlayerAction::createWithSpriteFrames(aniFrame, 0,1 );
}
void Monster1Action :: loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	spriteFrameCache->addSpriteFramesWithFile("Monster1.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;
	for (int i = 1; i < 10; i++) // Vong lap tao sprite attack
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

	m_walkAnimation = Monster1Action::createWithSpriteFrames(aniFrame, 0,1 );

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
			break;
		}
	}

	m_dieAnimation = Monster1Action::createWithSpriteFrames(aniFrame, 0,1 );


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
			break;
		}
	}
	m_stunAnimation = Monster1Action::createWithSpriteFrames(aniFrame, 0,1);
	
}




void Monster2Action :: loadAnimation(SpriteFrameCache* spriteFrameCache)
{
	spriteFrameCache->addSpriteFramesWithFile("Monster2.plist");
	char str[50] = {0}; // Bien tam luu ten cua cac sprite
	Vector<SpriteFrame*> aniFrame;
	for (int i = 1; i < 10; i++) // Vong lap tao sprite attack
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

	m_walkAnimation = Monster2Action::createWithSpriteFrames(aniFrame, 0,1 );

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

	m_dieAnimation = Monster2Action::createWithSpriteFrames(aniFrame, 0,1 );


	for (int i = 1; i < 10; i++) // Vong lap tao sprite attack
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
	m_stunAnimation = Monster2Action::createWithSpriteFrames(aniFrame, 0,1);
	
}

void AnimationManager::loadAnimationByTag(MonsterType arrMonsterType[10], SpriteFrameCache* spriteFrameCache)
{
	for each (MonsterType c in arrMonsterType)
	{
		switch (c)	
		{
		case MONSTER_1:
			Monster1Action::getInstance()->loadAnimation(spriteFrameCache);
			break;
		case MONSTER_2:
			Monster2Action::getInstance()->loadAnimation(spriteFrameCache);
			break;
		default:
			break;
		}
	}
}
Animation* AnimationManager::getWalkAnimationByTag (MonsterType type)
{
	switch (type)
	{
	case MONSTER_1:
		return Monster1Action::getInstance()->getMonsterWalkAnimation();
		break;
	case MONSTER_2:
		return Monster2Action::getInstance()->getMonsterWalkAnimation();
		break;
	default:
		break;
	}
}

Animation* AnimationManager::getDieAnimationByTag (MonsterType type)
{
	switch (type)
	{
	case MONSTER_1:
		return Monster1Action::getInstance()->getMonsterDieAnimation();
		break;
	case MONSTER_2:
		return Monster2Action::getInstance()->getMonsterDieAnimation();
		break;
	default:
		break;
	}
}
Animation* AnimationManager::getDieAnimationByTag (MonsterType type)
{
	switch (type)
	{
	case MONSTER_1:
		return Monster1Action::getInstance()->getMonsterStunAnimation();
		break;
	case MONSTER_2:
		return Monster2Action::getInstance()->getMonsterStunAnimation();
		break;
	default:
		break;
	}
}