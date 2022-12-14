/*#ifndef UNICODE
#define UNICODE
#endif */

#include <windows.h>
#include <windowsx.h>
#include <winnt.h>

#include "N-angleDLL.h"
#pragma comment(lib, "Msimg32.lib")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void paintWind(HWND hwnd);
void DrawNangle(HWND hwnd, int x, int y, int radius);

bool onPaint = false;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hbrBackground = (HBRUSH)(3);
	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"SuperFigure",					// Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	// Run the message loop.

	MSG msg = { };

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
int X = 0, Y = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//RECT clientRect;
	//GetClientRect(hwnd, &clientRect);

	switch (uMsg)
	{
	case WM_CLOSE:
	{
		if (MessageBox(hwnd, L"Really quit?", L"Super application", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		return 0;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	case WM_PAINT:
	{
		paintWind(hwnd);
		return 0;
	}

	case WM_ERASEBKGND:
	{
		return 1;
	}

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_TAB:
		{

		}
		}
		break;
		return 0;
	}

	case WM_LBUTTONDOWN:
	{
		onPaint = true;
		X = GET_X_LPARAM(lParam);
		Y = GET_Y_LPARAM(lParam);

		RECT clientRect;
		GetClientRect(hwnd, &clientRect);
		InvalidateRect(hwnd, &clientRect, true);
		return 0;
	}

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void DrawNangle(HWND hwnd, int x, int y, int radius)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	HBITMAP hbmBack = CreateCompatibleBitmap(hdc, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	HDC backDc = CreateCompatibleDC(hdc);
	HGDIOBJ previousBackBmp = SelectObject(backDc, hbmBack);
	FillRect(backDc, &clientRect, (HBRUSH)(3));
	SetBkColor(backDc, RGB(0x64, 0x95, 0xED));


	BitBlt(hdc, 0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, backDc, 0, 0, SRCCOPY);
	SelectObject(backDc, previousBackBmp);//?
	DeleteDC(backDc);
	EndPaint(hwnd, &ps);
}

void paintWind(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	HBITMAP hbmBack = CreateCompatibleBitmap(hdc, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	HDC backDc = CreateCompatibleDC(hdc);
	HGDIOBJ previousBackBmp = SelectObject(backDc, hbmBack);
	FillRect(backDc, &clientRect, (HBRUSH)(3));

	SetBkColor(backDc, RGB(0x64, 0x95, 0xED));

	if (onPaint)
	{
		draw(backDc, X, Y, 100);
		onPaint = false;
	}

	BitBlt(hdc, 0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, backDc, 0, 0, SRCCOPY);
	SelectObject(backDc, previousBackBmp);//?
	DeleteDC(backDc);
	EndPaint(hwnd, &ps);
}