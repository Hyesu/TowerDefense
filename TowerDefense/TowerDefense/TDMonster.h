/**
	File: TDMonster.h
		Define constants and class for representing monster in tower defense game.

	Shin Hyesu, 2016.06
*/

#ifndef __TD_MONSTER_H__
#define __TD_MONSTER_H__

#include "TDObject.h"

#define MONSTER_COLOR_RED		255
#define MONSTER_COLOR_GREEN		0
#define MONSTER_COLOR_BLUE		0

#define MONSTER_MOVE_UNIT		0.02f
#define MONSTER_MOVE_THRESHOLD	0.0f

#define MONSTER_LENGTH_X		1.0f
#define MONSTER_LENGTH_Y		1.0f
#define MONSTER_LENGTH_Z		1.0f

#define MONSTER_DEFAULT_POS_X	0.0f
#define MONSTER_DEFAULT_POS_Y	0.0f
#define MONSTER_DEFAULT_POS_Z	0.0f

#define MONSTER_NUM_TYPE		2		// land-type, air-type



/**
	Class: TDMonster
		Represent a "Monster" in tower defense game.
		Monsters move to portal by specific moving unit.
		Inherit TDObject.
*/
class TDMonster : public TDObject {
protected:
	D3DXVECTOR3 _vPortalPosition;	// target position for moving

public:
	TDMonster(float fPosMapEndX = MONSTER_DEFAULT_POS_X, float fPosMapEndY = MONSTER_DEFAULT_POS_Y, float fPosMapEndZ = MONSTER_DEFAULT_POS_Z);

	void setPortalPosition(D3DXVECTOR3 posPortal);
	void moveToPortal();

	enum MONSTER_TYPE {MONSTER_LAND, MONSTER_AIR};
};

#endif