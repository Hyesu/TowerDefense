#include "TDMap.h"

TDMap::TDMap() {
	init();
}
void TDMap::init() {
	// set tile color
	_nRed = TILE_COLOR;
	_nGreen = TILE_COLOR;
	_nBlue = TILE_COLOR;

	// set the number of tiles
	_nNumRow = TILE_NUM_ROW;
	_nNumCol = TILE_NUM_COL;

	// set position of tile
	_fPosX = TILE_POS_X;
	_fPosY = TILE_POS_Y;
	_fPosZ = TILE_POS_Z;
}

// getter
int TDMap::getRed() const {
	return _nRed;
}
int TDMap::getGreen() const {
	return _nGreen;
}
int TDMap::getBlue() const {
	return _nBlue;
}

int TDMap::getNumRow() const {
	return _nNumRow;
}
int TDMap::getNumCol() const {
	return _nNumCol;
}

float TDMap::getPosX() const {
	return _fPosX;
}
float TDMap::getPosY() const {
	return _fPosY;
}
float TDMap::getPosZ() const {
	return _fPosZ;
}