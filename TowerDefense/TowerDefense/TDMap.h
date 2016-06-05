#ifndef __TD_MAP_H__
#define __TD_MAP_H__

#define TILE_COLOR		64
#define TILE_NUM_ROW	5
#define TILE_NUM_COL	(TILE_NUM_ROW)

#define TILE_POS_X		((float) (TILE_NUM_ROW * -1))
#define TILE_POS_Y		(TILE_POS_X)
#define TILE_POS_Z		0.0f

class TDMap {
private:
	int _nRed, _nGreen, _nBlue;	// color
	int _nNumRow, _nNumCol;			// number of tiles
	float _fPosX, _fPosY, _fPosZ;	// position

public:
	TDMap();

	void init();

	// getter
	int getRed() const;
	int getGreen() const;
	int getBlue() const;

	int getNumRow() const;
	int getNumCol() const;
	
	float getPosX() const;
	float getPosY() const;
	float getPosZ() const;
};

#endif