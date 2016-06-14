/**
	File: TDTower.cpp
		Init static variables of TDTower class.
		Define functions of TDTower class.

	Shin Hyesu, 2016.06
*/

#include "TDTower.h"

// missile direction(4 directions)
const D3DXVECTOR3 TDTower::s_vMissileDirection[] = {
	D3DXVECTOR3(0.0f, 0.0f, -1.0f),
	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),
	D3DXVECTOR3(0.0f, 0.0f, 1.0f),
	D3DXVECTOR3(1.0f, 0.0f, 0.0f)
};

/**
	Function: TDTower
		Constructor of TDTower class.
		Init position of tower, create empty list for missiles.
		Set boundary of missile, in which missiles can move.

	Params:
		vTowerPosition	the positon which the tower is built on
		vMapPosition1	lower boundary of map
		vMapPosition2	upper boundary of map
*/
TDTower::TDTower(D3DXVECTOR3 vTowerPositon, D3DXVECTOR3 vMapPosition1, D3DXVECTOR3 vMapPosition2) :
	TDObject(TOWER_LENGTH, TOWER_LENGTH, TOWER_LENGTH, TOWER_COLOR_RED, TOWER_COLOR_GREEN, TOWER_COLOR_BLUE) {
	D3DXVECTOR3 towerPos = vTowerPositon;
	towerPos.y += 1.0f;
	_vPosition1 = towerPos;
	_vPosition2 += towerPos;

	_pMissileList = new std::list<TDMissile*>();

	_vMissileBoundary1 = D3DXVECTOR3(
		vMapPosition1.x < _vPosition1.x - TOWER_BOUNDARY ? _vPosition1.x - TOWER_BOUNDARY : vMapPosition1.x,
		vMapPosition1.y,
		vMapPosition1.z < _vPosition1.z - TOWER_BOUNDARY ? _vPosition1.z - TOWER_BOUNDARY : vMapPosition1.z);
	_vMissileBoundary2 = D3DXVECTOR3(
		vMapPosition2.x > _vPosition2.x + TOWER_BOUNDARY ? _vPosition2.x + TOWER_BOUNDARY : vMapPosition2.x,
		vMapPosition2.y,
		vMapPosition2.z > _vPosition2.z + TOWER_BOUNDARY ? _vPosition2.z + TOWER_BOUNDARY : vMapPosition2.z);

	_nMissileDirectionIndex = 0;

	_nType = TYPE_TOWER;
}
/**
	Function: ~TDTower
		Destructor of TDTower class.
		Delete missile list.
*/
TDTower::~TDTower() {
	if (_pMissileList != nullptr) delete _pMissileList;
}

/**
	Function: createMissile
		Create missile and push it into the missile list.
*/
void TDTower::createMissile() {
	_pMissileList->push_back(new TDMissile(_vPosition2.x - TOWER_LENGTH, _vPosition2.y - TOWER_LENGTH, 
		_vPosition2.z - TOWER_LENGTH, s_vMissileDirection[_nMissileDirectionIndex]));
}
/**
	Function: moveMissile
		Move all missiles in missile list.
		Check missiles are in boundary. 
		If a missile is not in boundary, delete it and erase it from list.
*/
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

/**
	Function: getMissileList
		Getter of missile list.
	Return:
		list of missile
*/
std::list<TDMissile*>* TDTower::getMissileList() const {
	return _pMissileList;
}

/**
	Function: handleCollideWith
		Check collision between all missiles in missile list and a object.
		If there is a collision, delete the missile and erase it from missile list.

	Params:
		pObject		target object for checking collision
	Return:
		boolean value of collision result
*/
bool TDTower::handleCollideWith(const TDObject* pObject) {
	for (std::list<TDMissile*>::iterator it = _pMissileList->begin(); it != _pMissileList->end(); ) {
		TDMissile* pMissile = (TDMissile*)(*it);
		if (pObject->collideWith(pMissile)) {
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

/**
	Function: changeMissileDirection
		Change direction of missile moving.
*/
void TDTower::changeMissileDirection() {
	_nMissileDirectionIndex = (_nMissileDirectionIndex + 1) % MISSILE_NUM_DIRECTION;
}