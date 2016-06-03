#include "TDObject.h"

TDObject::TDObject() {
	initVertices();
	initIndices();
}
void TDObject::initVertices() {
	g_pVertexBuffer->Lock(0, 0, (void**)&_pVertices, 0);

	// unit cube vertices
	_pVertices[0] = Vertex(-1.0f, -1.0f, -1.0f, TD_COLOR_TILE);
	_pVertices[1] = Vertex(-1.0f, 1.0f, -1.0f, TD_COLOR_TILE);
	_pVertices[2] = Vertex(1.0f, 1.0f, -1.0f, TD_COLOR_TILE);
	_pVertices[3] = Vertex(1.0f, -1.0f, -1.0f, TD_COLOR_TILE);
	_pVertices[4] = Vertex(-1.0f, -1.0f, 1.0f, TD_COLOR_TILE);
	_pVertices[5] = Vertex(-1.0f, 1.0f, 1.0f, TD_COLOR_TILE);
	_pVertices[6] = Vertex(1.0f, 1.0f, 1.0f, TD_COLOR_TILE);
	_pVertices[7] = Vertex(1.0f, -1.0f, 1.0f, TD_COLOR_TILE);

	g_pVertexBuffer->Unlock();
}
void TDObject::initIndices() {
	g_pIndexBuffer->Lock(0, 0, (void**)&_pIndices, 0);

	// unit cube plane
	// front side
	_pIndices[0] = 0; _pIndices[1] = 1; _pIndices[2] = 2;
	_pIndices[3] = 0; _pIndices[4] = 2; _pIndices[5] = 3;

	// back side
	_pIndices[6] = 4; _pIndices[7] = 6; _pIndices[8] = 5;
	_pIndices[9] = 4; _pIndices[10] = 7; _pIndices[11] = 6;

	// left side
	_pIndices[12] = 4; _pIndices[13] = 5; _pIndices[14] = 1;
	_pIndices[15] = 4; _pIndices[16] = 1; _pIndices[17] = 0;

	// right side
	_pIndices[18] = 3; _pIndices[19] = 2; _pIndices[20] = 6;
	_pIndices[21] = 3; _pIndices[22] = 6; _pIndices[23] = 7;

	// top
	_pIndices[24] = 1; _pIndices[25] = 5; _pIndices[26] = 6;
	_pIndices[27] = 1; _pIndices[28] = 6; _pIndices[29] = 2;

	// bottom
	_pIndices[30] = 4; _pIndices[31] = 0; _pIndices[32] = 3;
	_pIndices[33] = 4; _pIndices[34] = 3; _pIndices[35] = 7;

	g_pIndexBuffer->Unlock();
}