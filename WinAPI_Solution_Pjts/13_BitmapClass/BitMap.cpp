#include "BitMap.h"

BitMap::BitMap()
{

}

void BitMap::Init(HDC hdc, HINSTANCE hInst, int id)
{
	memDC = CreateCompatibleDC(hdc);
	myBitMap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(id));
	oldBitMap = (HBITMAP)SelectObject(memDC, myBitMap);

	BITMAP bitmapInfo;
	GetObject(myBitMap, sizeof(bitmapInfo), &bitmapInfo);
	size.cx = bitmapInfo.bmWidth;
	size.cy = bitmapInfo.bmHeight;
}

void BitMap::Draw(HDC hdc, int x, int y, int spX, int spY)
{
	StretchBlt(hdc, x, y, size.cx * spX, size.cy * spY, memDC, 0, 0, size.cx, size.cy, SRCCOPY);
}

BitMap::~BitMap()
{
	SelectObject(memDC, oldBitMap);
	DeleteObject(myBitMap);
	DeleteDC(memDC);
}