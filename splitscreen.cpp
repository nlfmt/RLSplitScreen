#include <Windows.h>
#include <ShlObj.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

#include "common.h"
#include "monitor.h"
#include "storage.h"
#include "MainForm.h"


namespace fs = std::filesystem;


std::string operator+ (int i, std::string s)
{
	return std::to_string(i) + s;
}
std::string operator+ (std::string s, int i)
{
	return s + std::to_string(i);
}


void enableSplitScreen(RLSplitScreen::MainForm^ app)
{
	// check if user has exactly two monitors
	app->log("Checking Monitor count...");
	if (GetSystemMetrics(SM_CMONITORS) != 2)
		return app->log("Error: You need two monitors to use SplitScreen.");


	// check if all resolutions have the same aspect ratio
	if (!isCompatible())
		return app->log("Error: Your monitors do not have the same aspect ratio.");

	std::vector<Monitor> monitors = getMonitors();

	// try setting the same resolution for both monitors
	int rlwidth = monitors[0].width * 2, rlheight = monitors[0].height;

	if (app->resSetEnabled() && (monitors[0].width != monitors[1].width || monitors[0].height != monitors[1].height))
	{
		app->log("Trying to set the same resolution for both monitors...");
		bool success = false;
		for (int m = 0; m < 2; m++)
		{
			int desired_width = monitors[2 - m - 1].width;
			int desired_height = monitors[2 - m - 1].height;

			for (int i = 0; ; i++)
			{
				DEVMODEA devmode;
				devmode.dmSize = sizeof(DEVMODEA);

				bool res = EnumDisplaySettingsA(monitors[m].name, i, &devmode);
				if (!res) break; // No more modes to enumerate

				if (devmode.dmPelsWidth == desired_width && devmode.dmPelsHeight == desired_height) {
					if (m == 1)
					{
						devmode.dmPosition.y = 0;
						devmode.dmPosition.x = monitors[m].width;
						devmode.dmFields |= DM_POSITION;
					}
					int err = ChangeDisplaySettingsExA(monitors[m].name, &devmode, NULL, 0, NULL);

					if (err) app->log(std::string("Error: Couldn't set display mode.") + err);
					else
					{
						success = true;
						saveMonitors(monitors);

						std::string msg = std::string("Set Resolution to ") + desired_width + "x" + desired_height;
						app->log(msg);

						rlwidth = desired_width * 2;
						rlheight = desired_height;
						break;
					}
				}
			}
			if (success) break;
		}

		if (!success) return app->log("Error: Couldn't find a suitable display mode.\nTry to make your displays the same resolution.");
	}


	const std::string configFileName = getDocumentsFolder() + "\\My Games\\Rocket League\\TAGame\\Config\\TASystemSettings.ini";
	const std::string configFileBackupName = configFileName + ".backup";

	app->log("Backing up config file...");
	// backup current config file
	if (!fs::exists(fs::path(configFileBackupName)) || MessageBoxA(0, "Backup config file already exists. Overwrite?", "Warning", MB_YESNO) == IDYES)
	{
		CopyFileA(configFileName.c_str(), configFileBackupName.c_str(), false);
	}


	// write new config
	app->log("Writing new config file...");

	std::ofstream configFile;
	configFile.open(configFileName);
	
	std::ifstream backupFile;
	backupFile.open(configFileBackupName);

	if (!configFile.is_open() || !backupFile.is_open())
		return app->log("Error: Failed to open config/backup file.");

	std::string line;
	while (std::getline(backupFile, line))
	{
		std::string l = line;
		std::transform(l.begin(), l.end(), l.begin(), ::tolower);

		if (l.rfind("resx=", 0) == 0)
			configFile << "ResX=" << rlwidth << "\n";

		else if (l.rfind("resy=", 0) == 0)
			configFile << "ResY=" << rlheight << "\n";

		else if (l.rfind("fullscreen=", 0) == 0)
			configFile << "Fullscreen=" << "False" << "\n";

		else if (l.rfind("borderless=", 0) == 0)
			configFile << "Borderless=" << "True" << "\n";

		else configFile << line << "\n";
	}
	backupFile.close();
	configFile.close();

	app->log("-------------------------------------------------------------------");
	app->log("Success!\r\n You can now restart Rocket League.");
	app->log("-------------------------------------------------------------------");
}

void disableSplitScreen(RLSplitScreen::MainForm^ app)
{
	if (app->resSetEnabled()) {

		app->log("Restoring display resolutions...");

		std::vector<Monitor> monitors = getMonitors();
		std::vector<Monitor> storedMonitors = getStoredMonitors();

		for (int i = 0; i < 2; i++)
		{
			DEVMODEA devmode;
			ZeroMemory(&devmode, sizeof(DEVMODEA));
			devmode.dmSize = sizeof(DEVMODEA);
			devmode.dmDriverExtra = 0;

			bool res = EnumDisplaySettingsExA(monitors[i].name, ENUM_CURRENT_SETTINGS, &devmode, 0);
			if (devmode.dmPelsWidth != storedMonitors[i].width || devmode.dmPelsHeight != storedMonitors[i].height)
			{
				for (int m = 0; res = EnumDisplaySettingsExA(monitors[i].name, m, &devmode, 0); m++)
				{
					if (devmode.dmPelsWidth == storedMonitors[i].width && devmode.dmPelsHeight == storedMonitors[i].height)
					{
						app->log(std::string("Switched Monitor ") + (i + 1) + " back to " + devmode.dmPelsWidth + "x" + devmode.dmPelsHeight);
						int err = ChangeDisplaySettingsExA(monitors[i].name, &devmode, NULL, 0, NULL);
						if (err) app->log("Warning: Couldn't restore display mode for monitor " + std::to_string(i + 1) + ".");
						break;
					}
				}
				if (!res)
				{
					app->log("Warning: No display mode found for monitor " + std::to_string(i + 1) + ".");
					continue;
				}
			}
		}
	}

	app->log("Reverting to backed up config file...");

	const std::string configFileName = getDocumentsFolder() + "\\My Games\\Rocket League\\TAGame\\Config\\TASystemSettings.ini";
	const std::string configFileBackupName = configFileName + ".backup";

	if (!fs::exists(fs::path(configFileBackupName)))
		return app->log("Error: No backup file found.");

	std::ofstream configFile;
	configFile.open(configFileName);
	std::ifstream backupFile;
	backupFile.open(configFileBackupName);

	configFile << backupFile.rdbuf();
	backupFile.close();
	configFile.close();

	DeleteFileA(configFileBackupName.c_str());

	app->log("-------------------------------------------------------------------");
	app->log("Done!");
	app->log("-------------------------------------------------------------------");
}