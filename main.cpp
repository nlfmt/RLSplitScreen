/**
 * Rocket League Split Screen Manager
 * made by Tom F. (https://github.com/nlfmt)
 *
 * This simple program sets your screen resolution and edits your rocket league config
 * to create a rocket league window that spans over multiple monitors.
 *
 * License: MIT
 */

#include "MainForm.h"

#include <iostream>

using namespace System;
using namespace System::Windows::Forms;

int main()
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	RLSplitScreen::MainForm form;
	Application::Run(% form);

	return 0;
}