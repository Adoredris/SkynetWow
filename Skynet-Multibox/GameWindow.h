#pragma once

#include "stdafx.h"
//#include "PixelReader.h"
#include "KeySender.h"
#include "Settings.h"
#include "KeyStateFreezing.h"

using namespace std;

class GameWindow {
public:
	//~GameWindow() {
	//};

	GameWindow(HWND _hwnd, HANDLE handle = 0) {
		hwnd = _hwnd;
		running = false;
		windows7 = !IsWindows8OrGreater();
		//std::cout << "win7: " << windows7 << std::endl;

		//pHandle = handle;
		//address = 0x40000000;

		//if (pHandle != 0) {
			//searchingThread = std::thread(std::mem_fn(&GameWindow::Scan), this);
		//}

		//searching = false;
		//gotProbablyCorrect = false;

		nextScanTime = std::chrono::system_clock::now();
	};

	void DoProcessing();
	HWND hwnd;

	void Stop();

private:
	void Run();
	void PixelProcess();

	double GetDoubleValue();
	COLORREF GetColorRefWin7();
	COLORREF GetColorRefWin10();		// otherwise known as other


	std::chrono::time_point<std::chrono::system_clock> nextScanTime;

	thread pixelThread;

	//void ParsePixelAndSend(COLORREF pixel);
	void ParseDoubleAndSend(double val);

	void DoBlueKeyPress(int key, bool lCtrl, bool rCtrl, bool lShift, bool rShift, bool lAlt, bool rAlt);
	void DoRedKeyPress(int key, bool rShift, bool rAlt);

	//static double repeatSpamTime;

	//static int pixelReadSleep;
	//static int sendKeySleep;
	bool running;

	static std::chrono::milliseconds delayAfterSpell;
	static std::chrono::milliseconds offDelay;
	static std::chrono::milliseconds deadDelay;			// don't read for freaking ages
	//static std::chrono::milliseconds delayBetweenClicks;
	static int delayBetweenSameClicks;
	static int delayBetweenDiffClicks;
	static std::chrono::milliseconds delayAfterNoSpell;

	static int windows7;

};