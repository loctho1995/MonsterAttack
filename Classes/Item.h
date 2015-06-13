#ifndef _ITEM_H_
#define _ITEM_H_

#include "cocos2d.h"
#include "Define.h"
#include "Animation.h"
USING_NS_CC;

class ItemManager;
class Item;

class Item : public Sprite
{
public:
	Item ()
	{}
	bool checkTouch(Point touchPoint)  // function check if touch in ITEM or not
	{
		float radius = this -> getContentSize().width/ 2;
		Point centerPoint = this -> getPosition();
		if( pow((touchPoint.x - centerPoint.x ), 2) + pow ((touchPoint.y - centerPoint.y ), 2 ) < pow( radius, 2))
		{
			return true;
		}
		else return false;
	}

	BulletType getType() const
	{
		return type;
	}
	virtual void animate();
	virtual void done();
protected:
	BulletType type;
	
};
class FireItem : public Item
{
public:
	FireItem()
	{
		type = BulletType::FIRE;
		this->initWithFile("FireItem_1.png");
	}

private:
	;
};
class WaterItem : public Item
{
public:
	WaterItem()
	{
		type = BulletType::WATER;
		this->initWithFile("WaterItem_1.png");
	}
private:
};
class LightingItem : public Item
{
public:
	LightingItem()
	{
		type = BulletType::LIGHTING ;
		this->initWithFile("LightingItem_1.png");
	}
private:

};
class IceItem : public Item 
{
public:
	IceItem() : Item()
	{
		type = BulletType::ICE; 
		this->initWithFile("IceItem_1.png");
		setTag(5);
	}
};


class ItemManager
{
public:
	Sprite* getItemByTag(BulletType type);

	std::vector<Item*> getItems()
	{
		return m_items;
	}

	void addItem(Item* item)
	{
		m_items.push_back(item);
	}

	void eraseItem(int pos)
	{
		m_items.at(pos)->removeFromParentAndCleanup(true);

		if(m_items.at(pos) != nullptr)
			m_items.at(pos) = nullptr;

		m_items.erase(m_items.begin() + pos);
	}

	static ItemManager* getInstacce() 
	{
		if(m_Instance == 0)
		{
			m_Instance = new ItemManager();
			return m_Instance;
		}
		else
		{
			return m_Instance;
		}
	}

private:
	std::vector<Item*> m_items;
	static ItemManager* m_Instance;
	ItemManager() {}
};
#endif