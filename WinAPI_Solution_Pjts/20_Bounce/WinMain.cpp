#include <Windows.h>

//Message processing function.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Hello World");
HWND hWndMain;

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
	hWndMain = hWnd;
	//Message loop.
	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message); //Checking and Making keyboard input message.
		DispatchMessage(&Message);	//Transfer message of message queue to WndProc
	}
	return (int)Message.wParam;
}

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);
	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;
	BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

#define R 20
int x, y;
int xi, yi;
HBITMAP hBit;

void OnTimer()
{
	RECT crt;
	HDC hdc, hMemDC;
	HBITMAP OldBit;
	HPEN hPen, OldPen;
	HBRUSH hBrush, OldBrush;
	int i;

	GetClientRect(hWndMain, &crt);
	hdc = GetDC(hWndMain);
	if (hBit == NULL) {
		hBit = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
	}
	hMemDC = CreateCompatibleDC(hdc);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBit);
	FillRect(hMemDC, &crt, GetSysColorBrush(COLOR_WINDOW));
	if (x <= R || x >= crt.right - R)
		xi *= -1;
	if (y <= R || y >= crt.bottom - R)
		yi *= -1;
	x += xi;
	y += yi;
	for (i = 0; i < crt.right; i += 10) {
		MoveToEx(hMemDC, i, 0, NULL);
		LineTo(hMemDC, i, crt.bottom);
	}
	for (i = 0; i < crt.bottom; i += 10) {
		MoveToEx(hMemDC, 0, i, NULL);
		LineTo(hMemDC, crt.right, i);
	}
	hPen = CreatePen(PS_INSIDEFRAME, 5, RGB(255, 0, 0));
	OldPen = (HPEN)SelectObject(hMemDC, hPen);
	hBrush = CreateSolidBrush(RGB(0, 0, 255));
	OldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
	Ellipse(hMemDC, x - R, y - R, x + R, y + R);
	DeleteObject(SelectObject(hMemDC, OldBrush));
	DeleteObject(SelectObject(hMemDC, OldPen));

	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWndMain, hdc);
	InvalidateRect(hWndMain, NULL, FALSE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, OldPen;
	HBRUSH hBrush, OldBrush;
	RECT crt;
	int i;

	switch (iMessage)
	{
	case WM_CREATE:
		x = 50;
		y = 50;
		xi = 4;
		yi = 5;
		SetTimer(hWnd, 1, 25, NULL);
		return 0;
	case WM_TIMER:
		OnTimer();
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (hBit) DrawBitmap(hdc, 0, 0, hBit);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		if (hBit) {
			DeleteObject(hBit);
		}
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}