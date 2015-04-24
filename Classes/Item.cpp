#include "Item.h"
USING_NS_CC;

ItemManager* ItemManager::m_Instance = 0;

void Item::animate()
{
	Action* action = RepeatForever::create(JumpTo::create(2, this->getPosition(), this->getContentSize().height * 1.5 , 1 ) );
	
	auto fadeIn = FadeIn::create(0.3f);
	auto fadeOut = FadeOut::create(0.3f);
	Sequence* sefade = Sequence::create(DelayTime::create(0.0f),fadeIn, fadeOut, nullptr);
	auto fade = Repeat::create(sefade, 6 );

	this->runAction(action);
	Sequence* newAction = Sequence::create(DelayTime::create(4.5f), fade,  
										CallFunc::create(CC_CALLBACK_0(Item::done, this)),
										nullptr);
	this->runAction(newAction);
}
void Item::done()
{
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);
}
Sprite* ItemManager::getItemByTag(BulletType type)
{
	switch (type)
	{
	case NORMAL:
		break;

	case FIRE :
		{
			auto newitem = new FireItem();
			return newitem;
		}	

	case LIGHTING:
		{
			auto newitem = new LightingItem();
			return newitem;
		}

	case WATER:
		{
			auto newitem = new WaterItem();
			return newitem;
			
		}

	case ICE:
		{
			auto newitem = new IceItem();
			return newitem;
			
		}
	}
}





