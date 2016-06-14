/**
	File: TDAirTower.cpp
		Define functions of TDAirTower class.

	Shin Hyesu, 2016.06
*/

#include "TDAirTower.h"


/**
	Function: TDAirTower
		Constructor of TDAirTower class.
		Init position and boundary of air-type tower.

	Params:
		vTowerPosition	the positon which the tower is built on
		vMapPosition1	lower boundary of map
		vMapPosition2	upper boundary of map
*/
TDAirTower::TDAirTower(D3DXVECTOR3 vTowerPosition, D3DXVECTOR3 vMapPosition1, D3DXVECTOR3 vMapPosition2)
	: TDTower(vTowerPosition, vMapPosition1, vMapPosition2) {
	_vUpperBound.y += TOWER_AIR_OFFSET;
	_vPosition2.y += TOWER_AIR_OFFSET;
}