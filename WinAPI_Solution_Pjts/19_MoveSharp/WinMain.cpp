#include <Windows.h>

//Message processing function.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
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

#define ACC 5

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x = 100, y = 100;
	static int delta = 1;
	BOOL bPress;
	RECT rt;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 50, NULL);
		return 0;
	case WM_TIMER:
		bPress = FALSE;
		if (GetKeyState(VK_LEFT) & 0x8000) {
			x -= (delta / ACC);
			bPress = TRUE;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000) {
			x += (delta / ACC);
			bPress = TRUE;
		}
		if (GetKeyState(VK_UP) & 0x8000) {
			y -= (delta / ACC);
			bPress = TRUE;
		}
		if (GetKeyState(VK_DOWN) & 0x8000) {
			y += (delta / ACC);
			bPress = TRUE;
		}
		if (bPress) {
			delta = min(delta + 1, ACC * 10);
			SetRect(&rt, x - 20, y - 40, x + 20, y + 40);
			InvalidateRect(hWnd, &rt, TRUE);
		}
		else {
			delta = 1;
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, x, y, TEXT("#"), 1);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}