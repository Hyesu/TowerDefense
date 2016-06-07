#ifndef __TOWER_DEFENSE_H__
#define __TOWER_DEFENSE_H__

#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <d3dx9.h>

#include "TDMap.h"
#include "TDPortal.h"
#include "TDLandMonster.h"
#include "TDAirMonster.h"

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
#define TD_BACKGROUND_COLOR		D3DCOLOR_XRGB(255, 255, 255)
#define TD_WINDOW_TITLE			(L"Tower Defense")
#define TD_WINDOW_WIDTH			800
#define TD_WINDOW_HEIGHT		600

#define TD_NUM_VERTICES			8	// cube vertices
#define TD_NUM_INDICES			36	// cube indices

#define TD_CAMERA_POSITION		D3DXVECTOR3(0.0f, 5.0f, -10.0f)
#define TD_TARGET_POSITION		D3DXVECTOR3(0.0f, 0.0f,  0.0f)
#define TD_WORLD_UP_VECTOR		D3DXVECTOR3(0.0f, 1.0f,  0.0f)

#define TD_PROJECTION_ANGLE		D3DX_PI * 0.25f
#define TD_PROJECTION_NEAR		1.0f
#define TD_PROJECTION_FAR		1000.0f

#define TD_TIME_CONSTANT		0.001f


// init game and handle direct3D
class TowerDefense
{
private:
	static TowerDefense* _pInstance;
	static const D3DXCOLOR _pColorList[];

	LPDIRECT3D9				_pD3D;			// Used to create the D3DDevice
	LPDIRECT3DDEVICE9		_pd3dDevice;	// Our rendering device
	IDirect3DVertexBuffer9* _pVertexBuffer;
	IDirect3DIndexBuffer9*  _pIndexBuffer;
	D3DXVECTOR3				_vCameraPosition;
	float					_fCameraAngle;

	// Tower Defense Game Variables
	TDMap* _pMap;
	TDPortal* _pPortal;
	TDMonster* _pMonster;

	// Window Variables: window, messages, ...
	HWND _pWindow;
	bool _bRButtonClicked;
	short _nClickPosX;


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
	VOID initViewSpace();

	VOID drawObject(TDObject* pObject);
	VOID doTowerDefense();

	
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
	VOID Render(float fTimeDelta);

	HRESULT SetUp();

	VOID SetRButton(bool bButtonClicked, short nClickPosX);
	VOID SetCamera(short nClickPosX);
};


#endif
