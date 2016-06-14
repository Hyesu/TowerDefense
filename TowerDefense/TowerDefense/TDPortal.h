/**
	File: TDPortal.h
		Define constants for portal.

	Shin Hyesu, 2016.06
*/

#ifndef __TD_PORTAL_H__
#define __TD_PORTAL_H__

#include "TDObject.h"

#define PORTAL_COLOR_RED		0
#define PORTAL_COLOR_GREEN		255
#define PORTAL_COLOR_BLUE		0

#define PORTAL_DEFAULT_POS_X	0.0f
#define PORTAL_DEFAULT_POS_Y	0.0f
#define PORTAL_DEFAULT_POS_Z	0.0f

#define PORTAL_LENGTH_X			1.0f
#define PORTAL_LENGTH_Y			3.0f
#define PORTAL_LENGTH_Z			1.0f


/**
	Class: TDPortal
		Represent a "Portal" in tower defense game.
		Inherit TDObject.
*/
class TDPortal : public TDObject {
public:
	TDPortal(float fMapPosX = PORTAL_DEFAULT_POS_X, float fMapPosY = PORTAL_DEFAULT_POS_Y, float fMapPosZ = PORTAL_DEFAULT_POS_Z);
};

#endif