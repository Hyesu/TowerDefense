#ifndef __TOWER_DEFENSE_H__
#define __TOWER_DEFENSE_H__

#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <d3dx9.h>

#include <list>

#include "TDMap.h"
#include "TDPortal.h"
#include "TDAirMonster.h"
#include "TDAirTower.h"
#include "TDMissile.h"

#define DEBUG(X)				MessageBox(0, X, 0, 0)

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
#define TD_BACKGROUND_COLOR		D3DCOLOR_XRGB(255, 255, 255)
#define TD_WINDOW_TITLE			(L"Tower Defense")
#define TD_WINDOW_WIDTH			800
#define TD_WINDOW_HEIGHT		800

#define TD_NUM_VERTICES			8	// cube vertices
#define TD_NUM_INDICES			36	// cube indices

#define TD_CAMERA_POSITION		D3DXVECTOR3(0.0f, 15.0f, -15.0f)
#define TD_TARGET_POSITION		D3DXVECTOR3(0.0f, 0.0f,  0.0f)
#define TD_WORLD_UP_VECTOR		D3DXVECTOR3(0.0f, 1.0f,  0.0f)

#define TD_PROJECTION_ANGLE		D3DX_PI * 0.25f
#define TD_PROJECTION_NEAR		1.0f
#define TD_PROJECTION_FAR		1000.0f

#define TD_CAMERA_ROTATION		0.05f

#define TD_RENDER_INTERVAL		50		// 50 ms interval
#define TD_RENDER_TIMER_ID		1
#define TD_MISSILE_INTERVAL		1500
#define TD_MISSILE_TIMER_ID		2


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
	TDTower* _pTower;

	// Window Variables: window, messages, ...
	HWND _pWindow;
	bool _bRButtonClicked;
	short _nClickPosX;


	// Structures
	struct Vertex {
		Vertex() {}
		Vertex(float x, float y, float z, DWORD color = 0) {
			_x = x, _y = y, _z = z;
			_color = color;
		}

		float _x, _y, _z;
		D3DCOLOR _color; // 32bit color:ARGB
		static const DWORD FVF;
	};
	struct Ray {
		Ray(D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDirection) {
			_vOrigin = vOrigin;
			_vDirection = vDirection;
		}
		D3DXVECTOR3 _vOrigin, _vDirection;
	};


	// Functions 
	VOID init();
	HRESULT initVertexBuffer(const TDObject* pObject);
	HRESULT initIndexBuffer();
	HRESULT initCamera();
	VOID initViewSpace(D3DXVECTOR3 vCameraPosition);
	VOID initTDObjects();

	VOID drawTowerDefense();
	VOID drawObject(const TDObject* pObject);
	VOID doTowerDefense();

	VOID createTower(D3DXVECTOR3 vMapPosition, bool bAirTower = false);

	Ray getPickingRay(int nScreenX, int nScreenY);
	Ray transformRayToWorld(Ray* ray);

	
public:
	TowerDefense();

	static TowerDefense* getInstance() {
		if (_pInstance == nullptr) {
			_pInstance = new TowerDefense();
		}
		return _pInstance;
	}

	HRESULT InitD3D(HWND hWnd);
	VOID Cleanup();
	VOID Render();

	HRESULT SetUp();

	VOID SetRButton(bool bButtonClicked, short nClickPosX);
	VOID SetCamera(short nClickPosX);
	bool GetRButton() const;

	VOID createMissile();
	VOID handlePicking(int nScreenX, int nScreenY);
};


#endif
