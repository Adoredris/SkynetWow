#include "stdafx.h"
#pragma once

class KeyStateFreezing {

public:
	static bool IsModifierDown() {
		//std::cout << GetKeyState(0xA0) << std::endl; 
		if (
			/*GetKeyState(0xA2) < 0				// lcontrol
			|| */GetKeyState(0xA0) < 0			// lshift
			|| GetKeyState(0xA4) < 0			// lalt
			|| GetKeyState(0x5B) < 0			// lwin
			//|| GetKeyState(0xA3) < 0			// rcontrol
			|| GetKeyState(0xA1) < 0			// rshift
			|| GetKeyState(0xA5) < 0			// ralt
			|| GetKeyState(0x5C) < 0)			// rwin
			return true;

		return false;
	}
};