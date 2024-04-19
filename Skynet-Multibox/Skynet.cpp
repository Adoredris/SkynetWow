// Skynet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <signal.h>

#include "Controller.h"


bool running;
Controller controller;
BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType) {
	if (dwCtrlType == CTRL_CLOSE_EVENT)
	{
		controller.Stop();
		running = false;
		return TRUE;
	}

	return FALSE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	BOOL ret = SetConsoleCtrlHandler(ConsoleHandlerRoutine, true);
	Settings::LoadSettings();
	running = true;
	
	char input = _getch();
	while (input != 'q' && running) {
		if (input == 'p') {
			controller.PauseResume();
		}
		else if (input == 'l') {
			Settings::LoadSettings();
		}
		else if (input == '1') {
			// force all windows to take up 1 screen
			std::cout << "making all windows take up 1 fullscreen" << std::endl;
			int i = 0;
			for (list<GameWindow>::iterator windowIter = controller.gamewindows.begin(); windowIter != controller.gamewindows.end(); windowIter++) {
				SetWindowLong(windowIter->hwnd, GWL_STYLE, 0x94000000);
				SetWindowPos(windowIter->hwnd, HWND_NOTOPMOST, i * 1920, 0, 1920, 1040, SWP_NOOWNERZORDER);
				i++;
			}
		}
		else if (input == '3') {
			// force all windows to take up 3 screen
			std::cout << "making all windows take up 3 screen" << std::endl;
			int i = 0;
			for (list<GameWindow>::iterator windowIter = controller.gamewindows.begin(); windowIter != controller.gamewindows.end(); windowIter++) {
				SetWindowLong(windowIter->hwnd, GWL_STYLE, 0x94000000);
				SetWindowPos(windowIter->hwnd, HWND_NOTOPMOST, -1920, 0, 5760, 1040, SWP_NOOWNERZORDER);
			}
		}
		else if (input == 'w') {
			// force all windows into windowed mode
			std::cout << "making all windows windowed" << std::endl;
			int i = 0;
			for (list<GameWindow>::iterator windowIter = controller.gamewindows.begin(); windowIter != controller.gamewindows.end(); windowIter++) {
				if (GetWindowLong(windowIter->hwnd, GWL_STYLE) != 0x16cf0000) {
					SetWindowLong(windowIter->hwnd, GWL_STYLE, 0x16cf0000);
					SetWindowPos(windowIter->hwnd, HWND_NOTOPMOST, i * 1920 + 5, 5, 1735, 919, SWP_NOOWNERZORDER);
				}
			}
		}

		input = _getch();
	}

	controller.Stop();
	//Sleep(10);


	return 0;
}

