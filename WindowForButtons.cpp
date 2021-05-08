#include "WindowForButtons.h"




ATOM AddWindowForButtons(const std::wstring&& windowClassName, const std::wstring&& windowTitle, HWND hParentHandle, const WNDPROC callback)
{
    GLOBALSTRUCT* params = (GLOBALSTRUCT*)GetWindowLongPtr(hParentHandle, GWLP_USERDATA);
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
    hWindowButton = CreateWindowW(windowClassName.c_str(), windowTitle.c_str(), WS_CHILDWINDOW, 0, 0, 400, 80, hParentHandle, nullptr, params->hInst, params);
    ShowWindow(hWindowButton, SW_SHOWDEFAULT);
    UpdateWindow(hWindowButton);
    return retValue;
}

LRESULT CALLBACK WndProcForWindowOfButtons(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    static HWND hButtonRegister;
    static HWND hButtonSetupApi;
    switch (message)
    {
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDB_GET_REGISTER_USB:
        {

        }
        case IDB_GET_SETUPAPI_USB:
        {

        }
        }
        break;
    }
    break;
    case WM_CREATE:
    {
        CREATESTRUCT* pCreateParams = reinterpret_cast<CREATESTRUCT*>(lParam);
        GLOBALSTRUCT* pGlobal = reinterpret_cast<GLOBALSTRUCT*>(pCreateParams->lpCreateParams);
        hButtonRegister = CreateWindow(L"button", L"READ USB FROM REGISTER", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 0, 200, 20, hWnd, (HMENU)IDB_GET_REGISTER_USB, pGlobal->hInst, NULL);
        hButtonSetupApi = CreateWindow(L"button", L"GET USB WITH SETUPAPI", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 200, 0, 200, 20, hWnd, (HMENU)IDB_GET_SETUPAPI_USB, pGlobal->hInst, NULL);
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