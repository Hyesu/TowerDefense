#include "TDMissile.h"

TDMissile::TDMissile(float fTowerPosX, float fTowerPosY, float fTowerPosZ, D3DXVECTOR3 vDirection)
	: TDObject(MISSILE_LENGTH, MISSILE_LENGTH, MISSILE_LENGTH, MISSILE_COLOR_RED, MISSILE_COLOR_GREEN, MISSILE_COLOR_BLUE) {
	D3DXVECTOR3 missilePos = D3DXVECTOR3(fTowerPosX, fTowerPosY, fTowerPosZ);
	_vPosition1 += missilePos;
	_vPosition2 += missilePos;

	_vDirection = MISSILE_MOVE_UNIT * vDirection;
}

// if missile moving is successful, return true
// but if missile is out of boundary, return false
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