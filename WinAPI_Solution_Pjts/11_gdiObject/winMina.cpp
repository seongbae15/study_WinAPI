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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH myBrush, oldBrush;
	HPEN myPen, oldPen;
	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		myBrush = CreateSolidBrush(RGB(255,0,0));
		myPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		oldPen = (HPEN)SelectObject(hdc, myPen);
		Rectangle(hdc, 50, 50, 300, 200);
		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
		DeleteObject(myBrush);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}