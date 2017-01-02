#include "stdafx.h"
#include "GameWindow.h"


COLORREF GameWindow::GetColorRefWin10() {
	RECT rct;
	GetWindowRect(hwnd, &rct);
	COLORREF cColour = 0;

	if (rct.left < 0) { rct.left = 0; };
	if (rct.top < 0) { rct.top = 0; };
	//std::chrono::duration<double> timeDifference;
	//std::chrono::time_point<std::chrono::system_clock> before = std::chrono::system_clock::now();		// remove later
	HDC hDC;
	if ((hDC = GetDC(NULL)) != NULL) {
		BOOL bOk = FALSE;
		HBITMAP hImage = NULL;

		if ((hImage = CreateCompatibleBitmap(hDC, 1, 1)) != NULL) {

			HDC hMemDC;
			if ((hMemDC = CreateCompatibleDC(hDC)) != NULL) {
				SelectObject(hMemDC, hImage);

				BitBlt(hMemDC, 0, 0, 1, 1,
					hDC, rct.left + Settings::x, rct.top + Settings::y, SRCCOPY);

				cColour = GetPixel(hMemDC, 0, 0);

				DeleteDC(hMemDC);

			}
			DeleteObject(hImage);
		}
		ReleaseDC(hwnd, hDC);

		/*std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
		timeDifference = now - before;
		double diff = timeDifference.count();
		if (diff > 0.01)
		std::cout << "Time to read pixel = " << timeDifference.count() << std::endl;
		*/
	}
	return cColour;
};