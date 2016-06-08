#include "TDTower.h"

TDTower::TDTower(float fMapPosX, float fMapPosY, float fMapPosZ) :
	TDObject::TDObject(TOWER_LENGTH, TOWER_LENGTH, TOWER_LENGTH,
		TOWER_COLOR_RED, TOWER_COLOR_GREEN, TOWER_COLOR_BLUE) {
	D3DXVECTOR3 towerPos = D3DXVECTOR3(fMapPosX, fMapPosY + 1.0f, fMapPosZ);
	_vPosition1 = towerPos;
	_vPosition2 += towerPos;
}