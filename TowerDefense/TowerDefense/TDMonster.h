#ifndef __TD_MONSTER_H__
#define __TD_MONSTER_H__

#include "TDObject.h"

#define MONSTER_COLOR_RED	255
#define MONSTER_COLOR_GREEN 0
#define MONSTER_COLOR_BLUE	0

#define MONSTER_NUM_CUBE	1

#define MONSTER_POS_Y_LAND	1.0f
#define MONSTER_POS_Y_AIR	(MONSTER_POS_Y_LAND + 1.0f)

class TDMonster : public TDObject {
private:

public:
	TDMonster();
};

#endif