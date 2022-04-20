#pragma once
#include <Windows.h>
#include <string>

namespace RLSplitScreen
{
	ref class MainForm;
}

std::string getDocumentsFolder();
std::string getAppdataFolder();
void enableSplitScreen(RLSplitScreen::MainForm^ app);
void disableSplitScreen(RLSplitScreen::MainForm^ app);

void quit();

std::string operator+(int, std::string);
std::string operator+(std::string, int);