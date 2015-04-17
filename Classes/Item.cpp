#include "Item.h"
USING_NS_CC;

ItemManager* ItemManager::m_Instance = 0;

void Item::Animate()
{
	Action* action = RepeatForever::create(JumpBy::create(0.5f, this->getPosition() , this->getPosition().y * 2 , 1 ) );
	Action* fadeIn = FadeIn::create(0.3f);
	Action* fadeOut = FadeOut::create(0.3f);
	Sequence* sefade = Sequence::create(DelayTime::create(0.0f),fadeIn, fadeOut, NULL);
	Action* fade = Repeat::create(sefade, 4 );
	this->runAction(action);
	Sequence* newACtion = Sequence::create(DelayTime::create(4.5f), fade, NULL);
	this->removeFromParent();
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





