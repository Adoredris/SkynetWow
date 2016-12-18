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

	GameWindow(HWND _hwnd) {
		hwnd = _hwnd;

		nextScanTime = std::chrono::system_clock::now();
	};

	void DoProcessing();
	HWND hwnd;

	void Stop();

private:
	void Run();
	void PixelProcess();

	COLORREF GetColorRef();

	std::chrono::time_point<std::chrono::system_clock> nextScanTime;

	thread pixelThread;

	void ParsePixelAndSend(COLORREF pixel);

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
	static int delayBetweenClicks;
	static std::chrono::milliseconds delayAfterNoSpell;

};