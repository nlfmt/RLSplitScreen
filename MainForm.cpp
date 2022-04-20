#include "common.h"
#include "MainForm.h"

namespace RLSplitScreen
{
	void MainForm::log(const char* msg) {
		String^ str = gcnew String(msg);
		this->logs->AppendText(str + "\r\n");
	}

	void MainForm::log(std::string msg) {
		String^ str = gcnew String(msg.c_str());
		this->logs->AppendText(str + "\r\n");
	}

	System::Void MainForm::btn_enable_Click(System::Object^ sender, System::EventArgs^ e) {
		enableSplitScreen(this);
	}

	System::Void MainForm::btn_disable_Click(System::Object^ sender, System::EventArgs^ e)
	{
		disableSplitScreen(this);
	}


	System::Void MainForm::TitleBar_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		dragging = true;
		offset.X = e->X;
		offset.Y = e->Y;
	}

	System::Void MainForm::TitleBar_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (dragging)
		{
			Point currentScreenPosition = PointToScreen(Point(e->X, e->Y));
			Location = Point(currentScreenPosition.X - offset.X, currentScreenPosition.Y - offset.Y);
		}
	}

	System::Void MainForm::TitleBar_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		dragging = false;
	}

	System::Void MainForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		quit();
	}
}