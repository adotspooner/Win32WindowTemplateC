#include <Windows.h>
#include <stdio.h>
#include <string.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// forward declaration of MainWndProc
LRESULT MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void OutputLastError() {
	DWORD errorCode = GetLastError();
	LPSTR errorMessage;
	DWORD errorSize = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
		(LPSTR)&errorMessage,
		0,
		NULL
	);
	char formattedMessageBuffer[1024];
	int bytesWritten = sprintf_s(formattedMessageBuffer, sizeof(formattedMessageBuffer), "Error %d (0x%X): %s", errorCode, errorCode, errorMessage);
	// print error message to dbg output
	OutputDebugStringA(formattedMessageBuffer);
	// free the error message buffer
	LocalFree(errorMessage);
}

int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	// define window class for main window
	WNDCLASSEXA wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEXA);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = MainWndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = NULL;
	wndClass.hCursor = LoadCursorA(NULL, (LPCSTR)IDC_ARROW);
	wndClass.hbrBackground = NULL;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = "MainWindowClass";
	wndClass.hIconSm = NULL;

	// register window class
	ATOM wndClassAtom = RegisterClassExA(&wndClass);

	// check if window class registration failed
	if (wndClassAtom == NULL) {
		OutputLastError();
		return 1;
	}

	HWND hWnd = CreateWindowExA(
		NULL,
		"MainWindowClass",
		"Win32 - Window Template - C",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// check if window creation failed
	if (hWnd == NULL) {
		OutputLastError();
		return 1;
	}

	// show the window
	ShowWindow(hWnd, nCmdShow);

	// update the window
	BOOL updateStatus = UpdateWindow(hWnd);

	// check if window update failed
	if (updateStatus == NULL) {
		OutputLastError();
		return 1;
	}

	// specify the desired window size
	RECT adjustWindowRectangle = { 0 };
	adjustWindowRectangle.left = 0;
	adjustWindowRectangle.top = 0;
	adjustWindowRectangle.right = WINDOW_WIDTH;
	adjustWindowRectangle.bottom = WINDOW_HEIGHT;

	// calculate the window rect so that the client are matches the desired size
	BOOL adjustStatus = AdjustWindowRectEx(&adjustWindowRectangle, WS_OVERLAPPEDWINDOW, FALSE, NULL);

	// check if window adjustment failed
	if (adjustStatus == FALSE) {
		OutputLastError();
		return 1;
	}

	// get monitor handle
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

	int windowCenterPositionX = 0;
	int windowCenterPositionY = 0;
	int windowAdjustedWidth = adjustWindowRectangle.right - adjustWindowRectangle.left;
	int windowAdjustedHeight = adjustWindowRectangle.bottom - adjustWindowRectangle.top;

	if (hMonitor != NULL) {

		MONITORINFO mInfo = { 0 };
		mInfo.cbSize = sizeof(MONITORINFO);

		// get monitor info
		BOOL miStatus = GetMonitorInfoA(hMonitor, &mInfo);

		if (miStatus != FALSE) {
			windowCenterPositionX = (mInfo.rcWork.left + mInfo.rcWork.right) / 2 - windowAdjustedWidth / 2;
			windowCenterPositionY = (mInfo.rcWork.top + mInfo.rcWork.bottom) / 2 - windowAdjustedHeight / 2;
		}

	}

	// resize the window to the calculated size
	BOOL setStatus = SetWindowPos(
		hWnd,
		NULL,
		windowCenterPositionX,
		windowCenterPositionY,
		windowAdjustedWidth,
		windowAdjustedHeight,
		SWP_SHOWWINDOW
	);

	// check if set window position failed
	if (setStatus == FALSE) {
		OutputLastError();
		return 1;
	}

	// message struct for window messages
	MSG msg;
	// store return value of GetMessageA here
	BOOL bRet;
	// blocking message pump
	while ((bRet = GetMessageA(&msg, hWnd, 0, 0)) != FALSE) {
		// if GetMessageA returns error bRet is set to -1
		if (bRet == -1) {
			OutputLastError();
			return 1;
		}
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	return 0;

}


LRESULT MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_CREATE:
	{
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		RECT cr;
		HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

		HDC hdc = BeginPaint(hWnd, &ps);

		// check if display device context is available
		if (hdc == NULL) {
			OutputLastError();
			return 0;
		}

		GetClientRect(hWnd, &cr);
		FillRect(hdc, &cr, brush);

		TextOutA(hdc, 32, 32, "Hello, World!", 13);

		// return value always nonzero
		EndPaint(hWnd, &ps);

		DeleteObject(brush);

		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProcA(hWnd, msg, wParam, lParam);
}

