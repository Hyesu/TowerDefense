#include "TDGlobal.h"

// init graphic object
LPDIRECT3D9 g_pD3D = nullptr;
LPDIRECT3DDEVICE9 g_pd3dDevice = nullptr;

const DWORD Vertex::FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

IDirect3DVertexBuffer9* g_pVertexBuffer = nullptr;
IDirect3DIndexBuffer9* g_pIndexBuffer = nullptr;