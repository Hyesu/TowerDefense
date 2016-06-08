#include "TDMap.h"

TDMap::TDMap() : TDObject::TDObject(MAP_LENGTH_X, MAP_LENGTH_Y, MAP_LENGTH_Z, MAP_COLOR, MAP_COLOR, MAP_COLOR){
	D3DXVECTOR3 mapPos = D3DXVECTOR3(MAP_POS_X, MAP_POS_Y, MAP_POS_Z);
	_vPosition1 = mapPos;
	_vPosition2 += mapPos;
}