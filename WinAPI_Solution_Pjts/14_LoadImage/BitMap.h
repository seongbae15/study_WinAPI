#pragma once
#include <Windows.h>

class BitMap
{
public:
	BitMap();
	void Init(HDC hdc, HINSTANCE hInst, LPCWSTR fileName);
	void Draw(HDC hdc, int x, int y, int spX = 1, int spY = 1);
	~BitMap();

private:
	HDC memDC;
	HBITMAP myBitMap;
	HBITMAP oldBitMap;
	SIZE size;
};

