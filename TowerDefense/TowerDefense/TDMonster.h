#ifndef __TD_MONSTER_H__
#define __TD_MONSTER_H__

#include "TDObject.h"

#define MONSTER_COLOR_RED	255
#define MONSTER_COLOR_GREEN 0
#define MONSTER_COLOR_BLUE	0

#define MONSTER_NUM_CUBE	1

class TDMonster : public TDObject {
private:

public:
	TDMonster(float fPosX = 0.0f, float fPosY = 0.0f, float fPosZ = 0.0f);
};

#endif