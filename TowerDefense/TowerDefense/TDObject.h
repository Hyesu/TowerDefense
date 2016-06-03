#ifndef __TD_OBJECT_H__
#define __TD_OBJECT_H__

#include "TDGlobal.h"

// TDObject is an unit cube
class TDObject 
{
private:
	Vertex* _pVertices;
	WORD* _pIndices;

	void initVertices();
	void initIndices();

public:
	TDObject();
};

#endif