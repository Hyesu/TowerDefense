#ifndef __TD_OBJECT_H__
#define __TD_OBJECT_H__

class TDObject {
private:
	int _nRed, _nGreen, _nBlue;		// color
	float _fPosX, _fPosY, _fPosZ;	// position
	int _nNumCube;					// number of cube

protected:
	void init(int nRed, int nGreen, int nBlue,
		float fPosX, float fPosY, float fPosZ, int nNumCube);

public:
	TDObject();

	// getter
	int getRed() const;
	int getGreen() const;
	int getBlue() const;

	int getNumCube() const;

	float getPosX() const;
	float getPosY() const;
	float getPosZ() const;
};

#endif