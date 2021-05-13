#include "windows.h"
#include <string>
#include "DataBase.h"
#include "resource.h"
#include "Common.h"
#include "WindowForRegister.h"

ATOM     AddWindowForButtons(const std::wstring&& windowClassName, const std::wstring&& windowTitle, HWND hParentHandle, const WNDPROC callback);
LRESULT CALLBACK    WndProcForWindowOfButtons(HWND, UINT, WPARAM, LPARAM);


