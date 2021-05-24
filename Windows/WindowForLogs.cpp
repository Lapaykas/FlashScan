// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "WindowForButtons.h"
#include "WindowForLogs.h"

 

struct PARAMSSTRUCT {
    HINSTANCE hInst;
    CDataBaseWrapper* BASE;
    HDEVNOTIFY REG_DEVICE;
};

// UnregisterClass(windowClassName.c_str(), GetModuleHandle(nullptr));
//PARAMSSTRUCT* params = (PARAMSSTRUCT*)GetWindowLongPtr(hParentHandle, GWLP_USERDATA);
//ShowWindow(hWindowListBox, SW_SHOWDEFAULT);
//UpdateWindow(hWindowListBox);

//Функция регистрации класса окна для логов
ATOM RegWindowForLogs(HINSTANCE hInstance)
{   
    WNDCLASSEXW WindowForLogs;

    WindowForLogs.cbSize = sizeof(WNDCLASSEXW);
    WindowForLogs.style = CS_HREDRAW | CS_VREDRAW;
    WindowForLogs.lpfnWndProc = WndProcForWindowOfLogs;
    WindowForLogs.cbClsExtra = 0;
    WindowForLogs.cbWndExtra = 0;
    WindowForLogs.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    WindowForLogs.hCursor = LoadCursor(nullptr, IDC_ARROW);
    WindowForLogs.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
    WindowForLogs.lpszMenuName = MAKEINTRESOURCEW(NULL);
    WindowForLogs.lpszClassName = LOGS_WINDOW_CLASS_NAME;
    WindowForLogs.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	WindowForLogs.hInstance = hInstance;
    
    return RegisterClassExW(&WindowForLogs);
}

//Функция создания окна для логов
HWND CreateWindowForLogs(HINSTANCE hInstance, HWND hWndParent)
{
	HWND hWindowForLogs = CreateWindowW(LOGS_WINDOW_CLASS_NAME, L"Окно для логов", WS_CHILDWINDOW, 0, 90, 400, 300,
		hWndParent, (HMENU)IDW_LOG_WINDOW, hInstance, nullptr);
	if (hWindowForLogs == NULL)
	{
        throw std::exception("Cannot create window for logs");
	}
	ShowWindow(hWindowForLogs, SW_SHOWDEFAULT);
	UpdateWindow(hWindowForLogs);
	return hWindowForLogs;
}

//CALLBACK Функция окна для логов для обработки сообщений
LRESULT CALLBACK WndProcForWindowOfLogs(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{   
	static UINT sizeHScroll;
    static HWND hWndListBox;
    switch (message)
    {
    case WM_COMMAND:
    {
        
        break;
    }
    break;
    case WM_USER_ADD_STRING_TO_LISTBOX:
    {        
     
        SendMessageW(hWndListBox, LB_ADDSTRING, 0, lParam);
        UINT tmpSize = CalcLBItemWidth(hWndListBox, (LPWSTR)lParam);
        if (sizeHScroll <= tmpSize)
        {
            sizeHScroll = tmpSize;
            SendMessageW(hWndListBox, LB_SETHORIZONTALEXTENT, (WPARAM)sizeHScroll, 0);
        }
        break;
    }
    case WM_CREATE:
    {
		sizeHScroll = 0;
        hWndListBox = CreateWindowW(L"listbox", NULL, WS_CHILDWINDOW | WS_VISIBLE | LBS_DISABLENOSCROLL | WS_VSCROLL | WS_HSCROLL
            , 0, 0, 380, 100, hWnd, (HMENU)IDW_LOG_WINDOW, nullptr, nullptr);
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