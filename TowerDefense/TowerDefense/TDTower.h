#ifndef __TD_TOWER_H__
#define __TD_TOWER_H__

#include "TDObject.h"

#define TOWER_DEFAULT_POS_X	0.0f
#define TOWER_DEFAULT_POS_Y	0.0f
#define TOWER_DEFAULT_POS_Z	0.0f

#define TOWER_COLOR_RED		0
#define TOWER_COLOR_GREEN	0
#define TOWER_COLOR_BLUE	255

#define TOWER_LENGTH		1.0f


class TDTower : public TDObject {
public:
	TDTower(float fMapPosX = TOWER_DEFAULT_POS_X, float fMapPosY = TOWER_DEFAULT_POS_Y, float fMapPosZ = TOWER_DEFAULT_POS_Z);
};

#endif
