#include "Bullet.h"

void Bullet::move(Vec2 touch, Sprite* sprite, Node* layer)
{
	auto body = PhysicsBody::createCircle(BULLET_RADIUS, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(15, 0));	
	body->setContactTestBitmask(BULLET_CONTACT_TEST_BITMASK);	
	body->setCollisionBitmask(BULLET_CONLLISION_BITMASK);
	body->setCategoryBitmask(BULLET_CONTACT_CATEGORY);	
	this->setPhysicsBody(body);
	this->setTag(BULLET_TAG);

	Point location = touch; //->getLocationInView();
	
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
	//auto realDest = Point(realX - 200, realY);
	
	int offRealX = realX - this->getPosition().x;
	int offRealY = realY - this->getPosition().y;
	float length = sqrtf((offRealX * offRealX) + (offRealY * offRealY));
	
	float velocity = 480/1;
	
	float realMoveDuration = length / velocity;
	
	CallFuncN *func = CallFuncN::create([&, this](Node* sender){ 
		((Bullet*)sender)->done();
	});

	this->runAction(Sequence::create(MoveTo::create(realMoveDuration, realDest), func, nullptr));
}

Point BulletManager::findPosition(Sprite* sprite, Vec2 touch)
{
	Point position;

	Point touches = touch;//->getLocationInView();

	touches = Director::getInstance()->convertToGL(touches);

	int spriteX = sprite->getPosition().x;

	int spriteY = sprite->getPosition().y;

	float X1 = spriteX - PLAYER_DISTANCE * (spriteX - touches.x) / sqrt((spriteY - touches.y)*(spriteY - touches.y) + (spriteX - touches.x)*(spriteX - touches.x));

	float X2 = spriteX + PLAYER_DISTANCE * (spriteX - touches.x) / sqrt((spriteY - touches.y)*(spriteY - touches.y) + (spriteX - touches.x)*(spriteX - touches.x));

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

//circle lighting
void Lighting::createLightingCircle(Node* monster)
{
	Sprite *LightingCircle = Sprite::create("thunderCircle.png");
	LightingCircle->setTag(LIGHTINGCIRCLE_TAG);
	monster->getParent()->addChild(LightingCircle);
	LightingCircle->setPosition(monster->getPosition().x, monster->getPosition().y);
	//LightingCircle->setVisible(false);

	//physics
	PhysicsBody *LightingCircleBody = PhysicsBody::createCircle(0.1 * this->getContentSize().width * 4 / 2, PhysicsMaterial(0, 0, 0), Vec2::ZERO);
	LightingCircleBody->setDynamic(false);
	LightingCircleBody->setContactTestBitmask(BULLET_CONTACT_TEST_BITMASK);
	//LightingCircleBody->setCategoryBitmask(BULLET_CONTACT_CATEGORY); // va cham
	LightingCircleBody->setCollisionBitmask(0x00); //chat lieu

	LightingCircle->setScale(0.1 * this->getContentSize().width * 4 / LightingCircle->getContentSize().width);
	LightingCircle->runAction(ScaleTo::create(0.5, this->getContentSize().width * 4 / LightingCircle->getContentSize().width));
	//thunderCircle->setScale(bullet->getContentSize().width * 4 / thunderCircle->getContentSize().width);
			
	LightingCircle->setPhysicsBody(LightingCircleBody);

	LightingCircle->runAction(RepeatForever::create(RotateBy::create(3, 360)));

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Bullet/Circle.wav");

	//LightingCircle->runAction(RepeatForever::create(TintBy::create(0.5, (rand()%256),(rand()%256), (rand()%256))));

	CallFuncN* func = CallFuncN::create([&, LightingCircle](Node* circle)
	{
		((Sprite*)circle)->removeFromParentAndCleanup(true); 
	});

	LightingCircle->runAction(Sequence::create(DelayTime::create(LIGHTINGCIRCLE_TIME), func, nullptr));
}

Bullet::~Bullet()
{
	if(prt != nullptr)
	{
		prt = nullptr;
	}
}