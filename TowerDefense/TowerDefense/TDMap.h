#ifndef __TD_MAP_H__
#define __TD_MAP_H__

#include "TDObject.h"

#define MAP_COLOR		64

#define MAP_LENGTH_X	6.0f
#define MAP_LENGTH_Y	1.0f
#define MAP_LENGTH_Z	(MAP_LENGTH_X)

#define MAP_POS_X		((float) (MAP_LENGTH_X / 2 * -1))
#define MAP_POS_Y		0.0f
#define MAP_POS_Z		(MAP_POS_X)

class TDMap : public TDObject{
public:
	TDMap();
};

#endif