/**
	File: TDMissile.cpp
		Define functions of TDMissile class.

	Shin Hyesu, 2016.06
*/

#include "TDMissile.h"


/**
	Function: TDMissile
		Constructor of TDMissile class.
		Init position and direction of missile.

	Params:
		fTowerPosX		float value for x-position of tower creating missile.
		fTowerPosY		float value for y-position of tower creating missile.
		fTowerPosZ		float value for z-position of tower creating missile.
		vDirection 		direction of missile (x, y, z)
*/
TDMissile::TDMissile(float fTowerPosX, float fTowerPosY, float fTowerPosZ, D3DXVECTOR3 vDirection)
	: TDObject(MISSILE_LENGTH, MISSILE_LENGTH, MISSILE_LENGTH, MISSILE_COLOR_RED, MISSILE_COLOR_GREEN, MISSILE_COLOR_BLUE) {
	D3DXVECTOR3 missilePos = D3DXVECTOR3(fTowerPosX, fTowerPosY, fTowerPosZ);
	_vPosition1 += missilePos;
	_vPosition2 += missilePos;

	_vDirection = MISSILE_MOVE_UNIT * vDirection;

	_nType = TYPE_MISSILE;
}

/**
	Function: move
		move missile by _vDirection

	Params:
		vBoundary1	lower boundary which in missile can move
		vBoundary2	upper boundary which in missile can move
	Return:
		boolean value for result of moving.
		If missile move in boundary, return true.
		If missile move out of boundary, return false.
*/
bool TDMissile::move(D3DXVECTOR3 vBoundary1, D3DXVECTOR3 vBoundary2) {
	_vPosition1 += _vDirection;
	_vPosition2 += _vDirection;

	if (_vPosition1.x > vBoundary2.x 
		|| _vPosition2.x < vBoundary1.x
		|| _vPosition1.z > vBoundary2.z
		|| _vPosition2.z < vBoundary1.z)
		return false;
	else
		return true;
}