#ifndef __TD_AIR_MONSTER_H__
#define __TD_AIR_MONSTER_H__

#include "TDMonster.h"

class TDAirMonster : public TDMonster {
private:

public:
	TDAirMonster(float fPosMapEndX = MONSTER_DEFAULT_POS_X, float fPosMapEndY = MONSTER_DEFAULT_POS_Y, float fPosMapEndZ = MONSTER_DEFAULT_POS_Z);
};

#endif