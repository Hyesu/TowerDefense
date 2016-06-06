#ifndef __TD_PORTAL_H__
#define __TD_PORTAL_H__

#include "TDObject.h"

#define PORTAL_COLOR_RED	0
#define PORTAL_COLOR_GREEN	255
#define PORTAL_COLOR_BLUE	0

#define PORTAL_NUM_CUBE		2

class TDPortal : public TDObject {
private:
	void initPosition();

public:
	TDPortal(float fPosX = 0.0f, float fPosY = 0.0f, float fPosZ = 0.0f);
};

#endif