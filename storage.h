#pragma once

#include <vector>
#include "monitor.h"


std::vector<Monitor> getStoredMonitors();

void loadMonitors();

void saveMonitors(std::vector<Monitor> mons);