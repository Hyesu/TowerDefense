#include "TDAirMonster.h"

TDAirMonster::TDAirMonster(float fPosMapEndX, float fPosMapEndY, float fPosMapEndZ)
	: TDMonster(fPosMapEndX, fPosMapEndY, fPosMapEndZ) {
	_vPosition1.y += 1.0f;
	_vPosition2.y += 1.0f;
}