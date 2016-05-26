// TransX64Dbg.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#pragma region Declaration
#define MENU_ABOUT 0
#define CONST_MSG "TransX64Dbg Plugin by Levis Nickaster\nUsage: Type command:\n\"translv NUMBER\" where NUMBER is decimal between 0\% and 100\%.\n\"translv off\" to turn off the transparent."
UINT Opacity;
BOOL isStyled=FALSE;
char iniFile[MAX_PATH];
LPCSTR sectName = "Setting", cfgEnabled = "Enabled", cfgOpacityValue = "Value";
#pragma endregion

#pragma region MainCode
void setTransparent()
{
	if (!isStyled)
	{
		SetWindowLong(hwndDlg, GWL_EXSTYLE, GetWindowLong(hwndDlg, GWL_EXSTYLE) | WS_EX_LAYERED);
		isStyled = TRUE;
	}
	SetLayeredWindowAttributes(hwndDlg, 0, Opacity, LWA_ALPHA);
}

void disableTransparent()
{
	//Opacity = 255;
	//setTransparent();
	SetWindowLong(hwndDlg, GWL_EXSTYLE, GetWindowLong(hwndDlg,GWL_EXSTYLE) & ~WS_EX_LAYERED);
	RedrawWindow(hwndDlg, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	WritePrivateProfileStringA(sectName, cfgEnabled, "0", iniFile);
	_plugin_logprintf("TransX64Dbg Disabled!");
}
//Callback Function for command line
bool cbTransProc(int argc, char* argv[])
{
	//_plugin_logprintf("%d", argc);
	if (argc==2)
	{
		if (strcmp(argv[1], "off") == 0)
		{
			//disable Transparent
			disableTransparent();
			return true;
		}
		else
		{
			//Enable Transparent and save setting to file
			WritePrivateProfileStringA(sectName, cfgEnabled, "1", iniFile);
			Opacity = (atoi(argv[1]) * 255) / 100;
			if (Opacity >= 0 && Opacity <= 255)
			{
				_plugin_logprintf("[TransX64Dbg] Setting Opacity value: %d\n", Opacity);
				setTransparent();
				char buffer[10];
				sprintf_s(buffer, "%d", Opacity);
				WritePrivateProfileStringA(sectName, cfgOpacityValue, buffer, iniFile);
				return true;
			}
			else
			{
				_plugin_logprintf("[TransX64Dbg] %d is not a valid value!\n", Opacity);
				return false;
			}
		}
	}
	return false;
}

//Show About Dialog
void cbMenuCallback(CBTYPE type, PLUG_CB_MENUENTRY* info)
{
	switch(info->hEntry)
	{
	case MENU_ABOUT:
		MessageBoxA(hwndDlg, CONST_MSG, "About", MB_OK + MB_ICONINFORMATION);
	}
}

//Self explained
BOOL checkFileExist()
{
	int fAtrrib = GetFileAttributesA(iniFile);
	return(fAtrrib != INVALID_FILE_ATTRIBUTES) && !(fAtrrib&FILE_ATTRIBUTE_DIRECTORY);
}
//Load seved Setting
void loadOpacity()
{
	GetCurrentDirectoryA(MAX_PATH, LPSTR(iniFile));
	strcat_s(iniFile, "\\TransX64Dbg.ini");
	if (!checkFileExist())
	{
		//Create ini File
		_plugin_logputs("[TransX64Dbg] Ini file not Exist! Creating...");
		WritePrivateProfileStringA(NULL, NULL, NULL, iniFile);
		WritePrivateProfileStringA(sectName, cfgEnabled, "0", iniFile);
		WritePrivateProfileStringA(sectName, cfgOpacityValue, "100", iniFile);
	}
	else
	{
		//if ini File is found, reload settings and apply them
		int isEnabled = GetPrivateProfileIntA(sectName, cfgEnabled, 0, iniFile);
		switch (isEnabled)
		{
		case 1:
		{
			_plugin_logputs("[TransX64Dbg] Enabled! Getting Opacity value...");
			Opacity = GetPrivateProfileIntA(sectName, cfgOpacityValue, 0, iniFile);
			_plugin_logprintf("[TransX64Dbg] Opacity Value: %d\n", Opacity);
			setTransparent();
			break;
		}
		case 0:
		{
			disableTransparent();
			break;
		}
		default:
		{
			setTransparent;
			break;
		}
		} 
	}
}
#pragma endregion
