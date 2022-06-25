#include <Windows.h>

//Message processing function.
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Hello World");

//Entry point.
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;		//Set message processing function.
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	//Set style.

	RegisterClass(&WndClass);

	//Create Window
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	//Message loop.
	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message); //Checking and Making keyboard input message.
		DispatchMessage(&Message);	//Transfer message of message queue to WndProc
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HDC hMemDC;
	HBITMAP myImage, oldImage;
	int bx, by;
	BITMAP bit;

	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hMemDC = CreateCompatibleDC(hdc);
		myImage = (HBITMAP)LoadImage(NULL, TEXT("image.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		oldImage = (HBITMAP)SelectObject(hMemDC, myImage);
		GetObject(myImage, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;

		BitBlt(hdc, 50, 50, bx, by, hMemDC, 0, 0, SRCCOPY);
		TransparentBlt(hdc, 350, 50, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));
		TransparentBlt(hdc, 650, 50, bx / 4, by / 4,
			hMemDC, (bx / 4) * 1, (by / 4) * 2, bx / 4, by / 4, RGB(255, 0, 255));
		SelectObject(hMemDC, oldImage);
		DeleteObject(myImage);
		DeleteDC(hMemDC);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}