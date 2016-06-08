#ifndef __TD_AIR_TOWER_H__
#define __TD_AIR_TOWER_H__

#include "TDTower.h"

class TDAirTower : public TDTower {
public:
	TDAirTower(D3DXVECTOR3 vTowerPosition, D3DXVECTOR3 vMapPosition1, D3DXVECTOR3 vMapPosition2);
};

#endif