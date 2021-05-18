#include "WindowForRegister.h"

//GLOBALSTRUCT* params = (GLOBALSTRUCT*)GetWindowLongPtr(hParentHandle, GWLP_USERDATA);
//ShowWindow(hWindowRegister, SW_SHOWDEFAULT);
//UpdateWindow(hWindowRegister);

//Функция регистрации класса окна для регистра
ATOM RegWindowForRegisters(HINSTANCE hInstance)
{
	WNDCLASSEXW WindowForRegister;;

	WindowForRegister.cbSize = sizeof(WNDCLASSEXW);
	WindowForRegister.style = CS_HREDRAW | CS_VREDRAW;
	WindowForRegister.lpfnWndProc = WndProcForWindowOfRegister;
	WindowForRegister.cbClsExtra = 0;
	WindowForRegister.cbWndExtra = 0;
	WindowForRegister.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	WindowForRegister.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WindowForRegister.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	WindowForRegister.lpszMenuName = MAKEINTRESOURCEW(NULL);
	WindowForRegister.lpszClassName = REGISTER_WINDOW_CLASS_NAME;
	WindowForRegister.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	WindowForRegister.hInstance = hInstance;
	
	return RegisterClassExW(&WindowForRegister);
}

//Функция создания окна для регистра
HWND CreateWindowForRegister()
{
	HWND hWindowForRegister = CreateWindowW(REGISTER_WINDOW_CLASS_NAME, L"Окно для записей из регистра", WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
		500, 300, 465, 180, nullptr, nullptr, nullptr, nullptr);
	if (hWindowForRegister == NULL)
	{
		return NULL;
	}
	ShowWindow(hWindowForRegister, SW_SHOWDEFAULT);
	UpdateWindow(hWindowForRegister);
	return hWindowForRegister;
}

//CALLBACK Функция окна для регистра для обработки сообщений
LRESULT CALLBACK WndProcForWindowOfRegister(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	REGISTERWINDOWSSTRUCT* pRegisterWindowStruct = (REGISTERWINDOWSSTRUCT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	switch (message)
	{
	case WM_COMMAND:
	{
		
	}
	break;
	case WM_CREATE:
	{
		REGISTERWINDOWSSTRUCT* pRegisterWindowStructCreate = AllocWindowStruct<REGISTERWINDOWSSTRUCT>(hWnd);
		if (pRegisterWindowStructCreate == nullptr)
		{
			MessageBox(NULL, L"Cannot create Window buttons ptr", L"Alloc Fail", MB_OK);
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
			break;
		}
		pRegisterWindowStructCreate->hListboxWindow = CreateWindow(L"listbox", L"UsbInfoFromRegister", WS_CHILDWINDOW | WS_VISIBLE | LBS_DISABLENOSCROLL | WS_VSCROLL | WS_HSCROLL,
			0, 0,450,150, hWnd, (HMENU)IDW_LOG_REGISTER, NULL, NULL);
		pRegisterWindowStructCreate->sizeHScroll = 0;

		std::vector<std::wstring> UsbInfoVector;
		GetUsbInfoFromRegister(UsbInfoVector);
		for (const auto& i : UsbInfoVector)
		{
			SendMessageW(pRegisterWindowStructCreate->hListboxWindow, LB_ADDSTRING, 0, (LPARAM)(LPWSTR)i.c_str());
			UINT tmpSize = CalcLBItemWidth(pRegisterWindowStructCreate->hListboxWindow, (LPWSTR)i.c_str());
			if (pRegisterWindowStructCreate->sizeHScroll <= tmpSize)
			{
				pRegisterWindowStructCreate->sizeHScroll = tmpSize;
				SendMessageW(pRegisterWindowStructCreate->hListboxWindow, LB_SETHORIZONTALEXTENT, (WPARAM)pRegisterWindowStructCreate->sizeHScroll, 0);
			}
		}
		
		break;
	}
	case WM_CLOSE:
	{
		delete pRegisterWindowStruct;
		DestroyWindow(hWnd);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}