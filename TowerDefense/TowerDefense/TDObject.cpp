#include "TDObject.h"

#include "TDMap.h"

TDObject::TDObject() {
	_nRed = _nGreen = _nBlue = 0;
	_nNumCube = 0;
	_pPosList = nullptr;
}
void TDObject::init(int nRed, int nGreen, int nBlue,
	float fPosX, float fPosY, float fPosZ, int nNumCube) {
	// set tile color
	_nRed = nRed;
	_nGreen = nGreen;
	_nBlue = nBlue;
	
	_nNumCube = nNumCube;
	_pPosList = new vector<Position>();

	// set position of first tile
	_pPosList->push_back(Position(fPosX, fPosY, fPosZ));
}

// getter
int TDObject::getRed() const {
	return _nRed;
}
int TDObject::getGreen() const {
	return _nGreen;
}
int TDObject::getBlue() const {
	return _nBlue;
}

int TDObject::getNumCube() const {
	return _nNumCube;
}

float TDObject::getPosX(int nIndex) const {
	if (_pPosList != nullptr)
		return _pPosList->at(nIndex)._x;
	else
		return 0.0f;
}
float TDObject::getPosY(int nIndex) const {
	if (_pPosList != nullptr)
		return _pPosList->at(nIndex)._y;
	else 
		return 0.0f;
}
float TDObject::getPosZ(int nIndex) const {
	if (_pPosList != nullptr)
		return _pPosList->at(nIndex)._z;
	else
		return 0.0f;
}