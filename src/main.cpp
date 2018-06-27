#include "stdafx.h"

#include <string>
#include "win32.h"

#include "MemoryService.h"

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void OnAssertFailed(const std::string& msg);
void ShowGameWindow(const wchar_t* msg, HINSTANCE hInstance, int nCmdShow);

void GameLoop();

int CALLBACK WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lcCmdLine, IN int nCmdShow)
{
	debug::__onAssertFailed = OnAssertFailed;

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	MemoryService service(sysInfo.dwPageSize);

	ShowGameWindow(L"HyperShot", hInstance, nCmdShow);

	MSG msg = { 0 };

	while (true)
	{
		//Message pump - process windows messages before letting game run it's own logic
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;
	}


	return msg.wParam;
}

void GameLoop()
{

}


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void ShowGameWindow(const wchar_t* msg, HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(0,
		L"WindowClass1",    // name of the window class
		msg,   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		CW_USEDEFAULT,    // x-position of the window
		CW_USEDEFAULT,    // y-position of the window
		1024,    // width of the window
		768,    // height of the window
		nullptr,    // we have no parent window, NULL
		nullptr,    // we aren't using menus, NULL
		hInstance,    // application handle
		nullptr);    // used with multiple windows, NULL

	if (!hWnd)
	{
		ASSERT(false, "Failed to create window! '%s'.", GetLastErrorString());
	}

	ShowWindow(hWnd, nCmdShow);
}


void OnAssertFailed(const std::string& msg)
{
	OutputDebugStringA(msg.c_str());

}

