#ifndef ___STATE__
#define ___STATE__
#include "cocos2d.h"
#include "Monster.h"

USING_NS_CC;

class State
{
public:
	State();
	virtual void nextWave();
	virtual bool isEndWave();
	virtual void addTarget(Node* parent, float dt);
	virtual void pause(float time);
	virtual bool isRunning();

protected:
	Monster* createMonster(int level, float delay);
	int m_numberOfWave;	
	float m_timePause;
	bool m_isPause;
};

class State1 : public State
{
public:
	State1();
	virtual void addTarget(Node* parent, float dt);
};

class State2 : public State
{
public:
	State2();
	virtual void addTarget(Node* parent, float dt);
};

class State3 : public State
{
public:
	State3();
	virtual void addTarget(Node* parent, float dt);
};
#endif