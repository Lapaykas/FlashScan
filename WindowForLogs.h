#include "windows.h"
#include <string>
#include "DataBase.h"
#include "resource.h"

HWND     AddWindowForLogs(const std::wstring&& windowClassName, const std::wstring&& windowTitle, HWND hParentHandle, const WNDPROC callback);
LRESULT CALLBACK    WndProcForWindowOfLogs(HWND, UINT, WPARAM, LPARAM);

