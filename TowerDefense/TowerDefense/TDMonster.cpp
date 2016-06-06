#include "TDMonster.h"

TDMonster::TDMonster(float fPosX, float fPosY, float fPosZ) {
	TDObject::init(MONSTER_COLOR_RED, MONSTER_COLOR_GREEN, MONSTER_COLOR_BLUE,
		fPosX, fPosY + 1.0f, fPosZ, MONSTER_NUM_CUBE);
}