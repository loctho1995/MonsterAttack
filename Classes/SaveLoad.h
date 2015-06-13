#ifndef __SAVE_LOAD__GAME__
#define __SAVE_LOAD__GAME__

class SaveLoad
{
public:
	static void saveGame();
	static void loadGame();
	static int getMaxState(); //default = 0
	static void setMaxState(int i);

private:
	static int m_maxState;
};
#endif