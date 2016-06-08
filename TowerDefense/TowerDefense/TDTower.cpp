#include "TDTower.h"

TDTower::TDTower(float fMapPosX, float fMapPosY, float fMapPosZ) :
	TDObject::TDObject(TOWER_LENGTH, TOWER_LENGTH, TOWER_LENGTH,
		TOWER_COLOR_RED, TOWER_COLOR_GREEN, TOWER_COLOR_BLUE) {
	D3DXVECTOR3 towerPos = D3DXVECTOR3(fMapPosX, fMapPosY + 1.0f, fMapPosZ);
	_vPosition1 = towerPos;
	_vPosition2 += towerPos;

	_pMissileList = new std::list<TDMissile*>();
}
TDTower::~TDTower() {
	if (_pMissileList != nullptr) delete _pMissileList;
}

void TDTower::createMissile() {
	_pMissileList->push_back(new TDMissile(_vPosition2.x - TOWER_LENGTH, _vPosition2.y - TOWER_LENGTH, _vPosition2.z - TOWER_LENGTH));
}
void TDTower::moveMissile() {
	if (_pMissileList->empty()) return;

	for (std::list<TDMissile*>::iterator it = _pMissileList->begin();
		it != _pMissileList->end(); ++it) {
		TDMissile* pMissile = (TDMissile*) (*it);
		pMissile->move();
	}
}

std::list<TDMissile*>* TDTower::getMissileList() const {
	return _pMissileList;
}