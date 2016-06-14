/**
	File: TDTile.h
		Define constants for tile in tower defense game.

	Shin Hyesu, 2016.06
*/

#ifndef __TD_TILE_H__
#define __TD_TILE_H__

#include "TDObject.h"

#define TILE_COLOR_RED				0
#define TILE_COLOR_GREEN			255
#define TILE_COLOR_BLUE				255

#define TILE_COLOR_RED_UNAVAIL		255
#define TILE_COLOR_GREEN_UNAVAIL	0
#define TILE_COLOR_BLUE_UNAVAIL		255

#define TILE_LENGTH					(OBJECT_DEFAULT_LENGTH)


/**
	Class: TDTile
		Represent a "Tile" in tower defense game.
		Tile is used to represent position of user mouse cursor.
		If user mouse hover on available(to build tower) tile, the tile color will be "TILE_COLOR_R/G/B".
		But if user mouse hover on unavailable tile, the tile color will be "TILE_COLOR_R/G/B_UNAVAIL"
		Inherit TDObject.
*/
class TDTile : public TDObject {
public:
	TDTile();

	void setPosition(D3DXVECTOR3 vPosition);
};

#endif