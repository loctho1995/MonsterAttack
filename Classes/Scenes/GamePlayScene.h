#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "State.h"
#include "CallBackWP.h"

USING_NS_CC;

#if CC_TARGET_PLATFORM != CC_PLATFORM_WP8
class GamePlayScene : public cocos2d::Layer

#else
class GamePlayScene : public cocos2d::Layer
#endif
{
public:
	
	~GamePlayScene();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int state);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	void gameLogic(float dt);
	void onTouchEnded (cocos2d::Touch* touches, cocos2d::Event* event);
	void onTouchMoved (cocos2d::Touch* touches, cocos2d::Event* event);
	bool onTouchBegan (cocos2d::Touch* touches, cocos2d::Event* event);
	void onBackPressed();
	bool onContactBegin(const PhysicsContact& contact);
	void setState(int state);
	void Pause(Ref *pSender);
	static int getState();
	CREATE_FUNC(GamePlayScene);

private:
	static int m_State;
	bool m_isWinGame, m_isLoseGame, m_isPause, m_isShowWingame;
	Point locateBullet (Point touchPoint);
	Sprite	*m_nextWave,
			*m_finalWave,
			*m_winGame,
			*m_circle,
			*m_pausePanel,
			*m_losePanel,
			*m_winPanel;

	Size m_winSize;

	MenuItemImage	*m_btPause,
					*m_resume,
					*m_restart,
					*m_selectlvl,
					*m_backtomenu;

	static Menu *m_mnPause;
	Menu *m_menupause;
	State* m_state;
	float m_timeWave; // thoi gian 1 wave
	Sprite **m_HP; //ve mau cua nhan vat

	void initMenu();
	void showPause();
	void hideMenu();
	void showWinGame();
	void showLoseGame();
	void onMenuItemClicked(Ref *ref);
};
#endif
// __HELLOWORLD_SCENE_H__

