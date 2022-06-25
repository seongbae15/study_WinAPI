#include "BitmapManager.h"

BitmapManager* BitmapManager::instance = NULL;

BitmapManager::BitmapManager()
{
	
}

void BitmapManager::Init(HWND hWnd, HINSTANCE hInst, int id)
{
	HDC hdc = GetDC(hWnd);
	bm = new BitMap;
	bm->Init(hdc, hInst, id);
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