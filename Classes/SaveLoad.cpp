#include "SaveLoad.h"
#include "cocos2d.h"

USING_NS_CC;
const char* MAX_STATE = "maxstate";

int SaveLoad::m_maxState = 1;

void SaveLoad::saveGame()
{
	UserDefault::getInstance()->setIntegerForKey(MAX_STATE, m_maxState);
}

void SaveLoad::loadGame()
{
	m_maxState = UserDefault::getInstance()->getIntegerForKey(MAX_STATE, 1);
}

void SaveLoad::setMaxState(int i)
{
	m_maxState = i;
}

int SaveLoad::getMaxState()
{
	return m_maxState;
}