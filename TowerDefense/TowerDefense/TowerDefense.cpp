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

	_pMap = new TDMap();
	_pPortal = new TDPortal(_pMap->getPosX(), _pMap->getPosY(), _pMap->getPosZ());

	int nLastTileIndex = _pMap->getNumCube() - 1;
	_pMonster = new TDAirMonster(_pMap->getPosX(nLastTileIndex), 
							  _pMap->getPosY(nLastTileIndex), 
							  _pMap->getPosZ(nLastTileIndex));
	_pMonster->setPortalPosition(_pPortal->getPosition());
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

	_pWindow = hWnd;

	return S_OK;
}
VOID TowerDefense::Cleanup() {
	if (_pd3dDevice != nullptr)
		_pd3dDevice->Release();

	if (_pD3D != nullptr)
		_pD3D->Release();

	if (_pVertexBuffer != nullptr)
		_pVertexBuffer->Release();

	if (_pIndexBuffer != nullptr)
		_pIndexBuffer->Release();

	if (_pMap != nullptr)
		delete _pMap;

	if (_pPortal != nullptr)
		delete _pPortal;
}
VOID TowerDefense::Render(float fTimeDelta) {
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
HRESULT TowerDefense::initVertexBuffer(D3DCOLOR color) {
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
	_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	// front face
	pVertices[0] = Vertex(-0.5f, 0.5f, -0.5f, color);
	pVertices[1] = Vertex(0.5f, 0.5f, -0.5f, color);
	pVertices[2] = Vertex(-0.5f, -0.5f, -0.5f, color);
	pVertices[3] = Vertex(0.5f, -0.5f, -0.5f, color);

	// back face
	pVertices[4] = Vertex(-0.5f, 0.5f, 0.5f, color);
	pVertices[5] = Vertex(0.5f, 0.5f, 0.5f, color);
	pVertices[6] = Vertex(-0.5f, -0.5f, 0.5f, color);
	pVertices[7] = Vertex(0.5f, -0.5f, 0.5f, color);

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
	pIndices[30] = 2; pIndices[31] = 3; pIndices[32] = 6;
	pIndices[33] = 6; pIndices[34] = 3; pIndices[35] = 7;

	_pIndexBuffer->Unlock();

	return S_OK;
}
HRESULT TowerDefense::initCamera() {
	// set view space
	D3DXVECTOR3 cameraPosition = TD_CAMERA_POSITION;
	D3DXVECTOR3 targetPosition = TD_TARGET_POSITION;
	D3DXVECTOR3 upVector = TD_WORLD_UP_VECTOR;

	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &cameraPosition, &targetPosition, &upVector);
	_pd3dDevice->SetTransform(D3DTS_VIEW, &viewMatrix);

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

VOID TowerDefense::Finalize() {
	Cleanup();
}

VOID TowerDefense::drawObject(TDObject* pObject) {
	int nRed = pObject->getRed(), nGreen = pObject->getGreen(), nBlue = pObject->getBlue();
	initVertexBuffer(D3DCOLOR_XRGB(nRed, nGreen, nBlue));
	_pd3dDevice->SetStreamSource(0, _pVertexBuffer, 0, sizeof(Vertex));

	D3DXMATRIX worldMatrix;
	for (int i = 0; i < pObject->getNumCube(); i++) {
		D3DXMatrixTranslation(&worldMatrix, pObject->getPosX(i), pObject->getPosY(i), pObject->getPosZ(i));
		_pd3dDevice->SetTransform(D3DTS_WORLD, &worldMatrix);

		_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, TD_NUM_VERTICES, 0, TD_NUM_INDICES / 3);
	}
}
VOID TowerDefense::doTowerDefense() {
	_pMonster->moveToPortal();
	if (_pPortal->collideWith(_pMonster)) {
		MessageBox(0, L"collision!", 0, 0);
		delete _pMonster;
		DestroyWindow(_pWindow);
	}
}