#pragma once

#include <vector>
#include <fstream>

typedef struct Monitor
{
	int width;
	int height;
	char name[32];
} Monitor;

void getMonitorInfo();
bool isCompatible();
std::vector<Monitor> getMonitors();