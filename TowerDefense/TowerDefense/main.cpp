#include "TDGlobal.h"


//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
{
	// Create the D3D object, which is needed to create the D3DDevice.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	// Create the Direct3D device.
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// Device state would normally be set here

	return S_OK;
}


VOID InitVertexBuffer()
{
	g_pd3dDevice->CreateVertexBuffer(
		TD_NUM_VERTICES * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		0);
}
VOID InitIndexBuffer()
{
	g_pd3dDevice->CreateIndexBuffer(
		TD_NUM_INDICES * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBuffer,
		0);
}
VOID InitCamera()
{
	// set view space
	D3DXVECTOR3 cameraPosition = TD_CAMERA_POSITION;
	D3DXVECTOR3 targetPosition = TD_TARGET_POSITION;
	D3DXVECTOR3 upVector = TD_WORLD_UP_VECTOR;

	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &cameraPosition, &targetPosition, &upVector);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &viewMatrix);

	// set projection
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveLH(&projectionMatrix,
		TD_PROJECTION_ANGLE,
		(float)TD_WINDOW_WIDTH / (float)TD_WINDOW_HEIGHT,
		TD_PROJECTION_NEAR,
		TD_PROJECTION_FAR);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}


//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();

	if (g_pVertexBuffer != NULL)
		g_pVertexBuffer->Release();

	if (g_pIndexBuffer != NULL)
		g_pIndexBuffer->Release();
}



//-----------------------------------------------------------------------------
// Name: InitWorld()
// Desc: Init World and render it
//-----------------------------------------------------------------------------
VOID InitWorld()
{
	
}


//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	if (NULL == g_pd3dDevice)
		return;

	// Clear the backbuffer to a TD_BACKGROUND_COLOR
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, TD_BACKGROUND_COLOR, 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// Rendering of scene objects can happen here
		InitWorld();





		// End the scene
		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		TD_WINDOW_TITLE, NULL
	};
	RegisterClassEx(&wc);

	// Create the application's window
	HWND hWnd = CreateWindow(TD_WINDOW_TITLE, TD_WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, TD_WINDOW_WIDTH, TD_WINDOW_HEIGHT,
		NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		// Get Vertex Buffer and Index Buffer
		InitVertexBuffer();
		InitIndexBuffer();

		// Set Camera
		InitCamera();

		// Show the window
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		// Enter the message loop
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	UnregisterClass(TD_WINDOW_TITLE, wc.hInstance);
	return 0;
}