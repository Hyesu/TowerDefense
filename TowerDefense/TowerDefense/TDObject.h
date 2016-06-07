#ifndef __TD_OBJECT_H__
#define __TD_OBJECT_H__

#include <vector>
using namespace std;

#define TD_OBJECT_EPSILON	0.1f

class Position {
public:
	float _x, _y, _z;
	Position() {
		_x = _y = _z = 0.0f;
	}
	Position(float x, float y, float z) {
		_x = x, _y = y, _z = z;
	}
};

class TDObject {
private:
	int _nRed, _nGreen, _nBlue;		// color
	int _nNumCube;					// number of cube


protected:
	vector<Position>* _pPosList;
	Position _posLowerBound, _posUpperBound;

	void init(int nRed, int nGreen, int nBlue,
		float fPosX, float fPosY, float fPosZ, int nNumCube);
	void setBound();

public:
	TDObject();
	~TDObject();

	// getter
	int getRed() const;
	int getGreen() const;
	int getBlue() const;

	int getNumCube() const;

	float getPosX(int nIndex = 0) const;
	float getPosY(int nIndex = 0) const;
	float getPosZ(int nIndex = 0) const;

	Position getPosition(int nIndex = 0) const;

	bool collideWith(const TDObject* pOther) const;
};

#endif