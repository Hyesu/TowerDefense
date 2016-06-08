#include "TowerDefense.h"
TowerDefense* TowerDefense::_pInstance = nullptr;
const DWORD TowerDefense::Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

TowerDefense::TowerDefense() {
	init();
}
VOID TowerDefense::init() {
	_pD3D = nullptr;
	_pd3dDevice = nullptr;
	_pVertexBuffer = nullptr;
	_pIndexBuffer = nullptr;

	_bRButtonClicked = false;

	_vCameraPosition = TD_CAMERA_POSITION;
	_fCameraAngle = 0.0f;

	// TD Objects init
	_pMap = new TDMap();

	D3DXVECTOR3 mapPosition = _pMap->getPosition();
	_pPortal = new TDPortal(mapPosition.x, mapPosition.y, mapPosition.z);

	D3DXVECTOR3 mapPosition2 = _pMap->getEndPosition();
	_pMonster = new TDAirMonster(mapPosition2.x, mapPosition2.y, mapPosition2.z);
	_pMonster->setPortalPosition(_pPortal->getPosition());

	// tower create should be changed later(by L button click event handler)
	D3DXVECTOR3 tempMapPosition = mapPosition + D3DXVECTOR3(_pMap->getLengthX() * 0.3f, 0, _pMap->getLengthZ() * 0.7f);
	_pTower = new TDAirTower(tempMapPosition.x, tempMapPosition.y, tempMapPosition.z);
}

HRESULT TowerDefense::InitD3D(HWND hWnd) {
	// Create the D3D object, which is needed to create the D3DDevice.
	if (NULL == (_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = TD_WINDOW_WIDTH;
	d3dpp.BackBufferHeight = TD_WINDOW_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// check device capability for hardware vertex processing
	D3DCAPS9 caps;
	_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	int nVertexProcessingType;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		nVertexProcessingType = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		nVertexProcessingType = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// Create the Direct3D device.
	if (FAILED(_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		nVertexProcessingType,
		&d3dpp, &_pd3dDevice)))	{
		return E_FAIL;
	}

	// set render interval
	_pWindow = hWnd;
	SetTimer(_pWindow, TD_RENDER_TIMER_ID, TD_RENDER_INTERVAL, nullptr);

	return S_OK;
}
VOID TowerDefense::Cleanup() {
	// release direct3d objects
	if (_pd3dDevice != nullptr)		_pd3dDevice->Release();
	if (_pD3D != nullptr)			_pD3D->Release();
	if (_pVertexBuffer != nullptr)	_pVertexBuffer->Release();
	if (_pIndexBuffer != nullptr)	_pIndexBuffer->Release();

	// delete tower defense objects
	if (_pMap != nullptr)			delete _pMap;
	if (_pPortal != nullptr)		delete _pPortal;
	if (_pMonster != nullptr)		delete _pMonster;
	if (_pTower != nullptr)			delete _pTower;

	KillTimer(_pWindow, TD_RENDER_TIMER_ID);
}
VOID TowerDefense::Render() {
	if (NULL == _pd3dDevice)
		return;

	// Clear the backbuffer to a TD_BACKGROUND_COLOR
	_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, TD_BACKGROUND_COLOR, 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(_pd3dDevice->BeginScene())) 	{
		// Rendering of scene objects can happen here
		_pd3dDevice->SetIndices(_pIndexBuffer);
		_pd3dDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

		// do game logic
		doTowerDefense();

		// draw objects in game
		drawObject(_pMap);
		drawObject(_pTower);
		drawObject(_pPortal);
		drawObject(_pMonster);

		// End the scene
		_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

HRESULT TowerDefense::SetUp() {
	if (FAILED(initIndexBuffer())) {
		MessageBox(0, L"InitIndexBuffer Failed", 0, 0);
		return E_FAIL;
	}

	if (FAILED(initCamera())) {
		MessageBox(0, L"InitCamera Failed", 0, 0);
		return E_FAIL;
	}
	return S_OK;
}
HRESULT TowerDefense::initVertexBuffer(const TDObject* pObject) {
	// create vertex buffer
	if (FAILED(_pd3dDevice->CreateVertexBuffer(
		TD_NUM_VERTICES * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&_pVertexBuffer,
		0)))
		return E_FAIL;

	// set vertex buffer
	Vertex* pVertices;
	D3DCOLOR color = pObject->getColor();
	D3DXVECTOR3 lb = pObject->getLowerBound(), ub = pObject->getUpperBound();
	_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	// front face
	pVertices[0] = Vertex(lb.x, ub.y, lb.z, color);
	pVertices[1] = Vertex(ub.x, ub.y, lb.z, color);
	pVertices[2] = Vertex(lb.x, lb.y, lb.z, color);
	pVertices[3] = Vertex(ub.x, lb.y, lb.z, color);

	// back face
	pVertices[4] = Vertex(lb.x, ub.y, ub.z, color);
	pVertices[5] = Vertex(ub.x, ub.y, ub.z, color);
	pVertices[6] = Vertex(lb.x, lb.y, ub.z, color);
	pVertices[7] = Vertex(ub.x, lb.y, ub.z, color);

	_pVertexBuffer->Unlock();

	return S_OK;
}
HRESULT TowerDefense::initIndexBuffer() {
	// create index buffer
	if (FAILED(_pd3dDevice->CreateIndexBuffer(
		TD_NUM_INDICES * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_pIndexBuffer,
		0)))
		return E_FAIL;

	// Set indices
	WORD* pIndices;
	_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	// front side
	pIndices[0] = 0; pIndices[1] = 1; pIndices[2] = 2;
	pIndices[3] = 2; pIndices[4] = 1; pIndices[5] = 3;

	// back side
	pIndices[6] = 5; pIndices[7] = 4; pIndices[8] = 7;
	pIndices[9] = 7; pIndices[10] = 4; pIndices[11] = 6;

	// left side
	pIndices[12] = 4; pIndices[13] = 0; pIndices[14] = 6;
	pIndices[15] = 6; pIndices[16] = 0; pIndices[17] = 3;

	// right side
	pIndices[18] = 1; pIndices[19] = 5; pIndices[20] = 3;
	pIndices[21] = 3; pIndices[22] = 5; pIndices[23] = 7;

	// top
	pIndices[24] = 4; pIndices[25] = 5; pIndices[26] = 0;
	pIndices[27] = 0; pIndices[28] = 5; pIndices[29] = 1;

	// bottom
	pIndices[30] = 6; pIndices[31] = 7; pIndices[32] = 2;
	pIndices[33] = 2; pIndices[34] = 7; pIndices[35] = 3;

	_pIndexBuffer->Unlock();

	return S_OK;
}
HRESULT TowerDefense::initCamera() {
	initViewSpace(TD_CAMERA_POSITION);

	// set projection
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix,
		TD_PROJECTION_ANGLE,
		(float)TD_WINDOW_WIDTH / (float)TD_WINDOW_HEIGHT,
		TD_PROJECTION_NEAR,
		TD_PROJECTION_FAR);
	_pd3dDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
	_pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);

	return S_OK;
}
VOID TowerDefense::initViewSpace(D3DXVECTOR3 vCameraPosition) {
	D3DXVECTOR3 targetPosition = TD_TARGET_POSITION;
	D3DXVECTOR3 upVector = TD_WORLD_UP_VECTOR;

	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &vCameraPosition, &targetPosition, &upVector);
	_pd3dDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
}

VOID TowerDefense::drawObject(const TDObject* pObject) {
	initVertexBuffer(pObject);
	_pd3dDevice->SetStreamSource(0, _pVertexBuffer, 0, sizeof(Vertex));

	D3DXMATRIX worldMatrix;
	D3DXVECTOR3 position = pObject->getPosition();
	D3DXMatrixTranslation(&worldMatrix, position.x, position.y, position.z);
	_pd3dDevice->SetTransform(D3DTS_WORLD, &worldMatrix);

	_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, TD_NUM_VERTICES, 0, TD_NUM_INDICES / 3);

}
VOID TowerDefense::doTowerDefense() {
	_pMonster->moveToPortal();
	if (_pPortal->collideWith(_pMonster)) {
		MessageBox(0, L"collision!", 0, 0);
		delete _pMonster;
		_pMonster = nullptr;
		DestroyWindow(_pWindow);
	}
}

VOID TowerDefense::SetRButton(bool bButtonClicked, short nClickPosX) {
	_bRButtonClicked = bButtonClicked;
	_nClickPosX = nClickPosX;
}
VOID TowerDefense::SetCamera(short nClickPosX) {
	if (!_bRButtonClicked) return;

	D3DXMATRIX rotationMatrix;
	if (nClickPosX > _nClickPosX) {
		_fCameraAngle += TD_CAMERA_ROTATION;
	}
	else if(nClickPosX < _nClickPosX) {
		_fCameraAngle -= TD_CAMERA_ROTATION;
	}
	D3DXMatrixRotationY(&rotationMatrix, _fCameraAngle);
	D3DXVECTOR3 rotatedPosition;
	D3DXVec3TransformNormal(&rotatedPosition, &TD_CAMERA_POSITION, &rotationMatrix);
	initViewSpace(rotatedPosition);
	_nClickPosX = nClickPosX;
}
bool TowerDefense::GetRButton() const {
	return _bRButtonClicked;
}