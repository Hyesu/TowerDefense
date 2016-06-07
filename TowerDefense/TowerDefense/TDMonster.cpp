#include "TDMonster.h"

TDMonster::TDMonster() {
	
}
void TDMonster::setPortalPosition(Position posPortal) {
	_posPortal._x = posPortal._x;
	_posPortal._y = posPortal._y;
	_posPortal._z = posPortal._z;
}

void TDMonster::moveToPortal() {
	float fDeltaX, fDeltaZ;
	fDeltaX = fDeltaZ = 0;
	
	if (_posPortal._x - getPosX() > MONSTER_MOVE_THRESHOLD) fDeltaX = MONSTER_MOVE_UNIT;
	else fDeltaX = -MONSTER_MOVE_UNIT;

	if (_posPortal._z - getPosZ() > MONSTER_MOVE_THRESHOLD) fDeltaZ = MONSTER_MOVE_UNIT;
	else fDeltaZ = -MONSTER_MOVE_UNIT;

	for (int i = 0; i < _pPosList->size(); i++) {
		_pPosList->at(i)._x += fDeltaX;
		_pPosList->at(i)._z += fDeltaZ;
	}
}