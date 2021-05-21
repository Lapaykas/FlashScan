#include "windows.h"
#include <string>
#include "DataBase.h"
#include "resource.h"

ATOM     AddWindowForScroll(const std::wstring&& windowClassName, const std::wstring&& windowTitle, HWND hParentHandle, const WNDPROC callback);
LRESULT CALLBACK    WndProcForWindowOfScroll(HWND, UINT, WPARAM, LPARAM);

