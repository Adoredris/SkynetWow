#include "stdafx.h"
#include "GameWindow.h"

COLORREF GameWindow::GetColorRefWin7() {
	COLORREF cColour = 0;

	//std::chrono::duration<double> timeDifference;
	//std::chrono::time_point<std::chrono::system_clock> before = std::chrono::system_clock::now();		// remove later
	HDC hDC;
	if ((hDC = GetDC(hwnd)) != NULL) {
		BOOL bOk = FALSE;
		HBITMAP hImage = NULL;

		if ((hImage = CreateCompatibleBitmap(hDC, 1, 1)) != NULL) {

			HDC hMemDC;
			if ((hMemDC = CreateCompatibleDC(hDC)) != NULL) {
				SelectObject(hMemDC, hImage);

				BitBlt(hMemDC, 0, 0, 1, 1,
					hDC, Settings::x, Settings::y, SRCCOPY);

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