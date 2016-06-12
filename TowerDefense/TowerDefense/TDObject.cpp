#include "TDObject.h"

TDObject::TDObject(float fLengthX, float fLengthY, float fLengthZ, int nRed, int nGreen, int nBlue) {
	_vLowerBound = D3DXVECTOR3(OBJECT_DEFAULT_LOWER_X, OBJECT_DEFAULT_LOWER_Y, OBJECT_DEFAULT_LOWER_Z);
	_vUpperBound = D3DXVECTOR3(_vLowerBound.x + fLengthX, _vLowerBound.y + fLengthY, _vLowerBound.z + fLengthZ);

	_color = D3DCOLOR_XRGB(nRed, nGreen, nBlue);

	_vPosition1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_vPosition2 = D3DXVECTOR3(fLengthX, fLengthY, fLengthZ);

	_bVisible = true;
}
TDObject::~TDObject() {
}

// getter
const D3DCOLOR& TDObject::getColor() const {
	return _color;
}
const D3DXVECTOR3& TDObject::getLowerBound() const {
	return _vLowerBound;
}
const D3DXVECTOR3& TDObject::getUpperBound() const {
	return _vUpperBound;
}
const D3DXVECTOR3& TDObject::getPosition() const {
	return _vPosition1;
}
const D3DXVECTOR3& TDObject::getEndPosition() const {
	return _vPosition2;
}

const float TDObject::getLengthX() const {
	return _vUpperBound.x - _vLowerBound.x;
}
const float TDObject::getLengthY() const {
	return _vUpperBound.y - _vLowerBound.y;
}
const float TDObject::getLengthZ() const {
	return _vUpperBound.z - _vLowerBound.z;
}

bool TDObject::collideWith(const TDObject* pOther) const {
	// check X-axis
	bool bCollisionX = (_vPosition1.x - pOther->_vPosition2.x > TD_OBJECT_EPSILON
					 || _vPosition2.x - pOther->_vPosition1.x < TD_OBJECT_EPSILON) ? false : true;
	bool bCollisionY = (_vPosition1.y - pOther->_vPosition2.y > TD_OBJECT_EPSILON
					 || _vPosition2.y - pOther->_vPosition1.y < TD_OBJECT_EPSILON) ? false : true;
	bool bCollisionZ = (_vPosition1.z - pOther->_vPosition2.z > TD_OBJECT_EPSILON
					 || _vPosition2.z - pOther->_vPosition1.z < TD_OBJECT_EPSILON) ? false : true;

	if (bCollisionX && bCollisionY && bCollisionZ) return true;
	else return false;
}
bool TDObject::isVisible() const {
	return _bVisible;
}

void TDObject::setVisible(bool bVisible) {
	_bVisible = bVisible;
}