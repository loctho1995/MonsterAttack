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
	Item (int ID) : m_ID( ID)
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
	virtual void Animate();
protected:
	int m_ID;
	BulletType type;
	
};
class FireItem : public Item
{
public:
	FireItem(int ID) : Item(ID)
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
	WaterItem(int ID) : Item(ID)
	{
		type = BulletType::WATER;
		this->initWithFile("LightingItem_1.png");
	}
private:
};
class LightingItem : public Item
{
public:
	LightingItem(int ID ) : Item(ID)
	{
		type = BulletType::LIGHTING ;
		this->initWithFile("WaterItem_1.png");
	}
private:

};
class IceItem : public Item 
{
public:
	IceItem(int ID) : Item(ID)
	{
		type = BulletType::ICE; 
		this->initWithFile("IceItem_1.png");
	}
};


class ItemManager
{
public:
	static Sprite* getItemByTag(BulletType type);
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
	std::vector<Item*> getItems()
	{
		return m_Items;
	}
	static void removeAt( int i);
	BulletType checkTouch( Point touchPoint );// function check all member of item vector
private:
	static std::vector < Item*> m_Items;
private:
	static int ID;
	static ItemManager* m_Instance;
	ItemManager() {}
};
#endif