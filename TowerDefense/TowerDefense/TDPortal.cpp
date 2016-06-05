#include "TDPortal.h"

TDPortal::TDPortal(float fPosX, float fPosY, float fPosZ) {
	TDObject::init(COLOR_RED, COLOR_GREEN, COLOR_BLUE,
		fPosX, fPosY + 1.0f, fPosZ, NUM_CUBE);
	initPosition();
}
void TDPortal::initPosition() {
	Position p = _pPosList->at(0);
	_pPosList->push_back(Position(p._x, p._y + 1.0f, p._z));
}