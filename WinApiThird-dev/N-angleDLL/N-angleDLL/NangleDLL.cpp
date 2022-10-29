// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include "N-angleDLL.h"
#include <windows.h>
#include <wingdi.h>
#pragma comment(lib, "Msimg32.lib")

#define EOF (-1)


void draw(HDC hdc, int x, int y, int radius)
{
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(0, 0, 100));
	HGDIOBJ oldBrush = SelectObject(hdc, hBrush);

	TRIVERTEX vertex[3]{};
	int r = radius * 6;
	int a = (int)(r * 1.7 / 2);
	vertex[0].x = x;
	vertex[0].y = y - r;
	vertex[0].Red = 0xff00;
	vertex[0].Green = 0x8000;
	vertex[0].Blue = 0x0000;
	vertex[0].Alpha = 0x0000;

	vertex[1].x = x - a;
	vertex[1].y = y + r / 2;
	vertex[1].Red = 0x8000;
	vertex[1].Green = 0x0000;
	vertex[1].Blue = 0x7000;
	vertex[1].Alpha = 0x0000;

	vertex[2].x = x + a;
	vertex[2].y = y + r / 2;
	vertex[2].Red = 0x9080;
	vertex[2].Green = 0x0009;
	vertex[2].Blue = 0x9000;
	vertex[2].Alpha = 0x0700;

	GRADIENT_TRIANGLE gTriangle{};
	gTriangle.Vertex1 = 0;
	gTriangle.Vertex2 = 1;
	gTriangle.Vertex3 = 2;

	GradientFill(hdc, vertex, 3, &gTriangle, 1, GRADIENT_FILL_TRIANGLE);

	SelectObject(hdc, oldBrush);
}

