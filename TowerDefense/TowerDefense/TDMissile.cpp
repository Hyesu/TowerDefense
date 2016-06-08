#include "TDMissile.h"

TDMissile::TDMissile(float fTowerPosX, float fTowerPosY, float fTowerPosZ)
	: TDObject(MISSILE_LENGTH, MISSILE_LENGTH, MISSILE_LENGTH, MISSILE_COLOR_RED, MISSILE_COLOR_GREEN, MISSILE_COLOR_BLUE) {
	D3DXVECTOR3 missilePos = D3DXVECTOR3(fTowerPosX, fTowerPosY, fTowerPosZ);
	_vPosition1 += missilePos;
	_vPosition2 += missilePos;

	_vDirection = MISSILE_MOVE_UNIT * MISSLE_DEFAULT_DIRECTION;
}

void TDMissile::move() {
	_vPosition1 += _vDirection;
	_vPosition2 += _vDirection;
}