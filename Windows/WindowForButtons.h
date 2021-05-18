#include "windows.h"
#include <string>
#include "../DataBase.h"
#include "../resource.h"
#include "../Common.h"
#include "WindowForRegister.h"
#include "ClassName.h"
#include "../Common.h"
#include "../Func.h"

ATOM     RegWindowForButtons(HINSTANCE hInstance);
HWND	 CreateWindowForButtons(HINSTANCE hInstance, HWND hWndParent);
LRESULT CALLBACK    WndProcForWindowOfButtons(HWND, UINT, WPARAM, LPARAM);

//hWindowButton = CreateWindowW(windowClassName.c_str(), windowTitle.c_str(), WS_CHILDWINDOW, 0, 0, 400, 80, hParentHandle, nullptr, params->hInst, params);
