#pragma once

#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <d3dx9.h>

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
#define TD_BACKGROUND_COLOR		D3DCOLOR_XRGB(255, 255, 255)
#define TD_WINDOW_TITLE			(L"Tower Defense")
#define TD_WINDOW_WIDTH			640.0f
#define TD_WINDOW_HEIGHT		480.0f

#define TD_NUM_VERTICES			8	// cube vertices
#define TD_NUM_INDICES			36	// cube indices

#define TD_CAMERA_POSITION		D3DXVECTOR3(0.0f, 0.0f, -5.0f)
#define TD_TARGET_POSITION		D3DXVECTOR3(0.0f, 0.0f,  0.0f)
#define TD_WORLD_UP_VECTOR		D3DXVECTOR3(0.0f, 1.0f,  0.0f)

#define TD_PROJECTION_ANGLE		D3DX_PI * 0.5f
#define TD_PROJECTION_NEAR		1.0f
#define TD_PROJECTION_FAR		1000.0f

#define TD_COLOR_TILE			0Xff0000ff




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
	Vertex(float x, float y, float z, DWORD color) {
		_x = x, _y = y, _z = z;

		_w = 1.0f;
		_color = color;
	}

	float _x, _y, _z, _w;
	DWORD _color;
	static const DWORD FVF;
};