/**
	File: TDAirMonster.h
		Define constants and class for representing air-type monster in tower defense game.

	Shin Hyesu, 2016.06
*/

#ifndef __TD_AIR_MONSTER_H__
#define __TD_AIR_MONSTER_H__

#include "TDMonster.h"

#define MONSTER_AIR_OFFSET 2.0f


/**
	Class: TDAirMonster
		Represent a "Air-type monster" in tower defense game.
		Air-type monster is created at air(above the map) not land(on the map).
		Inherit TDMonster.
*/
class TDAirMonster : public TDMonster {
public:
	TDAirMonster(float fPosMapEndX = MONSTER_DEFAULT_POS_X, float fPosMapEndY = MONSTER_DEFAULT_POS_Y, float fPosMapEndZ = MONSTER_DEFAULT_POS_Z);
};

#endif