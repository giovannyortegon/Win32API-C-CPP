#define UNICODE
#define _UNICODE
#include <windows.h>
#include <tchar.h>


// Titles and messages
const TCHAR CLSNAME[] = TEXT("helloworldWClass");
const TCHAR TITLE[] = TEXT("Application");

LRESULT CALLBACK winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp);

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdline, int cmdshow)
//int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PTSTR cmdline, int cmdshow)
{
	WNDCLASSEX wc = { };
	MSG msg;
	HWND hwnd;

	wc.cbSize = sizeof (WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = winproc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon (wc.hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor (NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLSNAME;
	wc.hIconSm = LoadIcon (wc.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, TEXT("Could not register window class"),
				   TEXT("Windows Desktop Guided Tour"), MB_ICONERROR);
		return 1;
	}

	 hwnd = CreateWindowEx(
		WS_EX_LEFT,
		CLSNAME,
		TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		300,
		200,
		NULL,
		NULL,
		hInst,
		NULL);

	if (!hwnd) {
		MessageBox(NULL, TEXT("Could not create window"), TEXT("Windows Desktop Guided Tour"), MB_ICONERROR);
		return 1;
	}

	ShowWindow(hwnd, cmdshow);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
LRESULT CALLBACK winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = TEXT("Hello, Windows desktop");

	switch(wm)
	{
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			TextOut(hdc, 5, 5, greeting, _tcslen(greeting));
			EndPaint(hwnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, wm, wp, lp);
			break;
	}
	return (0);
}
