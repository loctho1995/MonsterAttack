#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

#if CC_TARGET_PLATFORM != CC_PLATFORM_WP8
class HelloWorld : public cocos2d::Layer

#else
class HelloWorld : public cocos2d::Layer, BackButtonPressed
#endif
{
public:
	
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	void gameLogic(float dt);
	void addTarget(float dt);
	void spriteMoveFinished(cocos2d::Node* sender);
	void targetMoveFinished(cocos2d::Node* sender);
	void onTouchEnded (cocos2d::Touch* touches, cocos2d::Event* event);
	void onTouchMoved (cocos2d::Touch* touches, cocos2d::Event* event);
	bool onTouchBegan (cocos2d::Touch* touches, cocos2d::Event* event);
	void onBackPressed();
	bool onContactBegin(const PhysicsContact& contact);
	void Pause(Ref *pSender);
	static void EnablePausebt();
	static void DisablePausebt();
	CREATE_FUNC(HelloWorld);
private:
	Point locateBullet (Point touchPoint);
	Sprite	*m_bullet,
			*m_circle;
	Size m_winSize;
	MenuItemImage *m_btPause;
	static Menu *m_mnPause;

};
#endif
// __HELLOWORLD_SCENE_H__

