#include "TDGlobal.h"

// init graphic object
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;

const DWORD Vertex::FVF = D3DFVF_XYZ;

IDirect3DVertexBuffer9* g_pVertexBuffer = NULL;
IDirect3DIndexBuffer9* g_pIndexBuffer = NULL;