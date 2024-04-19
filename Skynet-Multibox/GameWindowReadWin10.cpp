#include "stdafx.h"
#include "GameWindow.h"

COLORREF GameWindow::GetColorRefWin10(bool right) {
	RECT rct;
	GetWindowRect(hwnd, &rct);
	COLORREF cColour = 0;

	
	
	
	
	//std::cout << wInfo.dwWindowStatus << std::endl;

	if (rct.left < -10000 || rct.left > 10000) {
		return cColour;
	}
	WINDOWINFO wInfo;
	GetWindowInfo(hwnd, &wInfo);
	int x = right ? (rct.right - 1 + (wInfo.rcClient.right - wInfo.rcWindow.right)) : (rct.left + 0 + (wInfo.rcClient.left - wInfo.rcWindow.left));
	/*int x = rct.left + 0 + (wInfo.rcClient.left - wInfo.rcWindow.left);
	std::cout << "rct.left: " << rct.left << std::endl;
	std::cout << "rcClient.left: " << wInfo.rcClient.left << std::endl;
	std::cout << "rcWindow.left: " << wInfo.rcWindow.left << std::endl;
	std::cout << "x: " << x << std::endl;*/

	/*int x = rct.right - 1 + (wInfo.rcClient.right - wInfo.rcWindow.right);
	std::cout << "rct.right: " << rct.right << std::endl;
	std::cout << "rcClient.right: " << wInfo.rcClient.right << std::endl;
	std::cout << "rcWindow.right: " << wInfo.rcWindow.right << std::endl;
	std::cout << "x: " << x << std::endl;*/

	int y = rct.top + 0 + (wInfo.rcClient.top - wInfo.rcWindow.top);
	
	//std::cout << GetForegroundWindow() << std::endl;
	
	/*if (GetForegroundWindow() != hwnd) {
		HWND hwndNext = GetNextWindow(hwnd, GW_HWNDPREV);
		//int i = 1;
		while (hwndNext != 0) {
			WINDOWINFO wNextInfo;
			GetWindowInfo(hwndNext, &wNextInfo);
			RECT nextrct = wNextInfo.rcWindow;
			WINDOWPLACEMENT wp;
			GetWindowPlacement(hwndNext, &wp);
			CHAR windowText[32];
			int classSize = GetWindowTextA(hwndNext, windowText, 32);
			if (classSize == 0)
			{
				break;
			}

			if (wp.showCmd == SW_SHOWMAXIMIZED) {
				//std::cout << "showCmd: " << wp.showCmd << " - " << windowText << std::endl;
				nextrct.left = nextrct.left + wNextInfo.cxWindowBorders;
				nextrct.right = nextrct.right - wNextInfo.cxWindowBorders;
				nextrct.top = nextrct.top + wNextInfo.cyWindowBorders;
				nextrct.bottom = nextrct.bottom - wNextInfo.cyWindowBorders;
			}
			else if (wp.showCmd == SW_SHOWMINIMIZED) {
				std::cout << windowText << std::endl;
				return cColour;
			}
			else 
			{
				//SW_SHOW
				//std::cout << windowText << " nextrct.left: " << nextrct.left << std::endl;
				//std::cout << windowText << " nextrct.right: " << nextrct.right << std::endl;
			}
			

			if (x > nextrct.left && x < nextrct.right &&
				y > nextrct.top && y < nextrct.bottom) {
				if (strcmp(windowText,"InputDirectorClipboardClientWin") == 0) {
					//std::cout << wNextInfo.cxWindowBorders << ", " << wNextInfo.cyWindowBorders << std::endl;
					std::cout << x << ", " << y << "Allowing colour through " << std::string(windowText) << " - " << classSize << std::endl;
					//std::cout << nextrct.left << ", " << nextrct.right << std::endl;
					//std::cout << nextrct.top << ", " << nextrct.bottom << std::endl;
					break;
				}
				else {
					std::cout << x << ", " << y << " Skipping cause overlap " << std::string(windowText) << " - " << classSize << std::endl;
					std::cout << "style: " << std::hex << wNextInfo.dwStyle << ", ExStyle: " << std::hex << wNextInfo.dwExStyle << std::endl;
					return cColour;
				}
			} 
			//i++;
			hwndNext = GetNextWindow(hwndNext, GW_HWNDPREV);
		}
	}*/

	//std::cout << "left: " << rct.left << ", right: " << rct.right << std::endl;
	//if (rct.left < 0) { rct.left = 0; };
	//if (rct.top < 0) { rct.top = 0; };
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
				//std::cout << "boo" << std::endl;
				
				
				//BitBlt(hMemDC, 0, 0, 1, 1,hDC, rct.left + 1 + (wInfo.rcClient.left - wInfo.rcWindow.left), rct.top + 1 + (wInfo.rcClient.top - wInfo.rcWindow.top), SRCCOPY);
				BitBlt(hMemDC, 0, 0, 1, 1, hDC, x, y, SRCCOPY);
				//BitBlt(hMemDC, 0, 0, 1, 1, hDC, 1, 1, SRCCOPY);

				cColour = GetPixel(hMemDC, 0, 0);
				//std::cout << cColour << std::endl;

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