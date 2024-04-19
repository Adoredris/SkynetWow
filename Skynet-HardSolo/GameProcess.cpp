#include "stdafx.h"
#include "GameProcess.h"

std::chrono::milliseconds GameProcess::delayAfterSpell = std::chrono::milliseconds(500);

std::chrono::milliseconds GameProcess::offDelay = std::chrono::milliseconds(1000);
std::chrono::milliseconds GameProcess::deadDelay = std::chrono::milliseconds(5000);
//std::chrono::milliseconds GameWindow::delayBetweenClicks = std::chrono::milliseconds(50);
int GameProcess::delayBetweenSameClicks = 100;
int GameProcess::delayBetweenDiffClicks = 20;
std::chrono::milliseconds GameProcess::delayAfterNoSpell = std::chrono::milliseconds(100);

void GameProcess::DoProcessing(HWND _hwnd) {
	hwnd = _hwnd;
	bool ran = false;
	double val = 0;
	double newVal = GetDoubleValue();
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> sendTime = now - GameProcess::deadDelay;
	while (newVal != 0) {
		if (KeyStateFreezing::IsModifierDown()) {
			ran = false;
			//std::cout << "skipping\n";
			break;
		}
		ran = true;
		if (val == newVal) {
			std::chrono::duration<double> timeDifference = (now - sendTime);
			if (timeDifference.count() * 1000 > delayBetweenSameClicks) {
				ParseDoubleAndSend(newVal);
				sendTime = now;
			}
		}
		else
		{
			ParseDoubleAndSend(newVal);
			sendTime = now;
			val = newVal;
		}
		Sleep(delayBetweenDiffClicks);
		newVal = GetDoubleValue();
		now = std::chrono::system_clock::now();
	}
	if (ran) {
		nextScanTime = std::chrono::system_clock::now() + delayAfterSpell;
	}
	else {
		nextScanTime = std::chrono::system_clock::now() + delayAfterNoSpell;
	}
};

void GameProcess::DoBlueKeyPress(int key, bool lCtrl, bool rCtrl, bool lShift, bool rShift, bool lAlt, bool rAlt) {
	if (key == VK_ESCAPE ||
		key == VK_RETURN ||
		key == VK_SNAPSHOT ||
		key == VK_DELETE && lCtrl && lAlt ||
		key == VK_F4 && (lAlt || rAlt) ||
		key == 0 || key == 0xFF ||
		key == VK_XBUTTON1 || key == VK_XBUTTON2)	// mouse 4/5 
	{
	}
	else {
		//std::cout << lCtrl << rCtrl << lShift << rShift << lAlt << rAlt << std::endl;

		PostMessage(hwnd, WM_KEYUP, 0xA2, 0);	// left control
		PostMessage(hwnd, WM_KEYUP, 0xA3, 0);	// right control
		PostMessage(hwnd, WM_KEYUP, 0xA0, 0);	// left shift
		PostMessage(hwnd, WM_KEYUP, 0xA1, 0);	// right shift
		PostMessage(hwnd, WM_KEYUP, 0xA4, 0);	// left alt
		PostMessage(hwnd, WM_KEYUP, 0xA5, 0);	// right alt

		// temp
		/*PostMessage(hwnd, WM_KEYDOWN, 0xA1, 0x2A8 << 15);

		PostMessage(hwnd, WM_KEYDOWN, 0x31, 2 << 15);

		PostMessage(hwnd, WM_KEYUP, 0x31, (2 << 15) + 3);

		PostMessage(hwnd, WM_KEYUP, 0xA1, (0x2A8 << 15) + 3);

		Sleep(5000);*/


		if (lCtrl) {
			PostMessage(hwnd, WM_KEYDOWN, 0xA2, 0);
		}
		if (rCtrl) {
			PostMessage(hwnd, WM_KEYDOWN, 0xA3, 0);
		}
		if (lShift) {
			PostMessage(hwnd, WM_KEYDOWN, 0xA0, 0);
		}
		if (rShift) {
			PostMessage(hwnd, WM_KEYDOWN, 0xA1, 0);
		}
		if (lAlt) {
			PostMessage(hwnd, WM_KEYDOWN, 0xA4, 0);
		}
		if (rAlt) {
			PostMessage(hwnd, WM_KEYDOWN, 0xA5, 0);
		}





		if (key == 5 || key == 6) {
			// mouse buttons
			//std::cout << "trying to send mouse button" << std::endl;
			if (key == 5) {
				//std::cout << "trying to send mouse button X1" << std::endl;
				PostMessage(hwnd, WM_XBUTTONDOWN, MK_XBUTTON1 | 0x00010000, 0);
			}
			else if (key == 6) {
				//std::cout << "trying to send mouse button X2" << std::endl;
				PostMessage(hwnd, WM_XBUTTONDOWN, MK_XBUTTON2 | 0x00020000, 0);
			}
		}
		else {
			//std::cout << key << std::endl;
			PostMessage(hwnd, WM_KEYDOWN, key, 0);
		}


		// uping all modifiers for now, so that RKey can go back to it's original behavior (this shit doesn't work for left vs right mods)
		/*PostMessage(hwnd, WM_KEYUP, 0x10, 0);
		PostMessage(hwnd, WM_KEYUP, 0x11, 0);
		PostMessage(hwnd, WM_KEYUP, 0x12, 0);
		PostMessage(hwnd, WM_KEYUP, 0x10, 0);
		PostMessage(hwnd, WM_KEYUP, 0x11, 0);
		PostMessage(hwnd, WM_KEYUP, 0x12, 0);*/

		if (lCtrl) {
			PostMessage(hwnd, WM_KEYUP, 0xA2, 0);
		}
		if (rCtrl) {
			PostMessage(hwnd, WM_KEYUP, 0xA3, 0);
		}
		if (lShift) {
			PostMessage(hwnd, WM_KEYUP, 0xA0, 0);
		}
		if (rShift) {
			PostMessage(hwnd, WM_KEYUP, 0xA1, 0);
		}
		if (lAlt) {
			PostMessage(hwnd, WM_KEYUP, 0xA4, 0);
		}
		if (rAlt) {
			PostMessage(hwnd, WM_KEYUP, 0xA5, 0);
		}


		if (key == 5 || key == 6) {
			// mouse buttons
			if (key == 5) {
				PostMessage(hwnd, WM_XBUTTONUP, 0x00010000, 0);
			}
			else if (key == 6) {
				PostMessage(hwnd, WM_XBUTTONUP, 0x00020000, 0);
			}
		}
		else {
			PostMessage(hwnd, WM_KEYUP, key, 0);
		}

	}
};

double GameProcess::GetDoubleValue() {
	double value;
	COLORREF color = GetColorRefWin10();

	int Red = (int)GetRValue(color);
	int Blue = (int)GetBValue(color);
	int Green = (int)GetGValue(color);

	value = Red * 65536 + Green * 256 + Blue;
	//std::cout << "using pixel value: " << value << std::endl;
	return value;
};

void GameProcess::DoRedKeyPress(int key, bool rCtrl, bool rShift) {
	DoBlueKeyPress(key, false, rCtrl, false, rShift, false, true);

};

void GameProcess::ParseDoubleAndSend(double val) {
	int number = (int)val;

	int Red = (number & 0xFF0000) >> 16;
	int Blue = number & 0xFF;
	int green = (number & 0xFF00) >> 8;




	// it's in this order because wow requires modifiers to be "alt-ctrl-shift"
	bool LAlt = ((green & 0x1) > 0);		// hex of 00000001
	bool RAlt = ((green & 0x2) > 0);		// hex of 00000010
	bool LCtrl = ((green & 0x4) > 0);		// hex of 00000100
	bool RCtrl = ((green & 0x8) > 0);		// hex of 00001000
	bool LShift = ((green & 0x10) > 0);		// hex of 00010000
	bool RShift = ((green & 0x20) > 0);		// hex of 00100000
	bool RedCtrl = ((green & 0x40) > 0);	// hex of 01000000
	bool RedShift = ((green & 0x80) > 0);	// hex of 10000000

											//std::cout << (int)pixel << std::endl;

											// verifies and reassigns at the same time
	DoRedKeyPress(Red, RedCtrl, RedShift);		// this uses right modifiers and actually sends them with alt always down
	DoBlueKeyPress(Blue, LCtrl, RCtrl, LShift, RShift, LAlt, RAlt);
};