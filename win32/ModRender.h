#pragma once

#include <windows.h>
/*	Inspired by	https://www.catch22.net/tuts/win32/flicker-free-drawing#	*/

HDC hdcMem;
HBITMAP hbmMem;
HANDLE hOld;
PAINTSTRUCT ps;
HDC hdc;

void ModInitRenderMemory()
{
	hdcMem = CreateCompatibleDC(hdc);
}
void Paint(HWND handle)
{
	hdc = BeginPaint(handle, &ps);


}