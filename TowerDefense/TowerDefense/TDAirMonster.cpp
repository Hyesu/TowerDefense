#include "TDAirMonster.h"

TDAirMonster::TDAirMonster(float fPosMapEndX, float fPosMapEndY, float fPosMapEndZ)
	: TDMonster(fPosMapEndX, fPosMapEndY, fPosMapEndZ) {
	_vPosition1.y += MONSTER_AIR_OFFSET;
	_vPosition2.y += MONSTER_AIR_OFFSET;
}