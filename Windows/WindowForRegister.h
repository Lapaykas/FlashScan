#include <windows.h>
#include "string"
#include "../Common.h"
#include "../Resource.h"
#include "../Func.h"
#include <vector>
#include "ClassName.h"


ATOM    RegWindowForRegisters(HINSTANCE hInstance);
HWND	CreateWindowForRegister();
LRESULT CALLBACK    WndProcForWindowOfRegister(HWND, UINT, WPARAM, LPARAM);


//hWindowRegister = CreateWindowW(windowClassName.c_str(), windowTitle.c_str(), WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME, 30, 40, 500, 200, nullptr, nullptr, nullptr, params);