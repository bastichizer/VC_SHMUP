//==================================================================
// main.cpp
//
// application entry point and windows message pump
//==================================================================

#include <Windows.h>
#include "RenderManager.h"
#include "Sprite.h"
#include "src\SHMUP_App.h"
#include "global.h"
#include "InputManager.h"

const int g_windowWidth = 480;
const int g_windowHeight = 640;

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		ValidateRect(hWnd, NULL);
		return 0;

	case WM_INPUT:
		InputManager::Get()->ProcessRawInput((HRAWINPUT)lParam);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"VC Shoot Em Up", NULL
	};
	RegisterClassEx(&wc);

	// Create the application's window
	DWORD windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	HWND hWnd = CreateWindowEx(NULL, "VC Shoot Em Up", "VC Shoot Em Up", windowStyle, 0, 0, g_windowWidth, g_windowHeight + 40, NULL, NULL, wc.hInstance, NULL);

	InputManager::Get()->Init(hWnd);

	if (SUCCEEDED(RenderManager::Get()->InitDevice(hWnd)))
	{
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		SHMUP_App app = SHMUP_App();
		app.Init();
		//SHMUP_GameManager gm = SHMUP_GameManager(NULL);

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT && msg.message != WM_DESTROY)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//gm.Update();
				//RenderManager::Get()->Begin();
				//RenderManager::Get()->Render();
				//gm.Render();
				//RenderManager::Get()->End();
				app.Update();
				app.Render();
			}
		}
		app.Shutdown();
		//RenderManager::Get()->Cleanup();
	}

	UnregisterClass("VC Shoot Em Up", wc.hInstance);

	return 0;
}