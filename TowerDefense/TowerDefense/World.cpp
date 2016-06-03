#include "World.h"

World::World() {
	init();
}
void World::init() {
	_pTileList = new vector<LPD3DXMESH*>(WORLD_SIZE);
	
	for (int i = 0; i < WORLD_SIZE; i++) {
	}
}