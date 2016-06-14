/**
	File: TDTower.h
		Define constants and class for representing tower in tower defense game.

	Shin Hyesu, 2016.06
*/

#ifndef __TD_TOWER_H__
#define __TD_TOWER_H__

#include <list>
#include "TDObject.h"
#include "TDMissile.h"

#define TOWER_DEFAULT_POS_X	0.0f
#define TOWER_DEFAULT_POS_Y	0.0f
#define TOWER_DEFAULT_POS_Z	0.0f

#define TOWER_COLOR_RED		0
#define TOWER_COLOR_GREEN	0
#define TOWER_COLOR_BLUE	255

#define TOWER_LENGTH		1.0f

#define TOWER_BOUNDARY		3.0f



/**
	Class: TDTower
		Represent a "Tower" in tower defense game.
		Create and manage missiles. Check collision between missiles and other objects.
		Inherit TDObject.
*/
class TDTower : public TDObject {
private:
	std::list<TDMissile*>* 	_pMissileList; 							// list of missile created by this tower
	D3DXVECTOR3 			_vMissileBoundary1, _vMissileBoundary2;	// valid boundary for missile moving

	unsigned int _nMissileDirectionIndex;							// missile direction index, used for s_vMissileDirection


public:
	TDTower(D3DXVECTOR3 vTowerPosition, D3DXVECTOR3 vMapPosition1, D3DXVECTOR3 vMapPosition2);
	~TDTower();

	void createMissile();
	void moveMissile();
	bool handleCollideWith(const TDObject* pObject);
	void changeMissileDirection();

	// getter
	std::list<TDMissile*>* getMissileList() const;


	const static D3DXVECTOR3 s_vMissileDirection[];					// missile direction array
};

#endif
