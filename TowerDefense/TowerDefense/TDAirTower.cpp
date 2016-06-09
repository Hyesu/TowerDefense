#include "TDAirTower.h"

TDAirTower::TDAirTower(D3DXVECTOR3 vTowerPosition, D3DXVECTOR3 vMapPosition1, D3DXVECTOR3 vMapPosition2)
	: TDTower(vTowerPosition, vMapPosition1, vMapPosition2) {
	_vUpperBound.y += TOWER_AIR_OFFSET;
	_vPosition2.y += TOWER_AIR_OFFSET;
}