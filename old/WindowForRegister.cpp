#include "WindowForRegister.h"



HWND AddWindowForRegisters(const std::wstring&& windowClassName, const std::wstring&& windowTitle, HWND hParentHandle, const WNDPROC callback)
{
	GLOBALSTRUCT* params = (GLOBALSTRUCT*)GetWindowLongPtr(hParentHandle, GWLP_USERDATA);
	WNDCLASSEXW WindowForRegister;
	HWND hWindowRegister;

	WindowForRegister.cbSize = sizeof(WNDCLASSEXW);
	WindowForRegister.style = CS_HREDRAW | CS_VREDRAW;
	WindowForRegister.lpfnWndProc = callback;
	WindowForRegister.cbClsExtra = 0;
	WindowForRegister.cbWndExtra = 0;
	WindowForRegister.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	WindowForRegister.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WindowForRegister.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	WindowForRegister.lpszMenuName = MAKEINTRESOURCEW(NULL);
	WindowForRegister.lpszClassName = windowClassName.c_str();
	WindowForRegister.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	//WindowForRegister.hInstance = params->hInst;

	ATOM retValue = RegisterClassExW(&WindowForRegister);
	hWindowRegister = CreateWindowW(windowClassName.c_str(), windowTitle.c_str(), WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME, 30, 40, 500, 200, nullptr, nullptr, nullptr, params);
	ShowWindow(hWindowRegister, SW_SHOWDEFAULT);
	UpdateWindow(hWindowRegister);
	return hWindowRegister;
}

LRESULT CALLBACK WndProcForWindowOfRegister(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hWindowRegister;
	static UINT sizeHScroll;
	switch (message)
	{
	case WM_COMMAND:
	{
		
	}
	break;
	case WM_USER_ADD_STRING_TO_LISTBOX_REGISTER:
	{
		
	}
	case WM_CREATE:
	{
		hWindowRegister = CreateWindow(L"listbox", L"UsbInfoFromRegister", WS_CHILDWINDOW | WS_VISIBLE | LBS_DISABLENOSCROLL | WS_VSCROLL | WS_HSCROLL,
			0, 0,450,150, hWnd, (HMENU)IDW_LOG_REGISTER, NULL, NULL);
		std::vector<std::wstring> UsbInfoVector;
		GetUsbInfoFromRegister(UsbInfoVector);
		for (const auto& i : UsbInfoVector)
		{
			SendMessageW(hWindowRegister, LB_ADDSTRING, 0, (LPARAM)(LPWSTR)i.c_str());
			UINT tmpSize = CalcLBItemWidth(hWindowRegister, (LPWSTR)i.c_str());
			if (sizeHScroll <= tmpSize)
			{
				sizeHScroll = tmpSize;
				SendMessageW(hWindowRegister, LB_SETHORIZONTALEXTENT, (WPARAM)sizeHScroll, 0);
			}
		}
		
		break;



		break;
	}
	case WM_CLOSE:
	{
		HWND tmp = FindWindow(L"Window", L"WindowForRegister");
		DestroyWindow(hWnd);
		//PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}