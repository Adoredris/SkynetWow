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

		input = _getch();
	}

	controller.Stop();
	//Sleep(10);


	return 0;
}

