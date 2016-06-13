#include "TowerDefense.h"
TowerDefense* TowerDefense::_pInstance = nullptr;
const DWORD TowerDefense::Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
int TowerDefense::s_nMonsterCreate = 0;

// create and init member variables
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
}


// public direct3D functions
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
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


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
	// release direct3d objects
	if (_pd3dDevice != nullptr)		_pd3dDevice->Release();
	if (_pD3D != nullptr)			_pD3D->Release();
	if (_pVertexBuffer != nullptr)	_pVertexBuffer->Release();
	if (_pIndexBuffer != nullptr)	_pIndexBuffer->Release();

	// delete tower defense objects
	if (_pMap != nullptr)			delete _pMap;
	if (_pPortal != nullptr)		delete _pPortal;
	if (_pMonsterList != nullptr) {
		delete _pMonsterList;
	}
	if (_pTowerList != nullptr) {
		delete _pTowerList;
	}
	if (_pTile != nullptr) delete _pTile;

	// kill timers
	KillTimer(_pWindow, TD_RENDER_TIMER_ID);
	KillTimer(_pWindow, TD_MISSILE_TIMER_ID);
	KillTimer(_pWindow, TD_MONSTER_TIMER_ID);
	KillTimer(_pWindow, TD_GAME_CLEAR_TIMER_ID);
}
VOID TowerDefense::Render() {
	if (NULL == _pd3dDevice)
		return;

	// Clear the backbuffer to a TD_BACKGROUND_COLOR
	_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, TD_BACKGROUND_COLOR, 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(_pd3dDevice->BeginScene())) 	{
		// Rendering of scene objects can happen here
		_pd3dDevice->SetIndices(_pIndexBuffer);
		_pd3dDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

		if (!doTowerDefense()) return;
		drawTowerDefense();

		// End the scene
		_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}


// init direct3D and Game objects
HRESULT TowerDefense::SetUp() {
	// for random number
	srand(static_cast<unsigned int>(time(nullptr)));

	if (FAILED(initIndexBuffer())) {
		MessageBox(0, L"InitIndexBuffer Failed", 0, 0);
		return E_FAIL;
	}

	if (FAILED(initCamera())) {
		MessageBox(0, L"InitCamera Failed", 0, 0);
		return E_FAIL;
	}
	
	initTDObjects();

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
	pIndices[15] = 6; pIndices[16] = 0; pIndices[17] = 2;

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

	// set render state
	_pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	_pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	return S_OK;
}
VOID TowerDefense::initViewSpace(D3DXVECTOR3 vCameraPosition) {
	D3DXVECTOR3 targetPosition = TD_TARGET_POSITION;
	D3DXVECTOR3 upVector = TD_WORLD_UP_VECTOR;

	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &vCameraPosition, &targetPosition, &upVector);
	_pd3dDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
}
VOID TowerDefense::initTDObjects() {
	// init map
	_pMap = new TDMap();


	// init portal
	D3DXVECTOR3 mapPosition = _pMap->getPosition();
	_pPortal = new TDPortal(mapPosition.x, mapPosition.y, mapPosition.z);


	// init monster
	_pMonsterList = new std::list<TDMonster*>();
	createMonster();
	_pMap->setPortalAndMonster(_pPortal->getPosition(), ((TDMonster*) (*_pMonsterList->begin()))->getPosition());
	SetTimer(_pWindow, TD_MONSTER_TIMER_ID, TD_MONSTER_INTERVAL, nullptr);

	_pTowerList = new std::vector<TDTower*>();

	_pTile = new TDTile();

	// set timer
	SetTimer(_pWindow, TD_RENDER_TIMER_ID, TD_RENDER_INTERVAL, nullptr);
	SetTimer(_pWindow, TD_MISSILE_TIMER_ID, TD_MISSILE_INTERVAL, nullptr);
}


// draw game object functions
VOID TowerDefense::drawTowerDefense() {
	drawObject(_pMap);
	drawObject(_pPortal);

	// draw monsters
	for (std::list<TDMonster*>::iterator it = _pMonsterList->begin(); it != _pMonsterList->end(); ++it) {
		drawObject(*it);
	}

	// draw tower and missiles
	for (int i = 0; i < _pTowerList->size(); i++) {
		TDTower* tower = _pTowerList->at(i);

		drawObject(tower);

		std::list<TDMissile*>* pMissileList = tower->getMissileList();
		if (pMissileList->empty()) continue;
		for (std::list<TDMissile*>::iterator it = pMissileList->begin(); it != pMissileList->end(); ++it) {
			drawObject((TDMissile*)(*it));
		}
	}

	drawObject(_pTile);
}
VOID TowerDefense::drawObject(const TDObject* pObject) {
	if (pObject == nullptr || !pObject->isVisible()) return;

	initVertexBuffer(pObject);
	_pd3dDevice->SetStreamSource(0, _pVertexBuffer, 0, sizeof(Vertex));

	D3DXMATRIX worldMatrix;
	D3DXVECTOR3 position = pObject->getPosition();
	D3DXMatrixTranslation(&worldMatrix, position.x, position.y, position.z);
	_pd3dDevice->SetTransform(D3DTS_WORLD, &worldMatrix);

	_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, TD_NUM_VERTICES, 0, TD_NUM_INDICES / 3);

}


// game logic functions
bool TowerDefense::doTowerDefense() {
	// move missile
	for (unsigned int i = 0; i < _pTowerList->size(); i++) {
		TDTower* tower = _pTowerList->at(i);
		tower->moveMissile();
	}

	// move monsters
	for (std::list<TDMonster*>::iterator it = _pMonsterList->begin(); it != _pMonsterList->end(); ) {
		TDMonster* pMonster = (TDMonster*)(*it);
		pMonster->moveToPortal();

		// check collision with portal
		if (_pPortal != nullptr && _pPortal->collideWith(pMonster)) {
			handleGameOver();
			return false;
		}

		bool bMonsterKillCondition = false;
		// check collistion with missile
		for (unsigned int i = 0; i < _pTowerList->size(); i++) {
			TDTower* tower = _pTowerList->at(i);

			if (tower->handleCollideWith(pMonster)) {
				delete pMonster;
				it = _pMonsterList->erase(it);
				bMonsterKillCondition = true;
				break;
			}

			for (unsigned int j = 0; j < _pTowerList->size(); j++) {
				TDTower* otherTower = _pTowerList->at(j);
				if (tower == otherTower) continue;
				tower->handleCollideWith(otherTower);
			}
		}			
		if (!bMonsterKillCondition)
			++it;
	}
	return true;
}


// camera rotation functions by mouse right-button click
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


// create game objects 
TDTower* TowerDefense::createTower(D3DXVECTOR3 vMapPosition, bool bAirTower) {
	TDTower* newTower = nullptr;
	if (bAirTower)
		newTower = new TDAirTower(vMapPosition, _pMap->getPosition(), _pMap->getEndPosition());
	else
		newTower = new TDTower(vMapPosition, _pMap->getPosition(), _pMap->getEndPosition());

	_pTowerList->push_back(newTower);
	return newTower;

}
VOID TowerDefense::createMissile() {
	for (int i = 0; i < _pTowerList->size(); i++)
		_pTowerList->at(i)->createMissile();
}
VOID TowerDefense::createMonster() {
	if (_pMap == nullptr || _pPortal == nullptr || _pMonsterList == nullptr) return;

	int nMonsterType = rand() % MONSTER_NUM_TYPE;

	D3DXVECTOR3 mapPosition = _pMap->getEndPosition();
	s_nMonsterCreate++;
	switch (nMonsterType) {
	case TDMonster::MONSTER_LAND:
		_pMonsterList->push_front(new TDMonster(mapPosition.x, mapPosition.y, mapPosition.z));
		break;
	case TDMonster::MONSTER_AIR:
		_pMonsterList->push_front(new TDAirMonster(mapPosition.x, mapPosition.y, mapPosition.z));
		break;
	default:
		MessageBox(0, L"not supported type of monster", 0, 0);
		break;
	}
	(*(_pMonsterList->begin()))->setPortalPosition(_pPortal->getPosition());

	if (s_nMonsterCreate >= TD_MAX_MONSTER) {
		KillTimer(_pWindow, TD_MONSTER_TIMER_ID);
		SetTimer(_pWindow, TD_GAME_CLEAR_TIMER_ID, TD_GAME_CLEAR_INTERVAL, nullptr);
	}
}


// event handler functions
VOID TowerDefense::handleGameOver() {
	MessageBox(0, L"GAME OVER!", L"GAME OVER", 0);
	DestroyWindow(_pWindow);
}
VOID TowerDefense::handleGameClear() {
	if (!_pMonsterList->empty()) return;

	KillTimer(_pWindow, TD_GAME_CLEAR_TIMER_ID);
	KillTimer(_pWindow, TD_RENDER_TIMER_ID);

	MessageBox(0, L"GAME CLEAR!", L"GAME CLEAR", 0);
	DestroyWindow(_pWindow);
}
VOID TowerDefense::handleMouseHover(int nScreenX, int nScreenY) {
	Ray ray = getPickingRay(nScreenX, nScreenY);
	transformRayToWorld(&ray);

	D3DXVECTOR3 mapPosition = _pMap->getPosition();
	for (int i = 0; i < _pMap->getRow(); i++) {
		for (int j = 0; j < _pMap->getCol(); j++) {
			D3DXVECTOR3 lowerBound = mapPosition + D3DXVECTOR3(1.0f * j, 0.0f, 1.0f * i);
			D3DXVECTOR3 upperBound = mapPosition + D3DXVECTOR3(1.0f * (j + 1), 1.0f, 1.0f * (i + 1));

			if (D3DXBoxBoundProbe(&lowerBound, &upperBound, &ray._vOrigin, &ray._vDirection)) {
				_pTile->setVisible(true);
				_pTile->setPosition(D3DXVECTOR3(lowerBound.x, upperBound.y, lowerBound.z));
				_nMouseRow = i;
				_nMouseCol = j;

				if (_pMap->isAvailableTile(_nMouseRow, _nMouseCol))
					_pTile->setColor(TILE_COLOR_RED, TILE_COLOR_GREEN, TILE_COLOR_BLUE);
				else
					_pTile->setColor(TILE_COLOR_RED_UNAVAIL, TILE_COLOR_GREEN_UNAVAIL, TILE_COLOR_BLUE_UNAVAIL);

				return;
			}
		}
	}
	_pTile->setVisible(false);
	_nMouseRow = -1;
	_nMouseCol = -1;
}
VOID TowerDefense::handleMouseClick() {
	if (_nMouseRow < 0 || _nMouseCol < 0) return;

	if (_pMap->isAvailableTile(_nMouseRow, _nMouseCol)) {
		// click empty tile case
		D3DXVECTOR3 clickedTilePosition = _pMap->getPosition() + D3DXVECTOR3(1.0f * _nMouseCol, 0.0f, 1.0f * _nMouseRow);
		_pMap->setAvailable(_nMouseRow, _nMouseCol, 
			createTower(clickedTilePosition, GetAsyncKeyState(VK_LSHIFT) & 0x8000 ? true : false));
	}
	else {
		// click tower case
		TDObject* clickedObject = _pMap->getObjectOn(_nMouseRow, _nMouseCol);
		if(clickedObject->getType() == TDObject::TYPE_TOWER)
			((TDTower*)clickedObject)->changeMissileDirection();
	}
}


// functions for picking
TowerDefense::Ray TowerDefense::getPickingRay(int nScreenX, int nScreenY) {
	D3DVIEWPORT9 viewport;
	_pd3dDevice->GetViewport(&viewport);

	D3DXMATRIX projection;
	_pd3dDevice->GetTransform(D3DTS_PROJECTION, &projection);

	float px = (((2.0f * nScreenX) / viewport.Width) - 1.0f) / projection(0, 0);
	float py = (((-2.0f * nScreenY) / viewport.Height) + 1.0f) / projection(1, 1);

	return Ray(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(px, py, 1.0f));
}
TowerDefense::Ray TowerDefense::transformRayToWorld(Ray* ray) {
	// get inverse of view matrix
	D3DXMATRIX view;
	_pd3dDevice->GetTransform(D3DTS_VIEW, &view);
	D3DXMATRIX viewInverse;
	D3DXMatrixInverse(&viewInverse, 0, &view);

	// transform ray from view space to world space
	D3DXVec3TransformCoord(&ray->_vOrigin, &ray->_vOrigin, &viewInverse);
	D3DXVec3TransformNormal(&ray->_vDirection, &ray->_vDirection, &viewInverse);

	return Ray(ray->_vOrigin, ray->_vDirection);
}
