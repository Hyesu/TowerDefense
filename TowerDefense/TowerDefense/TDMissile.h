#ifndef __TD_MISSILE_H__
#define __TD_MISSILE_H__

#include "TDObject.h"

#define MISSILE_COLOR_RED			255
#define MISSILE_COLOR_GREEN			255
#define MISSILE_COLOR_BLUE			0

#define MISSILE_LENGTH				1.0f

#define MISSILE_MOVE_UNIT			0.1f
#define MISSLE_DEFAULT_DIRECTION	D3DXVECTOR3(1.0f, 0.0f, -1.0f)

class TDMissile : public TDObject {
private:
	D3DXVECTOR3 _vDirection;

public:
	TDMissile(float fTowerPosX, float fTowerPosY, float fTowerPosZ);

	bool move(D3DXVECTOR3 vBoundary1, D3DXVECTOR3 vBoundary2);
};
#endif