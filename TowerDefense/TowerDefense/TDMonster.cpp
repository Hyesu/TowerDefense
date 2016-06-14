/**
	File: TDMonster.cpp
		Define functions of TDMonster class.

	Shin Hyesu, 2016.06
*/

#include "TDMonster.h"

/**
	Function: TDMonster
		Constructor of TDMonster class.
		Init position of monster.

	Params:
		fPosMapEndX		float value for x-position of monster
		fPosMapEndY		float value for y-position of monster
		fPosMapEndZ		float value for z-position of monster
*/
TDMonster::TDMonster(float fPosMapEndX, float fPosMapEndY, float fPosMapEndZ) 
	: TDObject(MONSTER_LENGTH_X, MONSTER_LENGTH_Y, MONSTER_LENGTH_Z, MONSTER_COLOR_RED, MONSTER_COLOR_GREEN, MONSTER_COLOR_BLUE) {
	D3DXVECTOR3 monsterPos = D3DXVECTOR3(fPosMapEndX - MONSTER_LENGTH_X, fPosMapEndY, fPosMapEndZ - MONSTER_LENGTH_Z);
	_vPosition1 = monsterPos;
	_vPosition2 += monsterPos;

	_nType = TYPE_MONSTER;
}

/**
	Function: setPortalPosition
		Setter for portal position used to monster moving target.

	Params:
		vPortal 	position of portal(x, y, z)
*/
void TDMonster::setPortalPosition(D3DXVECTOR3 vPortal) {
	_vPortalPosition = vPortal;
}

/**
	Function: moveToPortal
		move monster to portal.
*/
void TDMonster::moveToPortal() {
	float fDeltaX, fDeltaZ;
	fDeltaX = fDeltaZ = 0;
	
	if (_vPortalPosition.x - getPosition().x > MONSTER_MOVE_THRESHOLD) fDeltaX = MONSTER_MOVE_UNIT;
	else fDeltaX = -MONSTER_MOVE_UNIT;

	if (_vPortalPosition.z - getPosition().z > MONSTER_MOVE_THRESHOLD) fDeltaZ = MONSTER_MOVE_UNIT;
	else fDeltaZ = -MONSTER_MOVE_UNIT;

	_vPosition1.x += fDeltaX;
	_vPosition1.z += fDeltaZ;
	_vPosition2.x += fDeltaX;
	_vPosition2.z += fDeltaZ;
}