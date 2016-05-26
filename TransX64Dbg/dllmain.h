#pragma once
#ifndef _DLLMAIN_H
#define _DLLMAIN_H

#include <Windows.h>
#include "pluginsdk\_plugins.h"

#ifndef DLL_EXPORT
#define DLL_EXPORT _declspec(dllexport)
#endif // DLL_EXPORT

extern int g_plugHandle;
extern HWND hwndDlg;

#ifdef __cplusplus
extern "C"
{
#endif
	DLL_EXPORT bool pluginit(PLUG_INITSTRUCT* initStruc);
	DLL_EXPORT bool plugstop();
	DLL_EXPORT void plugsetup(PLUG_SETUPSTRUCT* setupStruct);
#ifdef __cplusplus
}
#endif

#endif // _DLLMAIN_H
