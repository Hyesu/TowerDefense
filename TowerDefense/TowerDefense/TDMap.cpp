/**
	File: TDMap.cpp
		Define functions of TDMap class.

	Shin Hyesu, 2016.06
*/

#include "TDMap.h"

/**
	Function: TDMap
		Constructor of TDMap class.
		Init the number of row and column of map.
		Init position of map.
		Init object list for managing object data which is on the map.
*/
TDMap::TDMap() : TDObject(MAP_LENGTH_X, MAP_LENGTH_Y, MAP_LENGTH_Z, MAP_COLOR, MAP_COLOR, MAP_COLOR){
	_nRow = MAP_NUM_ROW;
	_nCol = MAP_NUM_COL;

	D3DXVECTOR3 mapPos = D3DXVECTOR3(MAP_POS_X, MAP_POS_Y, MAP_POS_Z);
	_vPosition1 = mapPos;
	_vPosition2 += mapPos;

	_pObjectList = new std::vector<TDObject*>();
	_pObjectList->assign(MAP_NUM_ROW * MAP_NUM_COL, nullptr);
	_pDummyObject = new TDObject();

	_nType = TYPE_MAP;
}
/**
	Function: ~TDMap
		Destructor of TDMap class.
		Delete object list and dummy object.
*/
TDMap::~TDMap() {
	if (_pDummyObject != nullptr) {
		delete _pDummyObject;
		_pDummyObject = nullptr;
	}
	if (_pObjectList != nullptr) delete _pObjectList;
}


/**
	Function: setPortalAndMonster
		Marking object list to unavailable from portal position to monster position.
		It is for user not to build tower on monster moving path.

	Params:
		vPortal		position of portal (x, y, z)
		vMonster	position of monster (x, y, z)
*/
void TDMap::setPortalAndMonster(D3DXVECTOR3 vPortal, D3DXVECTOR3 vMonster) {
	int portalRow = (int)(vPortal.z - _vPosition1.z);
	int portalCol = (int)(vPortal.x - _vPosition1.x);
	int monsterRow = (int)(vMonster.z - _vPosition1.z);
	int monsterCol = (int)(vMonster.x - _vPosition1.x);
	
	_pObjectList->at(portalRow * MAP_NUM_COL + portalCol) = _pDummyObject;
	_pObjectList->at(monsterRow * MAP_NUM_COL + monsterCol) = _pDummyObject;

	// path for monster is not available for building tower
	int rowShift = portalRow < monsterRow ? 1 : -1;
	int colShift = portalCol < monsterCol ? 1 : -1;
	for (int i = portalRow, j = portalCol; i != monsterRow && j != monsterCol; i += rowShift, j += colShift) {
		_pObjectList->at(i * MAP_NUM_COL + j) = _pDummyObject;
	}
}
/**
	Function: setAvailable
		Set object list by some object.

	Params:
		row 		integer value for row of object
		col 		integer value for column of object
		pObject 	target object to be managed by object list of map
*/
void TDMap::setAvailable(int row, int col, TDObject* pObject) {
	_pObjectList->at(row * MAP_NUM_COL + col) = pObject;
}

/**
	Function: isAvailable
		Check the tile is available to build tower on the map.

	Params:
		row 	integer value for row of object
		col 	integer value for column of object
	Return:
		boolean value for availibility to build tower.
		If the object list at (row, col) points some object, reutrn false.
		If the object list at (row, col) points null, return true. 
*/
bool TDMap::isAvailableTile(int row, int col) const {
	return (_pObjectList->at(row * MAP_NUM_COL + col) == nullptr);
}
/**
	Function: getRow
		Getter for the number of row of map

	Return:
		integer value for the number of row
*/
int TDMap::getRow() const {
	return _nRow;
}
/**
	Function: getCol
		Getter for the number of column of map

	Return:
		integer value for the number of column
*/
int TDMap::getCol() const {
	return _nCol;
}
/**
	Function: getObjectOn
		Getter for object in the object list (row, col)

	Params:
		row 	integer value for row number of object list
		col 	integer value for column number of object list
	Return:
		the object which is in the object list (row, col)
*/
TDObject* TDMap::getObjectOn(int row, int col) {
	return _pObjectList->at(row * MAP_NUM_COL + col);
}