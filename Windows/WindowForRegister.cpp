#include "WindowForRegister.h"

//GLOBALSTRUCT* params = (GLOBALSTRUCT*)GetWindowLongPtr(hParentHandle, GWLP_USERDATA);
//ShowWindow(hWindowRegister, SW_SHOWDEFAULT);
//UpdateWindow(hWindowRegister);

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
		InitRegisterWindow(hWnd, lParam);		
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
void InitRegisterWindow(HWND hWnd, LPARAM lParam)
{
	try
	{
		REGISTERWINDOWSSTRUCT* pRegisterWindowStructCreate = AllocWindowStruct<REGISTERWINDOWSSTRUCT>(hWnd);
		pRegisterWindowStructCreate->hListboxWindow = CreateWindow(L"listbox", L"UsbInfoFromRegister", WS_CHILDWINDOW | WS_VISIBLE | LBS_DISABLENOSCROLL | WS_VSCROLL | WS_HSCROLL,
			0, 0, 450, 150, hWnd, (HMENU)IDW_LOG_REGISTER, NULL, NULL);
		pRegisterWindowStructCreate->sizeHScroll = 0;
		if (pRegisterWindowStructCreate->hListboxWindow == NULL)
		{
			MessageBoxA(NULL, "Cannot create window for register", "Create Window Error", MB_OK);
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
		}
		PrintListOfUSBDevices(pRegisterWindowStructCreate);
	}
	catch (const std::bad_alloc& error)
	{
		MessageBoxA(NULL, error.what(), "Memory Error", MB_OK);
		SendMessage(hWnd, WM_DESTROY, NULL, NULL);
	}
}
void PrintListOfUSBDevices(REGISTERWINDOWSSTRUCT* argStruct)
{
	std::vector<std::wstring> UsbInfoVector;
	GetUsbInfoFromRegister(UsbInfoVector);
	for (const auto& i : UsbInfoVector)
	{
		SendMessageW(argStruct->hListboxWindow, LB_ADDSTRING, 0, (LPARAM)(LPWSTR)i.c_str());
		UINT tmpSize = CalcLBItemWidth(argStruct->hListboxWindow, (LPWSTR)i.c_str());
		if (argStruct->sizeHScroll <= tmpSize)
		{
			argStruct->sizeHScroll = tmpSize;
			SendMessageW(argStruct->hListboxWindow, LB_SETHORIZONTALEXTENT, (WPARAM)argStruct->sizeHScroll, 0);
		}
	}
}
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