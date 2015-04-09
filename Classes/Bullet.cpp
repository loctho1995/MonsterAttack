#include "Bullet.h"

void Bullet::move(Touch* touch, Sprite* sprite, Layer* layer)
{
	Point location = touch->getLocationInView();
	
	location = Director::getInstance()->convertToGL(location);
	
	Size winSize = Director::getInstance()->getVisibleSize();

	Point position = BulletManager::findPosition(sprite, touch);

	this->setPosition(position.x, position.y);
	
	int offX = location.x - this->getPosition().x;
	int offY = location.y - this->getPosition().y;
	
	if(offX <= 0)
		return;
		
	layer->addChild(this);
	
	int realX = winSize.width + (this->getContentSize().width / 2);
	
	float ratio = (float)offY / (float)offX;
	
	int realY = ((realX - this->getPosition().x) * ratio) + this->getPosition().y;
	
	auto realDest = Point(realX, realY);
	
	int offRealX = realX - this->getPosition().x;
	int offRealY = realY - this->getPosition().y;
	float length = sqrtf((offRealX * offRealX) + (offRealY * offRealY));
	
	float velocity = 480/1;
	
	float realMoveDuration = length / velocity;
	
	CallFuncN *func = CallFuncN::create([&, this](Node* sender){ sender->removeFromParentAndCleanup(true);});

	this->runAction(Sequence::create(MoveTo::create(realMoveDuration, realDest), func, NULL));
}

Point BulletManager::findPosition(Sprite* sprite, Touch* touch)
{
	Point position;

	Point touches = touch->getLocationInView();

	touches = Director::getInstance()->convertToGL(touches);

	int spriteX = sprite->getPosition().x;

	int spriteY = sprite->getPosition().y;

	float X1 = spriteX - 200*(spriteX - touches.x) / sqrt((spriteY - touches.y)*(spriteY - touches.y) + (spriteX - touches.x)*(spriteX - touches.x));

	float X2 = spriteX + 200*(spriteX - touches.x) / sqrt((spriteY - touches.y)*(spriteY - touches.y) + (spriteX - touches.x)*(spriteX - touches.x));

	float Y;

	if(X1 >= spriteX)
	{
		Y = (spriteY - touches.y) * (X1 - spriteX) / (spriteX - touches.x) + spriteY;
		position.setPoint(X1, Y);
	}
	else
	{
		Y = (spriteY - touches.y) * (X2 - spriteX) / (spriteX - touches.x) + spriteY;
		position.setPoint(X2, Y);
	}

	return position;
}

