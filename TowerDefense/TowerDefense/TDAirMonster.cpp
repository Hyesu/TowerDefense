/**
	File: TDAirMonster.cpp
		Define functions of TDAirMonster class.

	Shin Hyesu, 2016.06
*/

#include "TDAirMonster.h"

/**
	Function: TDAirMonster
		Constructor of TDAirMonster class.
		Init position of air-type monster.

	Params:
		fPosMapEndX		float value for x-position of monster
		fPosMapEndY		float value for y-position of monster
		fPosMapEndZ		float value for z-position of monster
*/
TDAirMonster::TDAirMonster(float fPosMapEndX, float fPosMapEndY, float fPosMapEndZ)
	: TDMonster(fPosMapEndX, fPosMapEndY, fPosMapEndZ) {
	_vPosition1.y += MONSTER_AIR_OFFSET;
	_vPosition2.y += MONSTER_AIR_OFFSET;
}