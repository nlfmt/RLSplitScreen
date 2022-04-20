#pragma once
#include <Windows.h>
#include <string>

namespace RLSplitScreen
{
	ref class MainForm;
}

std::string getDocumentsFolder(RLSplitScreen::MainForm^ app);
void enableSplitScreen(RLSplitScreen::MainForm^ app);
void disableSplitScreen(RLSplitScreen::MainForm^ app);

void quit();