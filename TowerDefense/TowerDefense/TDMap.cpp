#include "TDMap.h"

TDMap::TDMap() {
	_nNumRow = TILE_NUM_ROW;
	_nNumCol = TILE_NUM_COL;
	TDObject::init(TILE_COLOR, TILE_COLOR, TILE_COLOR,
			 TILE_POS_X, TILE_POS_Y, TILE_POS_Z, _nNumRow * _nNumCol);
	initPosition();
}
void TDMap::initPosition() {
	for (int i = 1; i < _nNumCol * _nNumRow; i++) {
		_pPosList->push_back(Position(TILE_POS_X + i % TILE_NUM_COL,
									  TILE_POS_Y,
									  TILE_POS_Z + i / TILE_NUM_ROW));
	}
}

int TDMap::getNumRow() const {
	return _nNumRow;
}
int TDMap::getNumCol() const {
	return _nNumCol;
}