#include "common.h"
#include "monitor.h"


static float aspect_ratio;
static bool compatible = true;
static std::vector<Monitor> monitors = {{ 0, 0, "" }, { 0, 0, "" }};


std::vector<Monitor> getMonitors()
{
	getMonitorInfo();
	return monitors;
}

bool isCompatible()
{
	return compatible;
}


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
		monitors[0] = { width, height };

	}
	else
	{
		if (abs(ar - aspect_ratio) > 0.0001) compatible = false;

		monitors[1] = { width, height };
		return FALSE;
	}

	return TRUE; // Continue enumerating
}


void getMonitorInfo()
{
	// Get monitor resolutions
	EnumDisplayMonitors(0, 0, MonitorEnumProc, 0);
	if (!compatible) return;


	// get device names to set their device modes later
	DISPLAY_DEVICEA dev;
	ZeroMemory(&dev, sizeof(DISPLAY_DEVICEA));
	dev.cb = sizeof(DISPLAY_DEVICEA);

	for (int i = 0; EnumDisplayDevicesA(NULL, i, &dev, 0); i++) {
		if (dev.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
			memcpy(monitors[i].name, dev.DeviceName, sizeof(dev.DeviceName));
	}
}