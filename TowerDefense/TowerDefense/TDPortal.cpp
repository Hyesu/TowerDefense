#include "TDPortal.h"

TDPortal::TDPortal(float fMapPosX, float fMapPosY, float fMapPosZ) :
	TDObject(PORTAL_LENGTH_X, PORTAL_LENGTH_Y, PORTAL_LENGTH_Z, PORTAL_COLOR_RED, PORTAL_COLOR_GREEN, PORTAL_COLOR_BLUE) {
	D3DXVECTOR3 portalPos = D3DXVECTOR3(fMapPosX, fMapPosY + 1.0f, fMapPosZ);
	_vPosition1 = portalPos;
	_vPosition2 += portalPos;

	_nType = TYPE_PORTAL;
}