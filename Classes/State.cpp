#include "State.h"

#pragma region - STATE -
State::State()
{
	m_isPause = false;
}

void State::nextWave()
{
	m_numberOfWave--;
}

bool State::isEndWave()
{
	if(m_numberOfWave == 0)
		return true;

	return false;
}

void State::addTarget(Node* parent, float dt)
{
	
}

void State::pause(float time)
{
	m_timePause = time;
	m_isPause = true;
}

bool State::isRunning()
{
	if(m_isPause)
		return false;

	return true;
}

Monster* State::createMonster(int level, float delay)
{
	Monster *target = nullptr;
	auto m_winSize = Director::getInstance()->getVisibleSize();

	switch(level)
	{
		case 1:
			target = new Monster1();
			break;

		case 2:
			target = new Monster2();
			break;

		case 3:
			target = new Monster3();
			break;

		case 4:
			target = new Monster4();
			break;
	}	

	if(target == nullptr)
		return nullptr;

	// calculate target position
	int minY = target->getContentSize().height / 2;
	int maxY = m_winSize.height - target -> getContentSize().height / 2 - m_winSize.height/6;
	int rangeY = maxY - minY;
	int actualY = (rand()% rangeY) + minY;
		
	target->setPosition(Point(m_winSize.width + (target->getContentSize().width/2) + 10, actualY));
	target->setTimeDelay(delay);	

	return target;
}

#pragma endregion

#pragma region - STATE 1 -

State1::State1()
{
	// man 1 co 3 dot tan dong
	// chi co 3 loai quai

	m_numberOfWave = 3;
}

void State1::addTarget(Node* parent, float dt)
{
	if(m_isPause){
		m_timePause -= dt;

		if(m_timePause <= 0)
			m_isPause = false;

		return;
	}

	std::chrono::milliseconds duration(10);
	int x; 
	Monster* target = nullptr;

	switch(m_numberOfWave)
	{
		case 3:
			// cho khoang 10 con quai level 1 ra			
			target = createMonster(1, (float)(rand() % 30) / 100);
			target->walk();			
			parent->addChild(target);

			break;

		case 2:
			target = createMonster(1, (float)(rand() % 40) / 100);	
			target->walk();
			parent->addChild(target);

			std::this_thread::sleep_for(duration);

			target = createMonster(1, (float)(rand() % 50) / 100);
			target->walk();
			parent->addChild(target);

			break;

		case 1:
			target = createMonster(1, (float)(rand() % 60) / 100);
			target->walk();
			parent->addChild(target);

			std::this_thread::sleep_for(duration);
			x = rand() % 2 + 1;			

			target = createMonster(x, (float)(rand() % 30) / 100 + 0.1f);
			target->walk();
			parent->addChild(target);

			break;

		case 0:
			target = createMonster(2, (float)(rand() % 80) / 100);
			target->walk();
			parent->addChild(target);

			std::this_thread::sleep_for(duration);

			target = createMonster(2, (float)(rand() % 90) / 100 + 0.1f);
			target->walk();
			parent->addChild(target);

			break;
	}
}

#pragma endregion

#pragma region - STATE 2 -

State2::State2()
{
	// man 1 co 3 dot tan dong
	// chi co 3 loai quai

	m_numberOfWave = 4;
}

void State2::addTarget(Node* parent, float dt)
{	
	if(m_isPause){
		m_timePause -= dt;

		if(m_timePause <= 0)
			m_isPause = false;

		return;
	}

	std::chrono::milliseconds duration(10);
	int x; 
	Monster* target;

	switch(m_numberOfWave)
	{
		case 4:		
			target = createMonster(1, (float)(rand() % 30) / 100);
			target->walk();
			parent->addChild(target);
			break;

		case 3:
			target = createMonster(1, (float)(rand() % 40) / 100);
			target->walk();
			parent->addChild(target);

			std::this_thread::sleep_for(duration);

			target = createMonster(2, (float)(rand() % 50) / 100);
			target->walk();
			parent->addChild(target);

			break;

		case 2:
			target = createMonster(1, (float)(rand() % 60) / 100);
			target->walk();
			parent->addChild(target);

			std::this_thread::sleep_for(duration);
			x = rand() % 3 + 1;		

			target = createMonster(x, (float)(rand() % 30) / 100 + 0.1f);
			target->walk();
			parent->addChild(target);
			break;

		case 1:
			std::this_thread::sleep_for(duration);
			x = rand() % 2 + 2;			
			target = createMonster(x, (float)(rand() % 30) / 100 + 0.1f);
			target->walk();
			parent->addChild(target);
			break;

		case 0:
			target = createMonster(3, (float)(rand() % 30) / 100 + 0.1f);
			target->walk();
			parent->addChild(target);
			break;
	}
}

#pragma endregion

#pragma region - STATE 3 -

State3::State3()
{
	// man 1 co 3 dot tan dong
	// chi co 3 loai quai

	m_numberOfWave = 4;
}

void State3::addTarget(Node* parent, float dt)
{
	if(m_isPause){
		m_timePause -= dt;

		if(m_timePause <= 0)
			m_isPause = false;
		else
			return;
	}
	
	std::chrono::milliseconds duration(10);
	int x; 

	/*switch(m_numberOfWave)
	{
		case 4:
			createMonster(1, (float)(rand() % 40) / 100, Director::getInstance()->getRunningScene());	
			std::this_thread::sleep_for(duration);
			createMonster(2, (float)(rand() % 50) / 100, Director::getInstance()->getRunningScene());
			break;

		case 3:
			createMonster(2, (float)(rand() % 50) / 100, Director::getInstance()->getRunningScene());
			break;

		case 2:
			createMonster(2, (float)(rand() % 50) / 100, Director::getInstance()->getRunningScene());
			std::this_thread::sleep_for(duration);
			createMonster(3, (float)(rand() % 50) / 100, Director::getInstance()->getRunningScene());
			break;

		case 1:
			createMonster(3, (float)(rand() % 50) / 100, Director::getInstance()->getRunningScene());
			std::this_thread::sleep_for(duration);
			createMonster(4, (float)(rand() % 50) / 100, Director::getInstance()->getRunningScene());
			break;

		case 0:
			createMonster(4, (float)(rand() % 50) / 100, Director::getInstance()->getRunningScene());
			break;
	}*/
}

#pragma endregion