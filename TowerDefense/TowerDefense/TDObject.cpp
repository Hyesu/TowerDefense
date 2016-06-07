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
	_posLowerBound = Position(fPosX, fPosY, fPosZ);
	_posUpperBound = Position(fPosX + 1.0f, fPosY + 1.0f, fPosZ + 1.0f);
}
void TDObject::setBound() {
	for (int i = 1; i < _pPosList->size(); i++) {
		Position position = _pPosList->at(i);

		_posLowerBound._x = _posLowerBound._x < position._x ? position._x : _posLowerBound._x;
		_posLowerBound._y = _posLowerBound._y < position._y ? position._y : _posLowerBound._y;
		_posLowerBound._z = _posLowerBound._z < position._z ? position._z : _posLowerBound._z;

		_posUpperBound._x = _posUpperBound._x < position._x + 1.0f ? position._x + 1.0f : _posUpperBound._x;
		_posUpperBound._y = _posUpperBound._y < position._y + 1.0f ? position._y + 1.0f : _posUpperBound._y;
		_posUpperBound._z = _posUpperBound._z < position._z + 1.0f ? position._z + 1.0f : _posUpperBound._z;
	}
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

Position TDObject::getPosition(int nIndex) const {
	return _pPosList->at(nIndex);
}
bool TDObject::collideWith(const TDObject* pOther) const {
	// check X-axis
	bool bCollisionX = (_posLowerBound._x - pOther->_posUpperBound._x > TD_OBJECT_EPSILON
					 || _posUpperBound._x - pOther->_posLowerBound._x < TD_OBJECT_EPSILON) ? false : true;
	bool bCollisionY = (_posLowerBound._y - pOther->_posUpperBound._y > TD_OBJECT_EPSILON
					 || _posUpperBound._y - pOther->_posLowerBound._y < TD_OBJECT_EPSILON) ? false : true;
	bool bCollisionZ = (_posLowerBound._z - pOther->_posUpperBound._z > TD_OBJECT_EPSILON
					 || _posUpperBound._z - pOther->_posLowerBound._z < TD_OBJECT_EPSILON) ? false : true;

	if (bCollisionX && bCollisionY && bCollisionZ) return true;
	else return false;
}