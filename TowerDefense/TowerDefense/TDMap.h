/**
	File: TDMap.h
		Define constants and class for representing map in tower defense game.

	Shin Hyesu, 2016.06
*/

#ifndef __TD_MAP_H__
#define __TD_MAP_H__

#include <vector>
#include "TDObject.h"

#define MAP_COLOR		64	// map color will be RGB(MAP_COLOR, MAP_COLOR, MAP_COLOR)

#define MAP_NUM_ROW		10
#define MAP_NUM_COL		(MAP_NUM_ROW)

#define MAP_LENGTH_X	(OBJECT_DEFAULT_LENGTH * MAP_NUM_ROW)
#define MAP_LENGTH_Y	(OBJECT_DEFAULT_LENGTH)
#define MAP_LENGTH_Z	(MAP_LENGTH_X)

#define MAP_POS_X		((float) (MAP_LENGTH_X / 2 * -1))
#define MAP_POS_Y		0.0f
#define MAP_POS_Z		(MAP_POS_X)



/**
	Class: TDMap
		Represent a "Map" in tower defense game.
		Map handles list of TDObject which is on the map.
		Inherit TDObject.
*/
class TDMap : public TDObject{
private:
	int _nRow, _nCol;	// the number of row and column for map
	
	std::vector<TDObject*>* _pObjectList;	// used for handling the data of TDObject which is on the map
	TDObject* 				_pDummyObject; 	// used for marking unavailable tile

public:
	TDMap();
	~TDMap();

	// setter
	void setPortalAndMonster(D3DXVECTOR3 vPortal, D3DXVECTOR3 vMonster);
	void setAvailable(int row, int col, TDObject* pObject);

	// getter
	bool isAvailableTile(int row, int col) const;
	int getRow() const;
	int getCol() const;
	TDObject* getObjectOn(int row, int col);
};

#endif