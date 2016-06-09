#ifndef __TD_MAP_H__
#define __TD_MAP_H__

#include "TDObject.h"

#define MAP_COLOR		64

#define MAP_NUM_ROW		10
#define MAP_NUM_COL		(MAP_NUM_ROW)

#define MAP_LENGTH_X	(1.0f * MAP_NUM_ROW)
#define MAP_LENGTH_Y	1.0f
#define MAP_LENGTH_Z	(MAP_LENGTH_X)

#define MAP_POS_X		((float) (MAP_LENGTH_X / 2 * -1))
#define MAP_POS_Y		0.0f
#define MAP_POS_Z		(MAP_POS_X)

class TDMap : public TDObject{
private:
	int _nRow, _nCol;
	bool _bAvailable[MAP_NUM_ROW][MAP_NUM_COL];

public:
	TDMap();

	void setPortalAndMonster(D3DXVECTOR3 vPortal, D3DXVECTOR3 vMonster);
	bool isAvailableTile(int row, int col) const;
	int getRow() const;
	int getCol() const;
};

#endif