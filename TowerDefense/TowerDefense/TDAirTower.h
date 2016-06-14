/**
	File: TDAirTower.h
		Define constants and class for representing air-type tower in tower defense game.

	Shin Hyesu, 2016.06
*/

#ifndef __TD_AIR_TOWER_H__
#define __TD_AIR_TOWER_H__

#include "TDTower.h"
#include "TDAirMonster.h"

#define TOWER_AIR_OFFSET	(MONSTER_AIR_OFFSET)


/**
	Class: TDAirTower
		Represent a "Air-type Tower" in tower defense game.
		Air-type tower creates missiles for air-type monster.
		Inherit TDTower.
*/
class TDAirTower : public TDTower {
public:
	TDAirTower(D3DXVECTOR3 vTowerPosition, D3DXVECTOR3 vMapPosition1, D3DXVECTOR3 vMapPosition2);
};

#endif