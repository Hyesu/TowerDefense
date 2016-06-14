/**
	File: TDObject.cpp
		Define functions of TDObject class.

	Shin Hyesu, 2016.06
*/

#include "TDObject.h"


/**
	Function: TDObject
		Constructor of TDObject class.
		Init lower bound and upper bound of object, used to define vertex in local space.
		Init color of vertex.
		Init position of object, used to define position in world space.

	Params:
		fLengthX	float value for x-length of object
		fLengthY	float value for y-length of object
		fLengthZ	float value for z-length of object
		nRed		integer value for red color of object
		nGreen		integer value for green color of object
		nBlue		integer value for blue color of object
*/
TDObject::TDObject(float fLengthX, float fLengthY, float fLengthZ, int nRed, int nGreen, int nBlue) {
	_vLowerBound = D3DXVECTOR3(OBJECT_DEFAULT_LOWER_X, OBJECT_DEFAULT_LOWER_Y, OBJECT_DEFAULT_LOWER_Z);
	_vUpperBound = D3DXVECTOR3(_vLowerBound.x + fLengthX, _vLowerBound.y + fLengthY, _vLowerBound.z + fLengthZ);

	_color = D3DCOLOR_XRGB(nRed, nGreen, nBlue);

	_vPosition1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_vPosition2 = D3DXVECTOR3(fLengthX, fLengthY, fLengthZ);

	_bVisible = true;

	_nType = TYPE_OBJECT;
}
TDObject::~TDObject() {
}


/**
	Function: getColor
		Getter for color of object

	Return:
		color value of object (a, r, g, b)
*/
const D3DCOLOR& TDObject::getColor() const {
	return _color;
}
/**
	Function: getType
		Getter for type of object

	Return:
		integer value for type of object
*/
const int TDObject::getType() const {
	return _nType;
}
/**
	Function: getLowerBound
		Getter for lower bound of object in local space

	Return:
		vector value for lower bound of object (x, y, z)
*/
const D3DXVECTOR3& TDObject::getLowerBound() const {
	return _vLowerBound;
}
/**
	Function: getUpperBound
		Getter for upper bound of object in local space

	Return:
		vector value for upper bound of object (x, y, z)
*/
const D3DXVECTOR3& TDObject::getUpperBound() const {
	return _vUpperBound;
}
/**
	Function: getPosition
		Getter for lower position(minimum x/y/z-axis value) of object in world space

	Return:
		vector value for lower position of object (x, y, z)
*/
const D3DXVECTOR3& TDObject::getPosition() const {
	return _vPosition1;
}
/**
	Function: getEndPosition
		Getter for upper position(maximum x/y/z-axis value) of object in world space

	Return:
		vector value for upper position of object (x, y, z)
*/
const D3DXVECTOR3& TDObject::getEndPosition() const {
	return _vPosition2;
}
/**
	Function: getLengthX
		Getter for x-length of object

	Return:
		float value of x-length of object
*/
const float TDObject::getLengthX() const {
	return _vUpperBound.x - _vLowerBound.x;
}
/**
	Function: getLengthY
		Getter for y-length of object

	Return:
		float value of y-length of object
*/
const float TDObject::getLengthY() const {
	return _vUpperBound.y - _vLowerBound.y;
}
/**
	Function: getLengthZ
		Getter for z-length of object

	Return:
		float value of z-length of object
*/
const float TDObject::getLengthZ() const {
	return _vUpperBound.z - _vLowerBound.z;
}
/**
	Function: isVisible
		Getter for visible status of object

	Return:
		boolean value for visible status
*/
bool TDObject::isVisible() const {
	return _bVisible;
}


/**
	Function: collideWith
		Check whether collision occurs between this object and other object.

	Params:
		pOther	target object for checking collision
	Return:
		boolean value for result
*/
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

/**
	Function: setVisible
		Setter for visible status of object

	Params:
		bVisible 	boolean value for setting
*/
void TDObject::setVisible(bool bVisible) {
	_bVisible = bVisible;
}
/**
	Function: setColor
		Setter for color of object

	Params:
		nRed		integer value for object red color
		nGreen		integer value for object green color
		nBlue		integer value for object blue color
*/
void TDObject::setColor(int nRed, int nGreen, int nBlue) {
	_color = D3DCOLOR_XRGB(nRed, nGreen, nBlue);
}