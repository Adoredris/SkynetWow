// Skynet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <signal.h>
#include "GameProcess.h"

std::string wowClass = std::string("GxWindowClass");
bool running = true;

BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType) {
	if (dwCtrlType == CTRL_CLOSE_EVENT)
	{
		running = false;
		return TRUE;
	}

	return FALSE;
}

bool IsWowActiveWindow(HWND *hwnd)
{
	char wnd_class[32];
	*hwnd = GetForegroundWindow(); // get handle of currently active window
	RealGetWindowClassA(*hwnd, wnd_class, sizeof(wnd_class));
	if (std::string(wnd_class).compare(wowClass) == 0) {
		return true;
	}
	return false;
}

bool IsMultiPixelReadMatching(HWND _hwnd) {
	HDC hdc = GetDC(_hwnd);
	int x = 1;
	int y = 1;
	COLORREF first = GetPixel(hdc, x, y);
	//if (IsNotWhiteOrBlack(&first)) {
	COLORREF second = GetPixel(hdc, x + 5, y);
	if ((int)GetBValue(first) != (int)GetBValue(second) || (int)GetGValue(first) != (int)GetGValue(second) || (int)GetRValue(first) != (int)GetRValue(second))
		return false;
	else {
		second = GetPixel(hdc, x, y + 5);
		if ((int)GetBValue(first) != (int)GetBValue(second) || (int)GetGValue(first) != (int)GetGValue(second) || (int)GetRValue(first) != (int)GetRValue(second))
			return false;
		else {
			second = GetPixel(hdc, x + 5, y + 5);
			if ((int)GetBValue(first) != (int)GetBValue(second) || (int)GetGValue(first) != (int)GetGValue(second) || (int)GetRValue(first) != (int)GetRValue(second))
				return false;
			else
				return true;
		}
	}

};

int _tmain(int argc, _TCHAR* argv[])
{
	BOOL ret = SetConsoleCtrlHandler(ConsoleHandlerRoutine, true);
	
	GameProcess gameProcess;

	HWND hwnd;
	while (running) {
		if (IsWowActiveWindow(&hwnd)) {
			gameProcess.DoProcessing(hwnd);
		} else {
			//std::cout << "not wow\n";
		}
	}


	return 0;
}

