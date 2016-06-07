#ifndef __TD_MONSTER_H__
#define __TD_MONSTER_H__

#include "TDObject.h"

#define MONSTER_COLOR_RED	255
#define MONSTER_COLOR_GREEN 0
#define MONSTER_COLOR_BLUE	0

#define MONSTER_NUM_CUBE	1

#define MONSTER_POS_Y_LAND	1.0f
#define MONSTER_POS_Y_AIR	(MONSTER_POS_Y_LAND + 1.0f)

#define MONSTER_MOVE_UNIT		0.05f
#define MONSTER_MOVE_THRESHOLD	0.0f

class TDMonster : public TDObject {
protected:
	Position _posPortal;

public:
	TDMonster();

	void setPortalPosition(Position posPotal);
	void moveToPortal();
};

#endif