#include "TDGlobal.h"

/***
*	Global Variables and Static Variables
***/
LPDIRECT3D9 TD::g_pD3D = nullptr;
LPDIRECT3DDEVICE9 TD::g_pd3dDevice = nullptr;

IDirect3DVertexBuffer9* TD::g_pVertexBuffer = nullptr;
IDirect3DIndexBuffer9* TD::g_pIndexBuffer = nullptr;

const DWORD TD::Vertex::FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

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
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

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
	TD::g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, TD_BACKGROUND_COLOR, 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(TD::g_pd3dDevice->BeginScene()))
	{
		// Rendering of scene objects can happen here
		




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

HRESULT TD::InitVertexBuffer()
{
	if (FAILED(TD::g_pd3dDevice->CreateVertexBuffer(
		TD_NUM_VERTICES * sizeof(TD::Vertex),
		D3DUSAGE_WRITEONLY,
		TD::Vertex::FVF,
		D3DPOOL_MANAGED,
		&TD::g_pVertexBuffer,
		0)))
		return E_FAIL;
	else
		return S_OK;
}
HRESULT TD::InitIndexBuffer()
{
	TD::g_pd3dDevice->CreateIndexBuffer(
		TD_NUM_INDICES * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&TD::g_pIndexBuffer,
		0);

	return S_OK;
}