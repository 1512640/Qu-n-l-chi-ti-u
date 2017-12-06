// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <Windows.h>
#include <windows.h>
#include <windowsx.h>
#include <Commctrl.h>
#pragma comment(lib, "comctl32.lib")

#include <ObjIdl.h> 
#include <gdiplus.h>
#pragma comment (lib,"gdiplus.lib")
using namespace Gdiplus;

#include <iostream>
#include <string>
#include <fstream>
#include <fcntl.h> //_O_WTEXT
#include <io.h>    //_setmode()
#include <locale>
#include <codecvt> //possible C++11?
using namespace std;
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
