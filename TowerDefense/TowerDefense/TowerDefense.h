#ifndef __TOWER_DEFENSE_H__
#define __TOWER_DEFENSE_H__

#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <d3dx9.h>

#include "TDMap.h"

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
#define TD_BACKGROUND_COLOR		D3DCOLOR_XRGB(255, 255, 255)
#define TD_WINDOW_TITLE			(L"Tower Defense")
#define TD_WINDOW_WIDTH			600
#define TD_WINDOW_HEIGHT		600

#define TD_NUM_VERTICES			8	// cube vertices
#define TD_NUM_INDICES			36	// cube indices

#define TD_CAMERA_POSITION		D3DXVECTOR3(5.0f, 5.0f, -5.0f)
#define TD_TARGET_POSITION		D3DXVECTOR3(0.0f, 0.0f,  0.0f)
#define TD_WORLD_UP_VECTOR		D3DXVECTOR3(0.0f, 1.0f,  0.0f)

#define TD_PROJECTION_ANGLE		D3DX_PI * 0.25f
#define TD_PROJECTION_NEAR		1.0f
#define TD_PROJECTION_FAR		1000.0f


// init game and handle direct3D
class TowerDefense
{
private:
	static TowerDefense* _pInstance;
	static const D3DXCOLOR _pColorList[];
	static const enum TD_OBJECT_TYPE {
		TD_OBJECT_TILE = 0,
		TD_OBJECT_PORTAL = 1
	};

	LPDIRECT3D9				_pD3D;			// Used to create the D3DDevice
	LPDIRECT3DDEVICE9		_pd3dDevice;	// Our rendering device
	IDirect3DVertexBuffer9* _pVertexBuffer;
	IDirect3DIndexBuffer9*  _pIndexBuffer;

	TDMap* _pMap;

	struct Vertex {
		Vertex() {}
		Vertex(float x, float y, float z, DWORD color) {
			_x = x, _y = y, _z = z;
			_color = color;
		}

		float _x, _y, _z;
		D3DCOLOR _color; // 32bit color:ARGB
		static const DWORD FVF;
	};


	VOID init();
	HRESULT initVertexBuffer(D3DCOLOR color);
	HRESULT initIndexBuffer();
	HRESULT initCamera();

	VOID drawMap();
	VOID drawPortal();
	
public:
	TowerDefense();

	static TowerDefense* getInstance() {
		if (_pInstance == nullptr) {
			_pInstance = new TowerDefense();
		}
		return _pInstance;
	}
	VOID Finalize();

	HRESULT InitD3D(HWND hWnd);
	VOID Cleanup();
	VOID Render();

	HRESULT SetUp();
};


#endif
