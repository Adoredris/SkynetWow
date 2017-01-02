#include "stdafx.h"
#include "GameWindow.h"

std::chrono::milliseconds GameWindow::delayAfterSpell = std::chrono::milliseconds(500);

std::chrono::milliseconds GameWindow::offDelay = std::chrono::milliseconds(1000);
std::chrono::milliseconds GameWindow::deadDelay = std::chrono::milliseconds(5000);
//std::chrono::milliseconds GameWindow::delayBetweenClicks = std::chrono::milliseconds(50);
int GameWindow::delayBetweenClicks = 50;
std::chrono::milliseconds GameWindow::delayAfterNoSpell = std::chrono::milliseconds(100);

int GameWindow::windows7 = false;

void GameWindow::Stop() {
	if (this->pixelThread.joinable()) {
		this->pixelThread.join();
	}
};

void GameWindow::PixelProcess() {
	//std::chrono::time_point<std::chrono::system_clock> before = std::chrono::system_clock::now();		// remove later
	//COLORREF pixel = PixelReader::ReadPixel(hwnd);
	//std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

	// remove later
	//std::chrono::duration<double> timeDifference = now - before;
	//std::cout << "Time to read pixel = " << timeDifference.count() << std::endl;

	//bool needToSpam = false;
	//if (prevColour != pixel) {
	//	needToSpam = true;
	//}
	//else {
	//	std::chrono::duration<double> timeDifference = now - lastSpamTime;
	//	if (timeDifference.count() > repeatSpamTime) {
	//		needToSpam = true;
	//	}
	//}

	//if (needToSpam) {
		//std::chrono::time_point<std::chrono::system_clock> a = std::chrono::system_clock::now();
		//KeySender::DoPixelProcess(hwnd, pixel);

		//lastSpamTime = now;

		//prevColour = pixel;

		//std::chrono::time_point<std::chrono::system_clock> b = std::chrono::system_clock::now();
		//std::chrono::duration<double> timeDifference = b - a;
		//std::cout << "Time to read pixel = " << timeDifference.count() << std::endl;

		// some delay after posting the spam
		//Sleep(Settings::SendKeyDelay);
	//}

};

void GameWindow::DoProcessing() {
	//std::cout << "doprocessing\n";
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	if (now > nextScanTime) {
		while (KeyStateFreezing::IsModifierDown()) {
			Sleep(50);
		}
		if (!running) {
			if (pixelThread.joinable()) {
				pixelThread.join();
			}
			//std::cout << "thread started\n";
			running = true;
			pixelThread = std::thread(std::mem_fn(&GameWindow::Run), this);

			Sleep(50);
			// if pixel is black, then 'something' should be X
			// if pixel is non-black, then 'something' should be Y

			// processing will involve starting a thread, not actually doing the process

			//nextScanTime = now + something;
		}
	}

	// some delay after each pixel read
	//Sleep(Settings::PixelReadDelay);		// this delay shouldn't be there since DoProcessing has its own
};



void GameWindow::Run() {
	bool ran = false;
	COLORREF color = GetColorRef();
	while (color != 0) {
		if (KeyStateFreezing::IsModifierDown()) {
			ran = false;
			std::cout << "skipping\n";
			break;
		}
		ran = true;
		if ((int)GetBValue(color) == 255) {
			nextScanTime = std::chrono::system_clock::now() + offDelay;
			running = false;
			return;
		}
		// there was a point to this I swear
		//else if ((int)GetRValue(color) == 255) {
		//	nextScanTime = std::chrono::system_clock::now() + deadDelay;
		//	running = false;
		//	return;
		//}
		ParsePixelAndSend(color);
		Sleep(delayBetweenClicks);
		color = GetColorRef();
	}
	if (ran) {
		//std::cout << "not reading for a while\n";
		nextScanTime = std::chrono::system_clock::now() + delayAfterSpell;
	}
	else {
		nextScanTime = std::chrono::system_clock::now() + delayAfterNoSpell;
	}
	//std::cout << "thread ended\n";
	running = false;
};

void GameWindow::DoBlueKeyPress(int key, bool lCtrl, bool rCtrl, bool lShift, bool rShift, bool lAlt, bool rAlt) {
	if (key == VK_ESCAPE ||
		key == VK_RETURN ||
		key == VK_SNAPSHOT ||
		key == VK_DELETE && lCtrl && lAlt ||
		key == VK_F4 && (lAlt || rAlt)  ||
		key == 0 || key == 0xFF) {
	}
	else {
		std::cout << lCtrl << rCtrl << lShift << rShift << lAlt << rAlt << std::endl;

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
				std::cout << "trying to send mouse button X1" << std::endl;
				PostMessage(hwnd, WM_XBUTTONDOWN, MK_XBUTTON1 | 0x00010000, 0);
			}
			else if (key == 6) {
				std::cout << "trying to send mouse button X2" << std::endl;
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

COLORREF GameWindow::GetColorRef() {
	if (windows7) {
		//std::cout << "using win7 mode\n";
		return GetColorRefWin7();
	}
	else {
		//std::cout << "using win10 mode\n";
		return GetColorRefWin10();
	}
};

void GameWindow::DoRedKeyPress(int key, bool rCtrl, bool rShift) {
	DoBlueKeyPress(key, false, rCtrl, false, rShift, false, true);

};

void GameWindow::ParsePixelAndSend(COLORREF pixel) {
	int Red = (int)GetRValue(pixel);
	int Blue = (int)GetBValue(pixel);
	int green = (int)GetGValue(pixel);

	


	// it's in this order because wow requires modifiers to be "alt-ctrl-shift"
	bool LAlt = ((green & 0x1) > 0);		// hex of 00000001
	bool RAlt = ((green & 0x2) > 0);		// hex of 00000010
	bool LCtrl = ((green & 0x4) > 0);		// hex of 00000100
	bool RCtrl = ((green & 0x8) > 0);		// hex of 00001000
	bool LShift = ((green & 0x10) > 0);		// hex of 00010000
	bool RShift = ((green & 0x20) > 0);		// hex of 00100000
	bool RedCtrl = ((green & 0x40) > 0);	// hex of 01000000
	bool RedShift = ((green & 0x80) > 0);	// hex of 10000000

	std::cout << (int)pixel << std::endl;

									 // verifies and reassigns at the same time
	DoRedKeyPress(Red, RedCtrl, RedShift);		// this uses right modifiers and actually sends them with alt always down
	DoBlueKeyPress(Blue, LCtrl, RCtrl, LShift, RShift, LAlt, RAlt);
};