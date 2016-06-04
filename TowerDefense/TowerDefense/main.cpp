#include "TowerDefense.h"

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		TowerDefense::getInstance()->Cleanup();
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		TowerDefense::getInstance()->Render();
		ValidateRect(hWnd, NULL);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
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

	TowerDefense* pTD = TowerDefense::getInstance();
	// Initialize Direct3D
	if (SUCCEEDED(pTD->InitD3D(hWnd)))
	{
		// Setup
		pTD->SetUp();

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