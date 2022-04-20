#include "common.h"
#include "MainForm.h"

#include <Windows.h>
#include <ShlObj.h>



void quit()
{
	System::Windows::Forms::Application::Exit();
}


std::string getDocumentsFolder()
{
	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	if (result != S_OK) return "";
	return std::string(my_documents);
}


std::string getAppdataFolder()
{
	CHAR appdata[MAX_PATH];
	HRESULT result = SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, appdata);

	if (result != S_OK) return "";
	return std::string(appdata);
}