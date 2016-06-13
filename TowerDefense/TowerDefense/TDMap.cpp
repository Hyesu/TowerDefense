#include "TDMap.h"

#include <stdio.h>

TDMap::TDMap() : TDObject(MAP_LENGTH_X, MAP_LENGTH_Y, MAP_LENGTH_Z, MAP_COLOR, MAP_COLOR, MAP_COLOR){
	_nRow = MAP_NUM_ROW;
	_nCol = MAP_NUM_COL;

	D3DXVECTOR3 mapPos = D3DXVECTOR3(MAP_POS_X, MAP_POS_Y, MAP_POS_Z);
	_vPosition1 = mapPos;
	_vPosition2 += mapPos;

	_pObjectList = new std::vector<TDObject*>();
	_pObjectList->assign(MAP_NUM_ROW * MAP_NUM_COL, nullptr);
	_pDummyObject = new TDObject();
}
TDMap::~TDMap() {
	if (_pDummyObject != nullptr) {
		delete _pDummyObject;
		_pDummyObject = nullptr;
	}
	if (_pObjectList != nullptr) delete _pObjectList;
}

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
void TDMap::setAvailable(int row, int col, TDObject* pObject) {
	_pObjectList->at(row * MAP_NUM_COL + col) = pObject;
}

bool TDMap::isAvailableTile(int row, int col) const {
	return (_pObjectList->at(row * MAP_NUM_COL + col) == nullptr);
}
int TDMap::getRow() const {
	return _nRow;
}
int TDMap::getCol() const {
	return _nCol;
}
TDObject* TDMap::getObjectOn(int row, int col) {
	return _pObjectList->at(row * MAP_NUM_COL + col);
}