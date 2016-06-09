#include "TDMap.h"

TDMap::TDMap() : TDObject::TDObject(MAP_LENGTH_X, MAP_LENGTH_Y, MAP_LENGTH_Z, MAP_COLOR, MAP_COLOR, MAP_COLOR){
	D3DXVECTOR3 mapPos = D3DXVECTOR3(MAP_POS_X, MAP_POS_Y, MAP_POS_Z);
	_vPosition1 = mapPos;
	_vPosition2 += mapPos;

	for (int i = 0; i < MAP_NUM_ROW; i++) {
		for (int j = 0; j < MAP_NUM_COL; j++)
			_bAvailable[i][j] = true;
	}
}

void TDMap::setPortalAndMonster(D3DXVECTOR3 vPortal, D3DXVECTOR3 vMonster) {
	int portalRow = (int)(vPortal.z - _vPosition1.z);
	int portalCol = (int)(vPortal.x - _vPosition1.x);
	int monsterRow = (int)(vMonster.z - _vPosition1.z);
	int monsterCol = (int)(vMonster.x - _vPosition1.x);

	_bAvailable[portalRow][portalCol] = false;
	_bAvailable[monsterRow][monsterCol] = false;

	// path for monster is not available for building tower
	int rowShift = portalRow < monsterRow ? 1 : -1;
	int colShift = portalCol < monsterCol ? 1 : -1;
	for (int i = portalRow; i != monsterRow; i += rowShift) {
		for (int j = portalCol; j != monsterCol; j += colShift)
			_bAvailable[i][j] = false;
	}
}