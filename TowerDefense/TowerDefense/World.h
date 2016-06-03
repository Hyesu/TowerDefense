#ifndef __TD_WORLD_H__
#define __TD_WORLD_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#define WORLD_SIZE	25

using namespace std;

class World
{
private:
	vector<LPD3DXMESH*>* _pTileList;

	void init();

public:
	World();	
};

#endif