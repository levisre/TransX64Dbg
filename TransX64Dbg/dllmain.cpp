// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#pragma region Declaration
HMODULE _dllHandle;
int g_plugHandle;
HWND hwndDlg = 0;
int hMenu;
#define PLUGIN_NAME "Transx64Dbg"
#define PLUGIN_VER 001
#define MENU_ABOUT 0
#define COMMAND "translv"
#pragma endregion

#pragma region MainPluginProc

DLL_EXPORT bool pluginit(PLUG_INITSTRUCT* initStruct)
{
	strcpy_s(initStruct->pluginName, PLUGIN_NAME);
	initStruct->pluginVersion = PLUGIN_VER;
	initStruct->sdkVersion = PLUG_SDKVERSION;
	g_plugHandle = initStruct->pluginHandle;
	_plugin_registercommand(g_plugHandle, COMMAND, (CBPLUGINCOMMAND)cbTransProc,false);
	_plugin_registercallback(g_plugHandle, CB_MENUENTRY, (CBPLUGIN)cbMenuCallback);
	return true;
}

DLL_EXPORT bool plugstop()
{
	_plugin_menuclear(hMenu);
	_plugin_unregistercallback(g_plugHandle, CB_MENUENTRY);
	_plugin_unregistercommand(g_plugHandle, COMMAND);
	return true;

}
DLL_EXPORT void plugsetup(PLUG_SETUPSTRUCT* setupStruct)
{
	hwndDlg = setupStruct->hwndDlg;
	hMenu = setupStruct->hMenu;
	_plugin_menuaddentry(hMenu, MENU_ABOUT, "About & Help");
	loadOpacity();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		_dllHandle = hModule;
	}
	return TRUE;
}
#pragma endregion