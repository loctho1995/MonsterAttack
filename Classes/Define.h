#ifndef _DEFINE_H_
#define _DEFINE_H_
const int BULLET_VELOCITY =  480; // Toc do cua dan PIXLE / S

const float PLAYER_ATTACK_ANIMATION_TIME = 0.1f; // thoi gian chuyen frame cua animation Palyer Attack
const float MONSTER1_WALK_ANIMATION_TIME = 0.1f;

const int PLAYER_ATTACK_ANIMATION_FRAMES = 6; // so frame cua Player Attack animation
const int MONSTER1_WALK_ANIMATION_FRAMES = 3; // so frame cua Monster Walk 
const int MONSTER2_WALK_ANIMATION_FRAMES = 4;
const int PLAYER_TAG = 0; // tag cua player
const int MONSTER1_TAG = 1; // tag cua monster


enum MonsterType // Cac loai quai chua xac dinh co bao nhieu loai
	{
		MONSTER1,
		MONSTER2
	};

	enum BulletType
	{
		NORMAL,
		FIRE,
		LIGHTING,
		WATER
	};
#endif