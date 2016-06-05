#ifndef __TD_MAP_H__
#define __TD_MAP_H__

#include "TDObject.h"

#define TILE_COLOR		64
#define TILE_NUM_ROW	5
#define TILE_NUM_COL	(TILE_NUM_ROW)

#define TILE_POS_X		((float) (TILE_NUM_ROW * -1))
#define TILE_POS_Y		(TILE_POS_X)
#define TILE_POS_Z		0.0f

class TDMap : public TDObject{
private:
	int _nNumRow, _nNumCol;			// number of tiles

	void initPosition();

public:
	TDMap();

	int getNumRow() const;
	int getNumCol() const;
};

#endif