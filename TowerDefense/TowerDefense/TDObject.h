/**
	File: TDObject.h
		Define constants and class for data clas of tower defense game.

	Shin Hyesu, 2016.06
*/

#ifndef __TD_OBJECT_H__
#define __TD_OBJECT_H__

#include <d3d9.h>
#include <d3dx9.h>

#define TD_OBJECT_EPSILON		0.1f

#define OBJECT_DEFAULT_RED		0
#define OBJECT_DEFAULT_BLUE		0
#define OBJECT_DEFAULT_GREEN	0

#define OBJECT_DEFAULT_LOWER_X	-0.5f
#define OBJECT_DEFAULT_LOWER_Y	-0.5f
#define OBJECT_DEFAULT_LOWER_Z	-0.5f

#define OBJECT_DEFAULT_LENGTH	1.0f


/**
	Class: TDObject
		TDObject is the root of the Tower Defense Data class hierarchy.
		Every data class has TDObject as a superclass.
*/
class TDObject {
private:
	D3DCOLOR	_color;			// vertex color
	bool		_bVisible;		// boolean value whether the object will be draw or not

protected:
	D3DXVECTOR3 _vLowerBound, _vUpperBound;		// used to define vertex of object at local space
	D3DXVECTOR3 _vPosition1, _vPosition2;		// used to define position of object at world space
	int			_nType;							// define object type. value is one of OBJECT_TYPE enumerator

public:
	TDObject(float fLengthX = OBJECT_DEFAULT_LENGTH, float fLengthY = OBJECT_DEFAULT_LENGTH, float fLengthZ = OBJECT_DEFAULT_LENGTH,
		int nRed = OBJECT_DEFAULT_RED, int nGreen = OBJECT_DEFAULT_GREEN, int nBlue = OBJECT_DEFAULT_BLUE);
	virtual ~TDObject();


	// getter
	const D3DCOLOR& getColor() const;
	const int getType() const;

	const D3DXVECTOR3& getLowerBound() const;
	const D3DXVECTOR3& getUpperBound() const;
	const D3DXVECTOR3& getPosition() const;
	const D3DXVECTOR3& getEndPosition() const;

	const float getLengthX() const;
	const float getLengthY() const;
	const float getLengthZ() const;


	// setter
	void setVisible(bool bVisible);
	void setColor(int nRed, int nGreen, int nBlue);


	// other functions
	bool collideWith(const TDObject* pOther) const;
	bool isVisible() const;


	enum OBJECT_TYPE {TYPE_OBJECT, TYPE_MAP, TYPE_PORTAL, TYPE_MONSTER, TYPE_TOWER, TYPE_MISSILE, TYPE_TILE};
};

#endif