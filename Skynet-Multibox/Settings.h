#pragma once

#include "stdafx.h"
#include "INIReader.h"

/*PixelReadDelay = reader.GetInteger("Delays", "PixelReadDelay", 50);
SendKeyDelay = reader.GetInteger("Delays", "SendKeyDelay", 50);
ControllerRunDelay = reader.GetInteger("Delays", "ControllerRunDelay", 10);

ScanWindowsFrequencySeconds = reader.GetReal("Scanning", "ScanWindowsFrequencySeconds", 10.0);

x = reader.GetInteger("Coordinates", "x", 10);
y = reader.GetInteger("Coordinates", "y", 30);*/



class Settings {
public:
	static int PixelReadDelay;
	static int SendKeyDelay;
	static int ControllerRunDelay;
	static double ScanWindowsFrequencySeconds;
	static int x, y;

	static bool MemoryReadingEnabled;

	static void LoadSettings() {


		INIReader reader("Settings.ini");

		if (reader.ParseError() < 0) {
			std::cout << "Can't load 'Settings.ini'\nLoading Defaults\n";
			PixelReadDelay = 50;
			SendKeyDelay = 49;
			ControllerRunDelay = 50;
			ScanWindowsFrequencySeconds = 10;
			x = 10;
			y = 30;
			MemoryReadingEnabled = false;

			std::cout << "Would you like to generate a default Settings.ini file [y/n]?";
			char input = _getch();
			if (input == 'y' || input == 'Y') {
				std::cout << input << "\nGenerating....";
				CreateSettingsFile();
				std::cout << "Done.\n";
			}
			else {
				std::cout << "\nFine!" << std::endl;
			}
		}
		else {

			PixelReadDelay = reader.GetInteger("Delays", "PixelReadDelay", 50);
			SendKeyDelay = reader.GetInteger("Delays", "SendKeyDelay", 50);
			ControllerRunDelay = reader.GetInteger("Delays", "ControllerRunDelay", 10);

			ScanWindowsFrequencySeconds = reader.GetReal("Scanning", "ScanWindowsFrequencySeconds", 10.0);

			x = reader.GetInteger("Coordinates", "x", 10);
			y = reader.GetInteger("Coordinates", "y", 30);

			MemoryReadingEnabled = reader.GetBoolean("Memory", "Enabled", false);
		}

		std::cout << "Reading pixel at " << x << ", " << y << std::endl;
	};

private:
	static void CreateSettingsFile() {
		std::ofstream myfile;
		myfile.open("Settings.ini");
		myfile << "[Delays]\n";
		myfile << "PixelReadDelay=50\n";		// ms, frequency with which to read pixels, 
		myfile << "SendKeyDelay=50\n";			// ms, how long to avoid sending a keypress to each window after sending one
		myfile << "ControllerRunDelay=10\n";	// s, unused?
		myfile << "PostActionDelay=800\n";		// ms, soon as the pixel changes from a colour to black, it delays for this duration (could use a tiny number to account for stop casting / cast while moving stuff, or a large number to minimise performance hit), maybe could make this number change based on number of windows active?

		myfile << "\n[Scanning]\n";
		myfile << "ScanWindowsFrequencySeconds=10.0\n";		// s

		myfile << "\n[Coordinates]\n";
		myfile << "x=1\n";
		myfile << "y=1\n";

		myfile << "\n[Memory]\n";
		myfile << "Enabled=false\n";

		myfile.close();
	};
};


/*enum EnumSleeps {
PixelReadDelay = 50,
SendKeyDelay = 49,
ControllerRunDelay = 10
};*/