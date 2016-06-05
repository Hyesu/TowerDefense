#include "TDObject.h"

#include "TDMap.h"

TDObject::TDObject() {
	_nRed = _nGreen = _nBlue = 0;
	_fPosX = _fPosY = _fPosZ = 0.0f;
	_nNumCube = 0;
}
void TDObject::init(int nRed, int nGreen, int nBlue,
	float fPosX, float fPosY, float fPosZ, int nNumCube) {
	// set tile color
	_nRed = nRed;
	_nGreen = nBlue;
	_nBlue = nGreen;

	// set position of tile
	_fPosX = fPosX;
	_fPosY = fPosY;
	_fPosZ = fPosZ;

	_nNumCube = nNumCube;
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

float TDObject::getPosX() const {
	return _fPosX;
}
float TDObject::getPosY() const {
	return _fPosY;
}
float TDObject::getPosZ() const {
	return _fPosZ;
}