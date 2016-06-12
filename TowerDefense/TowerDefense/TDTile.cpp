#include "TDTile.h"

TDTile::TDTile() 
	:TDObject(TILE_LENGTH, 0.0f, TILE_LENGTH, TILE_COLOR_RED, TILE_COLOR_GREEN, TILE_COLOR_BLUE) {
	setVisible(false);
}

void TDTile::setPosition(D3DXVECTOR3 vPosition) {
	_vPosition1 = vPosition;
	_vPosition2 = _vPosition1 + D3DXVECTOR3(TILE_LENGTH, 0.0f, TILE_LENGTH);
}