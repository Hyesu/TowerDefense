/**
	File: TDMissile.h
		Define constants and class for representing missile in tower defense game.

	Shin Hyesu, 2016.06
*/

#ifndef __TD_MISSILE_H__
#define __TD_MISSILE_H__

#include "TDObject.h"

#define MISSILE_COLOR_RED			255
#define MISSILE_COLOR_GREEN			255
#define MISSILE_COLOR_BLUE			0

#define MISSILE_LENGTH				1.0f

#define MISSILE_MOVE_UNIT			0.1f
#define MISSILE_NUM_DIRECTION		4


/**
	Class: TDMissile
		Represent a "Missile" in tower defense game.
		Missile move by specific direction and velocity.
		Inherit TDObject.
		Missile is created and managed by TDTower class.
*/
class TDMissile : public TDObject {
private:
	D3DXVECTOR3 _vDirection;	// direction for moving

public:
	TDMissile(float fTowerPosX, float fTowerPosY, float fTowerPosZ, D3DXVECTOR3 vDirection);

	bool move(D3DXVECTOR3 vBoundary1, D3DXVECTOR3 vBoundary2);
};
#endif