#include "Item.h"
USING_NS_CC;

int ItemManager::ID = 0;
ItemManager* ItemManager::m_Instance = 0;
std::vector < Item*> ItemManager::m_Items;

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
	ItemManager::removeAt(m_ID);
}
Sprite* ItemManager::getItemByTag(BulletType type)
{
	switch (type)
	{
	case NORMAL:
		break;
	case FIRE :
		{
			auto newitem = new FireItem(ID);
			ID++;
			m_Items.push_back(newitem);
			return newitem;
		}	
	case LIGHTING:
		{
			auto newitem = new LightingItem(ID);
			ID++;
			m_Items.push_back(newitem);
			return newitem;
		}
	case WATER:
		{
			auto newitem = new WaterItem(ID);
			ID++;
			m_Items.push_back(newitem);
			return newitem;
			
		}
	case ICE:
		{
			auto newitem = new IceItem(ID);
			ID++;
			m_Items.push_back(newitem);
			return newitem;
			
		}
	}
}

void ItemManager::removeAt( int i )
{
	m_Items.erase(m_Items.begin() + i);
}

BulletType ItemManager:: checkTouch(Point touchPoint)
{
	for (int i = 0; i < m_Items.size(); i++)
	{
		Item* item = m_Items.at(i);
		if(item ->checkTouch( touchPoint))
		{
			item->stopAllActions();
			item ->removeFromParent();
			removeAt( i );
			return item -> getType();
			
		}
	}
	return BulletType::INVALID;
}


