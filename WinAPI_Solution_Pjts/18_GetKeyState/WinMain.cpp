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
	TCHAR Mes[128] = TEXT("왼 쪽 : 동기 검사, 오른 쪽 : 비동기 검사, T : 시간 끌기");
	static TCHAR str1[128] = TEXT("검사대기");
	static TCHAR str2[128] = TEXT("검사대기");
	TCHAR str3[128];
	int i;

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		if (GetKeyState(VK_SHIFT) & 0x8000) {
			lstrcpy(str1,TEXT("동기 검사 : Shift키가 눌러짐"));
		}
		else {
			lstrcpy(str1, TEXT("동기 검사 : Shift키가 안눌러짐"));
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_RBUTTONDOWN:
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
			lstrcpy(str1, TEXT("비동기 검사 : Shift키가 눌러짐"));
		}
		else {
			lstrcpy(str1, TEXT("비동기 검사 : Shift키가 안눌러짐"));
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case 'T':
			for (i = 0; i < 30; i++) {
				wsprintf(str3, TEXT("카운트 = %d"), i);
				SetWindowText(hWnd, str3);
				Sleep(100);
			}
			break;
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		TextOut(hdc, 10, 30, str1, lstrlen(str1));
		TextOut(hdc, 10, 50, str2, lstrlen(str2));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}