#ifndef __TD_TILE_H__
#define __TD_TILE_H__

#include "TDObject.h"

#define TILE_COLOR_RED				0
#define TILE_COLOR_GREEN			255
#define TILE_COLOR_BLUE				255

#define TILE_COLOR_RED_UNAVAIL		255
#define TILE_COLOR_GREEN_UNAVAIL	0
#define TILE_COLOR_BLUE_UNAVAIL		255

#define TILE_LENGTH					1.0f

class TDTile : public TDObject {
public:
	TDTile();

	void setPosition(D3DXVECTOR3 vPosition);
};

#endif