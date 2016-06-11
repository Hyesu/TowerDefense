#ifndef __TD_MONSTER_H__
#define __TD_MONSTER_H__

#include "TDObject.h"

#define MONSTER_COLOR_RED		255
#define MONSTER_COLOR_GREEN		0
#define MONSTER_COLOR_BLUE		0

#define MONSTER_MOVE_UNIT		0.05f
#define MONSTER_MOVE_THRESHOLD	0.0f

#define MONSTER_LENGTH_X		1.0f
#define MONSTER_LENGTH_Y		1.0f
#define MONSTER_LENGTH_Z		1.0f

#define MONSTER_DEFAULT_POS_X	0.0f
#define MONSTER_DEFAULT_POS_Y	0.0f
#define MONSTER_DEFAULT_POS_Z	0.0f

class TDMonster : public TDObject {
protected:
	D3DXVECTOR3 _vPortalPosition;

public:
	TDMonster(float fPosMapEndX = MONSTER_DEFAULT_POS_X, float fPosMapEndY = MONSTER_DEFAULT_POS_Y, float fPosMapEndZ = MONSTER_DEFAULT_POS_Z);

	void setPortalPosition(D3DXVECTOR3 posPortal);
	void moveToPortal();
};

#endif