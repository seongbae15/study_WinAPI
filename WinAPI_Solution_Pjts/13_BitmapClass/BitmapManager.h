#pragma once
#include <Windows.h>
#include "BitMap.h"

class BitmapManager
{
public:
	static BitmapManager* GetInstance()
	{
		if (NULL == instance)
		{
			instance = new BitmapManager;
		}
		return instance;
	}
	BitmapManager();
	void Init(HWND hWnd, HINSTANCE hInst, int id);
	void Draw(HDC hdc, int x, int y);
	void Release();
	~BitmapManager();

private:
	static BitmapManager* instance;
	BitMap* bm;
};

