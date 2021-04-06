// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include "KeyManager.h"
#include "Singleton.h"
using namespace std;

#define WINSIZE_X	1505	//1080
#define WINSIZE_Y	719		//720

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, * PFPOINT;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;