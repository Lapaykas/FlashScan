#include <windows.h>
#include "string"
#include "Common.h"
#include "Resource.h"
#include "Func.h"
#include <vector>

HWND     AddWindowForRegisters(const std::wstring&& windowClassName, const std::wstring&& windowTitle, HWND hParentHandle, const WNDPROC callback);
LRESULT CALLBACK    WndProcForWindowOfRegister(HWND, UINT, WPARAM, LPARAM);