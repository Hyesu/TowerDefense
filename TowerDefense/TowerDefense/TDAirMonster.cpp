#include "TDAirMonster.h"

TDAirMonster::TDAirMonster(float fPosX, float fPosY, float fPosZ) {
	TDObject::init(MONSTER_COLOR_RED, MONSTER_COLOR_GREEN, MONSTER_COLOR_BLUE,
		fPosX, fPosY + MONSTER_POS_Y_AIR, fPosZ, MONSTER_NUM_CUBE);
}