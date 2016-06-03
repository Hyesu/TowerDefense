#pragma once

#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )


//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
#define TD_BACKGROUND_COLOR		D3DCOLOR_XRGB(255, 255, 255)
#define TD_WINDOW_TITLE			(L"Tower Defense")

#define TD_NUM_VERTICES			8	// cube vertices
#define TD_NUM_INDICES			36	// cube indices


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
extern LPDIRECT3D9         g_pD3D; // Used to create the D3DDevice
extern LPDIRECT3DDEVICE9   g_pd3dDevice; // Our rendering device
extern IDirect3DVertexBuffer9* g_pVertexBuffer;
extern IDirect3DIndexBuffer9*  g_pIndexBuffer;



//-----------------------------------------------------------------------------
// Structs
//-----------------------------------------------------------------------------
struct Vertex {
	Vertex() {}
	Vertex(float x, float y, float z) {
		_x = x, _y = y, _z = z;
	}

	float _x, _y, _z;
	static const DWORD FVF;
};