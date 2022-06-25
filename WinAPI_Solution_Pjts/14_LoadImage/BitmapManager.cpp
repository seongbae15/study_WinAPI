#include "BitmapManager.h"

BitmapManager* BitmapManager::instance = NULL;

BitmapManager::BitmapManager()
{

}

void BitmapManager::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);
	bm = new BitMap;
	TCHAR fileName[256];
	wsprintf(fileName, L"RES//00.bmp");
	bm->Init(hdc, hInst, fileName);
}

void BitmapManager::Draw(HDC hdc, int x, int y)
{
	bm->Draw(hdc, x, y);
}

void BitmapManager::Release()
{
	delete(instance);
}

BitmapManager::~BitmapManager()
{
	delete(bm);
}