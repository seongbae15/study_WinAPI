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

enum
{
	ID_R1 = 101,
	ID_R2,
	ID_R3,
	ID_R4,
	ID_R5,
};

HWND r1, r2, r3, r4, r5;
int Graph = 0;
COLORREF Color = RGB(0, 0, 0);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH myBrush, oldBrush;

	static HWND c1, c2;
	static BOOL bEllipse = FALSE;
	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow(TEXT("Button"), TEXT("Click Me"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 20, 100, 25, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("Me too"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 50, 100, 25, hWnd, (HMENU)1, g_hInst, NULL);

		CreateWindow(TEXT("Button"), TEXT("Graph"), WS_CHILD | WS_VISIBLE|
			BS_GROUPBOX, 105, 105, 120, 110, hWnd, (HMENU)2, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("Color"), WS_CHILD | WS_VISIBLE |
			BS_GROUPBOX, 245, 105, 120, 110, hWnd, (HMENU)3, g_hInst, NULL);

		r1 = CreateWindow(TEXT("Button"),TEXT("Rectangle"),WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON | WS_GROUP, 110, 120, 100, 30, hWnd, (HMENU)ID_R1, g_hInst, NULL);
		r2 = CreateWindow(TEXT("Button"), TEXT("Ellipse"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON, 110, 150, 100, 30, hWnd, (HMENU)ID_R2, g_hInst, NULL);
		
		r3 = CreateWindow(TEXT("Button"), TEXT("Red"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON | WS_GROUP, 250, 120, 100, 30, hWnd, (HMENU)ID_R3, g_hInst, NULL);
		r4 = CreateWindow(TEXT("Button"), TEXT("Green"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON, 250, 150, 100, 30, hWnd, (HMENU)ID_R4, g_hInst, NULL);
		r5 = CreateWindow(TEXT("Button"), TEXT("Blue"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON, 250, 180, 100, 30, hWnd, (HMENU)ID_R5, g_hInst, NULL);
		Graph = 0;
		Color = RGB(255, 0, 0);
		CheckRadioButton(hWnd, ID_R1, ID_R2, ID_R1);
		CheckRadioButton(hWnd, ID_R3, ID_R5, ID_R3);
		
		c1 = CreateWindow(TEXT("Button"), TEXT("Draw Ellipse"), WS_CHILD| WS_VISIBLE |
			BS_CHECKBOX, 520, 120, 160, 25, hWnd, (HMENU)4, g_hInst, NULL);
		c2 = CreateWindow(TEXT("Button"), TEXT("GoobBye Message?"), WS_CHILD | WS_VISIBLE |
			BS_AUTOCHECKBOX, 520, 150, 160, 25, hWnd, (HMENU)5, g_hInst, NULL);

		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			MessageBox(hWnd, TEXT("1st Button Clicked"), TEXT("Button"), MB_OK);
			break;
		case 1:
			MessageBox(hWnd, TEXT("2nd Button Clicked"), TEXT("Button"), MB_OK);
			break;
		case ID_R1:
			Graph = 0;
			break;
		case ID_R2:
			Graph = 1;
			break;
		case ID_R3:
			Color = RGB(255, 0, 0);
			break;
		case ID_R4:
			Color = RGB(0, 255, 0);
			break;
		case ID_R5:
			Color = RGB(0, 0, 255);
			break;

		case 4:
			if (SendMessage(c1, BM_GETCHECK, 4, 0) == BST_UNCHECKED)
			{
				SendMessageW(c1, BM_SETCHECK, BST_CHECKED, 0);
				bEllipse = TRUE;
			}
			else
			{
				SendMessage(c1, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		myBrush = CreateSolidBrush(Color);
		oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		switch (Graph)
		{
		case 0:
			Rectangle(hdc, 210, 300, 400, 400);
			break;
		case 1:
			Ellipse(hdc, 210, 300, 400, 400);
			break;
		}
		if (bEllipse)
			Ellipse(hdc, 500, 300, 700, 400);
		else
			Rectangle(hdc, 500, 300, 700, 400);
		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		if (SendMessage(c2, BM_GETCHECK, 5, 0) == BST_CHECKED)
			MessageBox(hWnd, TEXT("Good bye"), TEXT("Button"), MB_OK);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}