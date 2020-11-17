#pragma once

#include "stdafx.h"

class KeySender {
public:
	static void DoPixelProcess(HWND hwnd, COLORREF pixel);
	static void IsValidKey(int &key, bool &alt, bool &ctrl, bool &shift);

	static void DoValidKeyPress(HWND hwnd, int key, bool alt, bool ctrl, bool shift);


};