#include "stdafx.h"
#include "Controller.h"

Controller::Controller() {
	running = true;
	paused = false;
	logicThread = std::thread(std::mem_fn(&Controller::Run), this);

};

// return true == next
BOOL CALLBACK Controller::EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	Controller *pThis = reinterpret_cast<Controller *>(lParam);
	CHAR windowClass[32];
	std::string wowClass = std::string("GxWindowClass");
	int classSize = GetClassNameA(hwnd, windowClass, 32);
	if (std::string(windowClass).compare(wowClass) != 0) {
		
		return true;

	}


	for (list<GameWindow>::iterator iter = /*pThis->*/gamewindows.begin(); iter != /*pThis->*/gamewindows.end(); iter++) {
		if (iter->hwnd == hwnd) {
			return true;
		}
	}

	/*DWORD tempProcid = 0;
	GetWindowThreadProcessId(hwnd, &tempProcid);
	HANDLE pHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, tempProcid);
	char Buffer[MAX_PATH];
	GetModuleFileNameEx(pHandle, 0, Buffer, MAX_PATH);

	std::cout << Buffer << std::endl;
	std::string path = Buffer;
	//std::cout << path << std::endl;
	if (path.size() > 8 && path[path.size() - 6] == 'o' && (path[path.size() - 5] == 'w' || path[path.size() - 5] == 'W')) {
		std::cout << "32 bit wow\nMemory reading might be viable.\n";

	} else {
		// 64 bit wow
		CloseHandle(pHandle);
		pHandle = 0;

	}*/

	// removed this crap cause false positives render it pointless anyway
	/*if (!IsMultiPixelReadMatching(hwnd)) {
		/////std::cout << "not logged in / pandeity not loaded?\n";
		return true;
	}*/

	//std::string newTitle = "WoW - ";
	//newTitle += std::to_string((long)hwnd);
	//newTitle += " - Pixel";

	//SetWindowText(hwnd, newTitle.c_str());

	/*pThis->*/gamewindows.push_back(GameWindow(hwnd/*, pHandle*/));

	//InjectDll();

	std::cout << "Added a game window" << std::endl;

	return true;
}

// maybe you should validate the actual process is the same too, but anyway
void Controller::ValidateWindows() {
	
	list<GameWindow>::iterator windowIter = gamewindows.begin();
	while (windowIter != gamewindows.end()) {
		if (!IsWindow(windowIter->hwnd)) {
			windowIter->Stop();
			windowIter = gamewindows.erase(windowIter);
			std::cout << "a window was terminated" << std::endl;
		}
		else {
			windowIter++;
		}
	}
}

void Controller::Run() {
	//std::cout << "run\n";
	EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(this));
	std::chrono::time_point<std::chrono::system_clock> lastScan = std::chrono::system_clock::now();
	
	while (running) {
		int delay = Settings::ControllerRunDelay;		// idea of this variable being here is in the future it will lower the sleep duration by however long it to to perform EnumWindows, etc
		if (!paused) {
			for (list<GameWindow>::iterator windowIter = gamewindows.begin(); windowIter != gamewindows.end(); windowIter++) {
				//std::cout << "processing window\n";
				windowIter->DoProcessing();
			}
		}


		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

		std::chrono::duration<double> timeDifference = now - lastScan;
		if (timeDifference.count() > Settings::ScanWindowsFrequencySeconds) {
			//std::cout << "checking windows\n";
			ValidateWindows();
			EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(this));
			lastScan = now;
		}

		Sleep(delay);
	}
	for (list<GameWindow>::iterator windowIter = gamewindows.begin(); windowIter != gamewindows.end(); windowIter++) {
		windowIter->Stop();
	}
};

bool Controller::IsMultiPixelReadMatching(HWND _hwnd) {
	HDC hdc = GetDC(_hwnd);
	int x = Settings::x;
	int y = Settings::y;
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
	/*} else {
	return false;
	}*/

};

void Controller::PauseResume() {
	paused = !paused;
}

void Controller::Stop() {
	running = false;
	logicThread.join();
};

list<GameWindow> Controller::gamewindows;