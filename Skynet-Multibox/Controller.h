#pragma once

#include "stdafx.h"

#include "GameWindow.h"

using namespace std;

class Controller {
private:

	thread logicThread;
	bool running;
	bool paused;

	static bool IsMultiPixelReadMatching(HWND _hwnd);

public:
	Controller();
	void Start();
	void Stop();
	void PauseResume();

	void Run();

	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
	void ValidateWindows();

	static list<GameWindow> gamewindows;
};