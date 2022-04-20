#include <Windows.h>
#include <ShlObj.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

#include "common.h"
#include "MainForm.h"


namespace fs = std::filesystem;


void quit()
{
	System::Windows::Forms::Application::Exit();
}


std::string getDocumentsFolder(RLSplitScreen::MainForm^ app)
{
	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	if (result != S_OK) {
		app->log("Error: Failed to get Documents folder.");
	}
	return std::string(my_documents);
}


struct Monitor
{
	int width;
	int height;
	int top;
	CHAR name[32];
};

float aspect_ratio;
bool compatible = true;
Monitor monitors[2];

BOOL MonitorEnumProc(HMONITOR hMon, HDC hdc, LPRECT lpRect, LPARAM lParam)
{
	MONITORINFO info;
	info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfoA(hMon, &info);
	int width = info.rcMonitor.right - info.rcMonitor.left;
	int height = info.rcMonitor.bottom - info.rcMonitor.top;
	float ar = (float)width / (float)height;

	if (!aspect_ratio)
	{
		aspect_ratio = ar;
		monitors[0] = { width, height, info.rcMonitor.top };
		
	} else
	{
		if (abs(ar - aspect_ratio) > 0.0001) compatible = false;

		monitors[1] = { width, height, info.rcMonitor.top };
		return FALSE;
	}

	return TRUE; // Continue enumerating
}


void enableSplitScreen(RLSplitScreen::MainForm^ app)
{
	// check if user has exactly two monitors
	app->log("Checking Monitor count...");
	if (GetSystemMetrics(SM_CMONITORS) != 2)
	{
		app->log("Error: You need two monitors to use SplitScreen.");
		return;
	}


	// get all monitor resolutions and check if they have the same aspect ratio
	EnumDisplayMonitors(0, 0, MonitorEnumProc, 0);
	if (!compatible)
	{
		app->log("Error: Your monitors do not have the same aspect ratio.");
		return;
	}


	// get device names to set their device modes later
	DISPLAY_DEVICEA dev;
	ZeroMemory(&dev, sizeof(DISPLAY_DEVICEA));
	dev.cb = sizeof(DISPLAY_DEVICEA);

	for (int i = 0; EnumDisplayDevicesA(NULL, i, &dev, 0); i++) {
		if (i == 1) memcpy(monitors[i].name, dev.DeviceName, sizeof(dev.DeviceName));
	}


	// try setting the same resolution for both monitors
	int rlwidth = monitors[0].width * 2, rlheight = monitors[0].height;

	if (monitors[0].width != monitors[1].width || monitors[0].height != monitors[1].height)
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
						devmode.dmPosition.y = 0; // monitors[2 - m - 1].top;
						devmode.dmPosition.x = monitors[m].width;
						devmode.dmFields |= DM_POSITION;
					}
					int err = ChangeDisplaySettingsExA(monitors[m].name, &devmode, NULL, 0, NULL);

					if (err) app->log(std::string("Error: Couldn't set display mode.") + std::to_string(err));
					else
					{
						success = true;

						std::string msg = "Set Resolution to " + std::to_string(desired_width) + "x" + std::to_string(desired_height);
						app->log(msg.c_str());

						rlwidth = desired_width * 2;
						rlheight = desired_height;
						break;
					}
				}
			}
			if (success) break;
		}

		if (!success)
		{
			app->log("Error: Couldn't find a suitable display mode.\nTry to make your displays the same resolution.");
			return;
		}
	}


	const std::string configFileName = getDocumentsFolder(app) + "\\My Games\\Rocket League\\TAGame\\Config\\TASystemSettings.ini";
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

	if (!configFile.is_open() || !backupFile.is_open()) {
		app->log("Error: Failed to open config/backup file.");
		return;
	}

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
	app->log("Success!\r\nYou can now restart Rocket League.");
}

void disableSplitScreen(RLSplitScreen::MainForm^ app)
{
	app->log("Restoring display resolutions...");

	EnumDisplayMonitors(0, 0, MonitorEnumProc, 0);
	for (int i=0; i < 2; i++)
	{
		DEVMODEA devmode;
		devmode.dmSize = sizeof(DEVMODEA);

		bool res = EnumDisplaySettingsA(monitors[i].name, 1, &devmode);
		/*for (int m = 1; res; m++)
			res = EnumDisplaySettingsA(monitors[i].name, m, &devmode);*/

		if (!res)
		{
			app->log("Warning: No display mode found for monitor " + std::to_string(i+1) + ".");
			continue;
		}

		int err = ChangeDisplaySettingsExA(monitors[i].name,  &devmode, NULL, 0, NULL);
		if (err) app->log("Warning: Couldn't restore display mode for monitor " + std::to_string(i+1) + ".");
	}

	app->log("Reverting to backed up config file...");

	const std::string configFileName = getDocumentsFolder(app) + "\\My Games\\Rocket League\\TAGame\\Config\\TASystemSettings.ini";
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

	app->log("Done!");
}