#pragma once

#include "stdafx.h"
//#include "PixelReader.h"
//#include "KeySender.h"
#include "../Skynet-Multibox/KeyStateFreezing.h"

using namespace std;

class GameProcess {
public:
	GameProcess() {
		nextScanTime = std::chrono::system_clock::now();
		hwnd = 0;
	};

	void DoProcessing(HWND _hwnd);

	void Stop();

	HWND hwnd;

private:
	double GetDoubleValue();

	void ParseDoubleAndSend(double val);

	COLORREF GetColorRefWin10();		// otherwise known as other


	std::chrono::time_point<std::chrono::system_clock> nextScanTime;

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

};