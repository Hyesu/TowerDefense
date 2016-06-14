/**
	File: TDTile.cpp
		Define functions of TowerDefense class.

	Shin Hyesu, 2016.06
*/

#include "TDTile.h"


/**
	Function: TDTile
		Constructor of TDTile class.
*/
TDTile::TDTile() 
	:TDObject(TILE_LENGTH, 0.0f, TILE_LENGTH, TILE_COLOR_RED, TILE_COLOR_GREEN, TILE_COLOR_BLUE) {
	setVisible(false);

	_nType = TYPE_TILE;
}

/**
	Function: setPosition
		Set position of tile.

	Params:
		vPosition  new position of tile(x, y, z)
*/
void TDTile::setPosition(D3DXVECTOR3 vPosition) {
	_vPosition1 = vPosition;
	_vPosition2 = _vPosition1 + D3DXVECTOR3(TILE_LENGTH, 0.0f, TILE_LENGTH);
}