#ifndef __TD_AIR_TOWER_H__
#define __TD_AIR_TOWER_H__

#include "TDTower.h"

class TDAirTower : public TDTower {
public:
	TDAirTower(float fMapPosX = TOWER_DEFAULT_POS_X, float fMapPosY = TOWER_DEFAULT_POS_Y, float fMapPosZ = TOWER_DEFAULT_POS_Z);
};

#endif