#include "TDMonster.h"

TDMonster::TDMonster() {
	
}
void TDMonster::setPortalPosition(Position posPortal) {
	_posPortal._x = posPortal._x;
	_posPortal._y = posPortal._y;
	_posPortal._z = posPortal._z;
}

void TDMonster::moveToPortal(float fDelta) {
	float fDeltaX = (_posPortal._x - getPosX()) * fDelta;
	float fDeltaY = (_posPortal._y - getPosY()) * fDelta;
	float fDeltaZ = (_posPortal._z - getPosZ()) * fDelta;

	for (int i = 0; i < _pPosList->size(); i++) {
		_pPosList->at(i)._x += fDeltaX;
		_pPosList->at(i)._y += fDeltaY;
		_pPosList->at(i)._z += fDeltaZ;
	}
}