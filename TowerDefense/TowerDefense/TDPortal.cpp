/**
	File: TDPortal.cpp
		Define functions of TDPortal class.

	Shin Hyesu, 2016.06
*/

#include "TDPortal.h"

/**
	Function: TDPortal
		Constructor of TDPortal class.
		Init position of portal.

	Params:
		fMapPosX	float value of x position of map for creating portal
		fMapPosY	float value of y position of map for creating portal
		fMapPosZ	float value of z position of map for creating portal
*/
TDPortal::TDPortal(float fMapPosX, float fMapPosY, float fMapPosZ) :
	TDObject(PORTAL_LENGTH_X, PORTAL_LENGTH_Y, PORTAL_LENGTH_Z, PORTAL_COLOR_RED, PORTAL_COLOR_GREEN, PORTAL_COLOR_BLUE) {
	D3DXVECTOR3 portalPos = D3DXVECTOR3(fMapPosX, fMapPosY + OBJECT_DEFAULT_LENGTH, fMapPosZ);
	_vPosition1 = portalPos;
	_vPosition2 += portalPos;

	_nType = TYPE_PORTAL;
}