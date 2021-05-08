#include "WindowForButtons.h"


struct PARAMSSTRUCT {
    HINSTANCE hInst;
    DataBase* BASE;
    HDEVNOTIFY REG_DEVICE;
};

ATOM AddWindowForScroll(const std::wstring&& windowClassName, const std::wstring&& windowTitle, HWND hParentHandle, const WNDPROC callback)
{
    // UnregisterClass(windowClassName.c_str(), GetModuleHandle(nullptr));
    PARAMSSTRUCT* params = (PARAMSSTRUCT*)GetWindowLongPtr(hParentHandle, GWLP_USERDATA);
    WNDCLASSEXW WindowForButtons;
    HWND hWindowButton;

    WindowForButtons.cbSize = sizeof(WNDCLASSEXW);
    WindowForButtons.style = CS_HREDRAW | CS_VREDRAW;
    WindowForButtons.lpfnWndProc = callback;
    WindowForButtons.cbClsExtra = 0;
    WindowForButtons.cbWndExtra = 0;
    WindowForButtons.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    WindowForButtons.hCursor = LoadCursor(nullptr, IDC_ARROW);
    WindowForButtons.hbrBackground = (HBRUSH)(GetStockObject(BLACK_BRUSH));
    WindowForButtons.lpszMenuName = MAKEINTRESOURCEW(NULL);
    WindowForButtons.lpszClassName = windowClassName.c_str();
    WindowForButtons.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    WindowForButtons.hInstance = params->hInst;

    ATOM retValue = RegisterClassExW(&WindowForButtons);
    hWindowButton = CreateWindowW(windowClassName.c_str(), windowTitle.c_str(), WS_CHILDWINDOW, 0, 0, 400, 20, hParentHandle, nullptr, params->hInst, nullptr);
    ShowWindow(hWindowButton, SW_SHOWDEFAULT);
    UpdateWindow(hWindowButton);
    return retValue;
}

LRESULT CALLBACK WndProcForWindowOfScroll(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hButtonRegister;
    static HWND hButtonSetupApi;
    switch (message)
    {
    case WM_COMMAND:
    {
        break;
    }
    break;
    case WM_CREATE:
    {
       
        break;
    }
    case WM_DEVICECHANGE:
    {
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT PS;
       // HDC hdc = BeginPaint(hWnd, &PS);
       // SetTextColor(hdc, RGB(255,0,0));
       // SetBkColor(hdc, RGB(0,255,255));
       // SetTextAlign(hdc, TA_CENTER);
       // const wchar_t* str = L"Privet";
       // TextOut(hdc, 100, 100, str , wcslen(str));
       // EndPaint(hWnd, &PS);
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