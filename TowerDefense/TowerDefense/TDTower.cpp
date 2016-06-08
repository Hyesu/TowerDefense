#include "TDTower.h"

TDTower::TDTower(D3DXVECTOR3 vTowerPositon, D3DXVECTOR3 vMapPosition1, D3DXVECTOR3 vMapPosition2) :
	TDObject::TDObject(TOWER_LENGTH, TOWER_LENGTH, TOWER_LENGTH,
		TOWER_COLOR_RED, TOWER_COLOR_GREEN, TOWER_COLOR_BLUE) {
	D3DXVECTOR3 towerPos = vTowerPositon;
	towerPos.y += 1.0f;
	_vPosition1 = towerPos;
	_vPosition2 += towerPos;

	_pMissileList = new std::list<TDMissile*>();

	_vMissileBoundary1 = vMapPosition1;
	_vMissileBoundary2 = vMapPosition2;
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
		it != _pMissileList->end();) {
		TDMissile* pMissile = (TDMissile*) (*it);
		if (!pMissile->move(_vMissileBoundary1, _vMissileBoundary2)) {
			// missile is out of map. delete missile
			delete pMissile;
			it = _pMissileList->erase(it);
		}
		else
			++it;
	}
}

std::list<TDMissile*>* TDTower::getMissileList() const {
	return _pMissileList;
}

bool TDTower::handleCollideWith(const TDObject* pMonster) {
	for (std::list<TDMissile*>::iterator it = _pMissileList->begin(); it != _pMissileList->end(); ) {
		TDMissile* pMissile = (TDMissile*)(*it);
		if (pMonster->collideWith(pMissile)) {
			// missile collide with the monster
			delete pMissile;
			it = _pMissileList->erase(it);
			return true;
		}
		else
			++it;
	}
	return false;
}