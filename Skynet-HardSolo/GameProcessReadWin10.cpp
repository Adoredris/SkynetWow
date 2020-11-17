#include "stdafx.h"
#include "GameProcess.h"

COLORREF GameProcess::GetColorRefWin10() {
	RECT rct;
	GetWindowRect(hwnd, &rct);
	COLORREF cColour = 0;

	if (rct.left < -10000 || rct.left > 10000) {
		return cColour;
	}
	WINDOWINFO wInfo;
	GetWindowInfo(hwnd, &wInfo);
	int x = rct.left + 1 + (wInfo.rcClient.left - wInfo.rcWindow.left);
	int y = rct.top + 1 + (wInfo.rcClient.top - wInfo.rcWindow.top);

	HDC hDC;
	if ((hDC = GetDC(NULL)) != NULL) {
		BOOL bOk = FALSE;
		HBITMAP hImage = NULL;

		if ((hImage = CreateCompatibleBitmap(hDC, 1, 1)) != NULL) {

			HDC hMemDC;
			if ((hMemDC = CreateCompatibleDC(hDC)) != NULL) {
				SelectObject(hMemDC, hImage);


				BitBlt(hMemDC, 0, 0, 1, 1, hDC, x, y, SRCCOPY);

				cColour = GetPixel(hMemDC, 0, 0);

				DeleteDC(hMemDC);

			}
			DeleteObject(hImage);
		}
		ReleaseDC(hwnd, hDC);

	}
	return cColour;
};