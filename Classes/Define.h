#ifndef _DEFINE_H_
#define _DEFINE_H_
const int BULLET_VELOCITY =  480; // Toc do cua dan PIXLE / S
const int BULLET_RADIUS = 10; // ban kinh cua vien dan dung de set physic body
const float BULLET_ICE_TIME = 1; // 1s dong bang
const float LIGHTINGCIRCLE_TIME = 2;// thoi gian ton tai vong set

const float PLAYER_ATTACK_ANIMATION_TIME = 0.05f; // thoi gian chuyen frame cua animation Player Attack
const int PLAYER_ATTACK_ANIMATION_FRAMES = 6; // so frame cua Player Attack animation
const int PLAYER_DISTANCE = 50;

const float MONSTER1_WALK_ANIMATION_TIME = 0.1f;
const float MONSTER1_DIE_ANIMATION_TIME = 0.2f;
const float MONSTER1_DONE_ANIMATION_TIME = 0.15f;
const int MONSTER1_WALK_ANIMATION_FRAMES = 3; // so frame cua Monster1 Walk 
const int MONSTER1_DIE_ANIMATION_FRAMES = 3;
const int MONSTER1_STUN_ANIMATION_FRAMES = 4;
const int MONSTER1_DONE_ANIMATION_FRAMES = 8;

const int MONSTER2_WALK_ANIMATION_FRAMES = 3; // so frame cua Monster2 Walk

const int MONSTER3_WALK_ANIMATION_FRAMES = 4;

const int MONSTER4_WALK_ANIMATION_FRAMES = 9;
const int MONSTER4_DIE_ANIMATION_FRAMES = 5;

const int MONSTER5_WALK_ANIMATION_FRAMES = 3;

const int PLAYER_TAG = 0; // tag cua player
const int MONSTER_TAG = 1; // tag cua monster
const int CIRCLE_TAG = 2;
const int BULLET_TAG = 3;
const int LIGHTINGCIRCLE_TAG = 4;
//cac monster khong cham vao nhau
//bullet va circle khong cham vao nhau
//dung thuat toan & tren bit
// 0 & 0 = 0; 0 & 1 = 0; 1 & 1 = 1 ; 1 & 0 = 0
// 0001 & 0010 = 0 ; 0x003 = 0011
////const int MONSTER_COLLISION_BITMASK = 0x01;	// 0001
////const int BULLET_CONLLISION_BITMASK = 0x02; // 0010
////const int CIRCLE_CONLLISION_BITMASK = 0x04; // 0100
////
////const int MONSTER_CONTACT_CATEGORY = 0x06;	// 0110
////const int BULLET_CONTACT_CATEGORY = 0x01;	// 0001
////const int CIRCLE_CONTACT_CATEGORY = 0x01;	// 0001
////
////const int MONSTER_CONTACT_TEST_BITMASK = 0x01;
////const int BULLET_CONTACT_TEST_BITMASK = 0x04;
////const int CIRCLE_CONTACT_TEST_BITMASK = 0x04;

const int MONSTER_COLLISION_BITMASK = 0x01;
const int BULLET_CONLLISION_BITMASK = 0x02;
const int CIRCLE_CONLLISION_BITMASK = 0x02;

const int MONSTER_CONTACT_CATEGORY = 0x02;
const int BULLET_CONTACT_CATEGORY = 0x01;
const int CIRCLE_CONTACT_CATEGORY = 0x01;

const int MONSTER_CONTACT_TEST_BITMASK = 0x01;
const int BULLET_CONTACT_TEST_BITMASK = 0x02;
const int CIRCLE_CONTACT_TEST_BITMASK = 0x02;

//so sanh category - collision, category - test bitmask

const float WAVE_TIME = 20.0f; //thoi gian cho 1 wave
const float NEXTWAVE_DELAY_TIME = 0.5f; // thoi gian cho delay khi wave tiep theo toi

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
		WATER,
		ICE
	};
#endif