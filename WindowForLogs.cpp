#include "WindowForButtons.h"
#include "WindowForLogs.h"


struct PARAMSSTRUCT {
    HINSTANCE hInst;
    CDataBaseWrapper* BASE;
    HDEVNOTIFY REG_DEVICE;
};

HWND AddWindowForLogs(const std::wstring&& windowClassName, const std::wstring&& windowTitle, HWND hParentHandle, const WNDPROC callback)
{
    // UnregisterClass(windowClassName.c_str(), GetModuleHandle(nullptr));
    PARAMSSTRUCT* params = (PARAMSSTRUCT*)GetWindowLongPtr(hParentHandle, GWLP_USERDATA);
    WNDCLASSEXW WindowForLogs;
    HWND hWindowLogs;

    WindowForLogs.cbSize = sizeof(WNDCLASSEXW);
    WindowForLogs.style = CS_HREDRAW | CS_VREDRAW;
    WindowForLogs.lpfnWndProc = callback;
    WindowForLogs.cbClsExtra = 0;
    WindowForLogs.cbWndExtra = 0;
    WindowForLogs.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    WindowForLogs.hCursor = LoadCursor(nullptr, IDC_ARROW);
    WindowForLogs.hbrBackground = (HBRUSH)(GetStockObject(BLACK_BRUSH));
    WindowForLogs.lpszMenuName = MAKEINTRESOURCEW(NULL);
    WindowForLogs.lpszClassName = windowClassName.c_str();
    WindowForLogs.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    WindowForLogs.hInstance = params->hInst;

    ATOM retValue = RegisterClassExW(&WindowForLogs);
    hWindowLogs = CreateWindowW(windowClassName.c_str(), NULL, WS_CHILDWINDOW | WS_VISIBLE | LBS_DISABLENOSCROLL
		, 0, 90, 400, 300, hParentHandle, (HMENU)IDW_LOG_WINDOW, params->hInst, nullptr);
    ShowWindow(hWindowLogs, SW_SHOWDEFAULT);
    UpdateWindow(hWindowLogs);
    return hWindowLogs;
}

LRESULT CALLBACK WndProcForWindowOfLogs(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
    switch (message)
    {
    case WM_COMMAND:
    {
        
        break;
    }
    break;
    case WM_USER_ADD_STRING_TO_LISTBOX:
    {
      //  SendMessageW(hwndListBox, LB_ADDSTRING, 0, lParam);
    }
    case WM_CREATE:
    {
        break;
    }
    case WM_DEVICECHANGE:
    {
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}