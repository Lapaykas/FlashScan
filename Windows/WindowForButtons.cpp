#include "WindowForButtons.h"

//GLOBALSTRUCT* params = (GLOBALSTRUCT*)GetWindowLongPtr(hParentHandle, GWLP_USERDATA);
//ShowWindow(hWindowButton, SW_SHOWDEFAULT);
//UpdateWindow(hWindowButton);

//Функция регистрации класса окна для кнопок
ATOM RegWindowForButtons(HINSTANCE hInstance)
{
    WNDCLASSEXW WindowForButtons;
    
    WindowForButtons.cbSize = sizeof(WNDCLASSEXW);
    WindowForButtons.style = CS_HREDRAW | CS_VREDRAW;
    WindowForButtons.lpfnWndProc = WndProcForWindowOfButtons;
    WindowForButtons.cbClsExtra = 0;
    WindowForButtons.cbWndExtra = 0;
    WindowForButtons.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    WindowForButtons.hCursor = LoadCursor(nullptr, IDC_ARROW);
    WindowForButtons.hbrBackground = (HBRUSH)(GetStockObject(BLACK_BRUSH));
    WindowForButtons.lpszMenuName = MAKEINTRESOURCEW(NULL);
    WindowForButtons.lpszClassName = BUTTONS_WINDOW_CLASS_NAME;
    WindowForButtons.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    WindowForButtons.hInstance = hInstance;
   
    return RegisterClassExW(&WindowForButtons);
}

//Функция создания окна для кнопок
HWND CreateWindowForButtons(HINSTANCE hInstance, HWND hWndParent)
{
	HWND hWindowForButtons = CreateWindowW(BUTTONS_WINDOW_CLASS_NAME, L"Окно для кнопок", WS_CHILDWINDOW, 0, 0, 400, 20, 
		hWndParent, nullptr, hInstance, nullptr);
	if (hWindowForButtons == NULL)
	{
		return NULL;
	}
	ShowWindow(hWindowForButtons, SW_SHOWDEFAULT);
	UpdateWindow(hWindowForButtons);
	return hWindowForButtons;
}

//CALLBACK Функция окна для кнопок для обработки сообщений
LRESULT CALLBACK WndProcForWindowOfButtons(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BUTTONWINDOWSSTRUCT* pButtonWindowStruct = (BUTTONWINDOWSSTRUCT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    	
    switch (message)
    {
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
			case IDB_GET_REGISTER_USB:
			{
				pButtonWindowStruct->hRegisterWindow = FindWindowW(REGISTER_WINDOW_CLASS_NAME, L"Окно для записей из регистра");
				if (pButtonWindowStruct->hRegisterWindow == NULL)
				{
					pButtonWindowStruct->hRegisterWindow = CreateWindowForRegister();
				}			    
			}     
        }
        break;
    }
    break;
    case WM_CREATE:
    {
		BUTTONWINDOWSSTRUCT* pButtonWindowStructCreate = AllocWindowStruct<BUTTONWINDOWSSTRUCT>(hWnd);
		if (pButtonWindowStructCreate == nullptr)
		{
			MessageBox(NULL, L"Cannot create Window buttons ptr", L"Alloc Fail", MB_OK);
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
			break;
		}
		pButtonWindowStructCreate->hRegisterWindow = NULL;
		pButtonWindowStructCreate->hButtonWindowRegister = CreateWindowW(L"button", L"READ USB FROM REGISTER", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 0, 400,20, hWnd, (HMENU)IDB_GET_REGISTER_USB, NULL, NULL);
 
        break;
    }
    case WM_DEVICECHANGE:
    {
        break;
    }
    case WM_DESTROY:
		delete pButtonWindowStruct;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}