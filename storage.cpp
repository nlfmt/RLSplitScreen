#include "common.h"
#include "storage.h"

#include <filesystem>


namespace fs = std::filesystem;


const std::string monitorFile = "\\RLSplitScreen\\monitors.bin";
static std::vector<Monitor> monitors = {{ 0, 0, "" }, { 0, 0, "" }};


std::vector<Monitor> getStoredMonitors()
{
	return monitors;
}

void loadMonitors()
{
	const std::string appdata = getAppdataFolder();
	if (appdata == "") return;

	std::ifstream file;
	file.open(appdata + monitorFile, std::ios::binary);

	if (file.is_open())
	{
		file.read(reinterpret_cast<char*>(&monitors[0]), sizeof(Monitor) * 2);
		file.close();
	}
}

// store monitor resolutions in file to restore them after restart
void saveMonitors(std::vector<Monitor> mons)
{
	monitors = mons;
	const std::string appdata = getAppdataFolder();
	if (appdata == "") return;

	CreateDirectoryA((appdata + "\\RLSplitScreen").c_str(), nullptr);

	std::ofstream file;
	file.open(appdata + monitorFile, std::ios::binary);

	if (file.is_open())
	{
		file.write(reinterpret_cast<char*>(&mons[0]), sizeof(Monitor) * 2);
		file.close();
	}
}