#include "TDGlobal.h"

/***
*	Global Variables and Static Variables
***/
LPDIRECT3D9 TD::g_pD3D = nullptr;
LPDIRECT3DDEVICE9 TD::g_pd3dDevice = nullptr;

IDirect3DVertexBuffer9* TD::g_pVertexBuffer = nullptr;
IDirect3DIndexBuffer9* TD::g_pIndexBuffer = nullptr;

const DWORD TD::Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

/***
*	Global Functions
***/

HRESULT TD::InitD3D(HWND hWnd)
{
	// Create the D3D object, which is needed to create the D3DDevice.
	if (NULL == (TD::g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
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
	TD::g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	int nVertexProcessingType;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		nVertexProcessingType = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		nVertexProcessingType = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// Create the Direct3D device.
	if (FAILED(TD::g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		nVertexProcessingType,
		&d3dpp, &TD::g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// Device state would normally be set here

	return S_OK;
}
VOID TD::Cleanup()
{
	if (TD::g_pd3dDevice != nullptr)
		TD::g_pd3dDevice->Release();

	if (TD::g_pD3D != nullptr)
		TD::g_pD3D->Release();

	if (TD::g_pVertexBuffer != nullptr)
		TD::g_pVertexBuffer->Release();

	if (TD::g_pIndexBuffer != nullptr)
		TD::g_pIndexBuffer->Release();
}
VOID TD::Render()
{
	if (NULL == TD::g_pd3dDevice)
		return;

	// Clear the backbuffer to a TD_BACKGROUND_COLOR
	TD::g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, TD_BACKGROUND_COLOR, 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(TD::g_pd3dDevice->BeginScene()))
	{
		// Rendering of scene objects can happen here
		g_pd3dDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex));
		g_pd3dDevice->SetIndices(g_pIndexBuffer);
		g_pd3dDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, TD_NUM_VERTICES, 0, TD_NUM_INDICES / 3);

		// End the scene
		TD::g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	TD::g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
LRESULT WINAPI TD::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		Render();
		ValidateRect(hWnd, NULL);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

HRESULT TD::SetUp() 
{
	if (FAILED(TD::InitVertexBuffer())) {
		MessageBox(0, L"InitVertexBuffer Failed", 0, 0);
		return E_FAIL;
	}
	if (FAILED(InitIndexBuffer())) {
		MessageBox(0, L"InitIndexBuffer Failed", 0, 0);
		return E_FAIL;
	}

	if (FAILED(InitCamera())) {
		MessageBox(0, L"InitCamera Failed", 0, 0);
		return E_FAIL;
	}
	return S_OK;
}
HRESULT TD::InitVertexBuffer()
{
	// create vertex buffer
	if (FAILED(TD::g_pd3dDevice->CreateVertexBuffer(
		TD_NUM_VERTICES * sizeof(TD::Vertex),
		D3DUSAGE_WRITEONLY,
		TD::Vertex::FVF,
		D3DPOOL_MANAGED,
		&TD::g_pVertexBuffer,
		0)))
		return E_FAIL;

	// set vertex buffer
	Vertex* pVertices;
	g_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	// front face
	pVertices[0] = Vertex(-1.0f, 1.0f, -1.0f, TD_COLOR_TILE);
	pVertices[1] = Vertex(1.0f, 1.0f, -1.0f, TD_COLOR_TILE);
	pVertices[2] = Vertex(-1.0f, -1.0f, -1.0f, TD_COLOR_TILE);
	pVertices[3] = Vertex(1.0f, -1.0f, -1.0f, TD_COLOR_TILE);

	// back face
	pVertices[4] = Vertex(-1.0f, 1.0f, 1.0f, TD_COLOR_TILE);
	pVertices[5] = Vertex(1.0f, 1.0f, 1.0f, TD_COLOR_TILE);
	pVertices[6] = Vertex(-1.0f, -1.0f, 1.0f, TD_COLOR_TILE);
	pVertices[7] = Vertex(1.0f, -1.0f, 1.0f, TD_COLOR_TILE);
	
	g_pVertexBuffer->Unlock();

	return S_OK;
}
HRESULT TD::InitIndexBuffer()
{
	// create index buffer
	if (FAILED(TD::g_pd3dDevice->CreateIndexBuffer(
		TD_NUM_INDICES * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&TD::g_pIndexBuffer,
		0)))
		return E_FAIL;

	// Set indices
	WORD* pIndices;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

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

	g_pIndexBuffer->Unlock();

	return S_OK;
}
HRESULT TD::InitCamera()
{
	// set view space
	D3DXVECTOR3 cameraPosition = TD_CAMERA_POSITION;
	D3DXVECTOR3 targetPosition = TD_TARGET_POSITION;
	D3DXVECTOR3 upVector = TD_WORLD_UP_VECTOR;

	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &cameraPosition, &targetPosition, &upVector);
	TD::g_pd3dDevice->SetTransform(D3DTS_VIEW, &viewMatrix);

	// set projection
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix,
		TD_PROJECTION_ANGLE,
		(float)TD_WINDOW_WIDTH / (float)TD_WINDOW_HEIGHT,
		TD_PROJECTION_NEAR,
		TD_PROJECTION_FAR);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);

	return S_OK;
}