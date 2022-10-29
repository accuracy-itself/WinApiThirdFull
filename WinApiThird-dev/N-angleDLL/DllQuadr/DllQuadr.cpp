// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include "DllQuadr.h"
#include <windows.h>
#include <wingdi.h>
#pragma comment(lib, "Msimg32.lib")

#define EOF (-1)


void draw(HDC hdc, int x, int y, int radius)
{
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(0, 0, 100));
	HGDIOBJ oldBrush = SelectObject(hdc, hBrush);

	TRIVERTEX vertex[2]{};
	int r = radius;
	vertex[0].x = x - r * 4;
	vertex[0].y = y - r * 4;
	vertex[0].Red = 0xff00;
	vertex[0].Green = 0x8000;
	vertex[0].Blue = 0x0000;
	vertex[0].Alpha = 0x0000;

	vertex[1].x = x + r * 4;
	vertex[1].y = y + r * 4;
	vertex[1].Red = 0x8000;
	vertex[1].Green = 0x0000;
	vertex[1].Blue = 0x7000;
	vertex[1].Alpha = 0x0000;

	GRADIENT_RECT gRect{};
	gRect.UpperLeft = 0;
	gRect.LowerRight = 1;

	GradientFill(hdc, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_H);

	SelectObject(hdc, oldBrush);
}

