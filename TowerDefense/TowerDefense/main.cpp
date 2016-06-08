#include "TowerDefense.h"

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_DESTROY:
		TowerDefense::getInstance()->Cleanup();
		PostQuitMessage(0);
		return 0;
	case WM_TIMER:
		switch (wParam)
		{
		case TD_RENDER_TIMER_ID:
			TowerDefense::getInstance()->Render();
			ValidateRect(hWnd, nullptr);
			break;
		}
		return 0;
	case WM_RBUTTONDOWN:
		TowerDefense::getInstance()->SetRButton(true, LOWORD(lParam));
		return 0;
	case WM_RBUTTONUP:
		TowerDefense::getInstance()->SetRButton(false, LOWORD(lParam));
		return 0;
	case WM_MOUSEMOVE:
		if(TowerDefense::getInstance()->GetRButton())
			TowerDefense::getInstance()->SetCamera(LOWORD(lParam));
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

VOID EnterMsgLoop(HWND hWnd) {
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_QUIT) break;
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT) {
	UNREFERENCED_PARAMETER(hInst);

	// Register the window class
	WNDCLASSEX wc =	{
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

		EnterMsgLoop(hWnd);
	}

	UnregisterClass(TD_WINDOW_TITLE, wc.hInstance);
	return 0;
}