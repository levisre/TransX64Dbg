#pragma once
#ifndef _TRANSX64DBG_H
#define _TRANSX64DBG_H
#include <Windows.h>

extern bool cbTransProc(int argc, char* argv[]);
extern void loadOpacity();
extern void cbMenuCallback(CBTYPE type, PLUG_CB_MENUENTRY* info);

#endif // !_TRANSX64DBG_H

