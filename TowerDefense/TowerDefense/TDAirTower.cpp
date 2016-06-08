#include "TDAirTower.h"

TDAirTower::TDAirTower(float fMapPosX, float fMapPosY, float fMapPosZ) 
	: TDTower(fMapPosX, fMapPosY, fMapPosZ) {
	_vUpperBound.y += 1.0f;
	_vPosition2.y += 1.0f;
}