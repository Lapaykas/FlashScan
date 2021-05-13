// FlashScan.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "FlashScan.h"
#include "Dbt.h"
#include "DataBase.h"
#include "USBInfo.h"
#include <windows.h>
#include <utility>
#include <string>
#include "./Windows/WindowForButtons.h" 
#include "./Windows/WindowForLogs.h" 
#include "./Windows/WindowForRegister.h"
#include "Common.h"


#define MAX_LOADSTRING 100
#define ID_BUTTON 3000
// Global Variables:
                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Giud for usb devices
ATOM                MyRegisterClass(HINSTANCE hInstance);
bool RegWindowsClasses(HINSTANCE hInstance)
{
	std::wstring errorMessage(L"Cannot create ");
	bool result = true;
	if (MyRegisterClass(hInstance) == NULL)
	{
		result &= false;
		errorMessage += L"Mainwindow class";
	}
	if (RegWindowForButtons(hInstance) == NULL)
	{
		result &= false;
		errorMessage += L" WindowForButtons class";
	}
	if (RegWindowForLogs(hInstance) == NULL)
	{
		result &= false;
		errorMessage += L" WindowForLogs class";
	}
	if (RegWindowForRegisters(hInstance) == NULL)
	{
		result &= false;
		errorMessage += L" WindowForRegister class";
	}
	if (!result)
	{
		MessageBox(NULL, errorMessage.c_str(), L"FailRegistry", MB_OK);
	}
	return result;
	
}


// Forward declarations of functions included in this code module:

BOOL                InitInstance(HINSTANCE, int, HWND&);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FLASHSCAN, szWindowClass, MAX_LOADSTRING);
	// Регистрация классов окон
	if (!RegWindowsClasses(hInstance)) 
	{
		return FALSE;
	}
    // Perform application initialization:
    HWND MAINWINDOWHANDLE;
    if (!InitInstance (hInstance, nCmdShow, MAINWINDOWHANDLE))
    {
        return FALSE;
    }
    

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FLASHSCAN));
   
    
    // Main message loop:
    MSG msg;    
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
        
    return (int) msg.wParam;
}


//Функция регистрации приложения для получения уведомлений от системы
HDEVNOTIFY RegProc(HWND hWnd) noexcept
{
    DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
    ZeroMemory(&NotificationFilter, sizeof(NotificationFilter));
    NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    NotificationFilter.dbcc_classguid = guidForUSBDevices;
    HDEVNOTIFY REG = RegisterDeviceNotification(hWnd, &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE); 
    return REG;
}
//Функция получения полного имени USB-накопителя
wchar_t* GetUSBInfo(WPARAM wParam, LPARAM lParam) noexcept
{
    int wmId = LOWORD(wParam);
    switch (wmId)
    {
    case  DBT_DEVICEARRIVAL:
        DEV_BROADCAST_HDR* DeviceType = (DEV_BROADCAST_HDR*)lParam;
        switch (DeviceType->dbch_devicetype)
        {
        case DBT_DEVTYP_DEVICEINTERFACE:
            DEV_BROADCAST_DEVICEINTERFACE* USBInfo = (DEV_BROADCAST_DEVICEINTERFACE*)lParam;
            return USBInfo->dbcc_name;
        }
    }
    return nullptr;
}
//Функция регистрации класса главного окна
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FLASHSCAN));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;//MAKEINTRESOURCEW(IDC_FLASHSCAN);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
//Функция создания главного окна
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND& hWnd)
{
    // Store instance handle in our global variable

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
      500,300 , 405,500, nullptr, nullptr, hInstance, hInstance);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
//Функция получения строки из имени и серийного номера устройства
std::wstring GetConcateStringToAddToLogs(const wchar_t* arg1, const wchar_t* arg2)
{
    std::wstring wstrResult;
    return wstrResult =L"Device Name: " + std::wstring(arg1) + L" Serial Number: " + std::wstring(arg2);
}

//CALLBACK функция обработки сообщений
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{    
    MAINWINDOWSTRUCT* pMainWindowStruct = (MAINWINDOWSTRUCT*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:                
                DialogBox(pMainWindowStruct->hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_CREATE:   
        {
		;
            MAINWINDOWSTRUCT* pMainWindowStructCreate = new MAINWINDOWSTRUCT;
		
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pMainWindowStructCreate);

        CDataBaseWrapper *BASE = new CDataBaseWrapper;

        
        pMainWindowStructCreate->BASE = BASE;

        CREATESTRUCT* pCreateParams = reinterpret_cast<CREATESTRUCT*>(lParam);
        pMainWindowStructCreate->hInst = reinterpret_cast<HINSTANCE>(pCreateParams->lpCreateParams);

        pMainWindowStructCreate->REG_DEVICE = RegProc(hWnd);
        HWND hWindowForButtons = CreateWindowForButtons(pMainWindowStructCreate->hInst, hWnd);  
		pMainWindowStructCreate->hLogWindow = CreateWindowForLogs(pMainWindowStructCreate->hInst, hWnd);;
 
        break;
        }
    case WM_DEVICECHANGE:
    {               
        wchar_t* pConnectedDevice = GetUSBInfo(wParam, lParam);
        if (pConnectedDevice == nullptr)
            break;
        else {
            CUsbInfoRetrieved USBINFO(pConnectedDevice);
			SendMessage(pMainWindowStruct->hLogWindow, WM_USER_ADD_STRING_TO_LISTBOX, 0, 
                (LPARAM)(LPWSTR)GetConcateStringToAddToLogs(USBINFO.GetDeviceName(), USBINFO.GetSerialNumber()).c_str());
            pMainWindowStruct->BASE->AddDataToDataBase(USBINFO.GetDeviceName(), USBINFO.GetSerialNumber());
			
            break;
        }
        }
    case WM_DESTROY:
        UnregisterDeviceNotification(pMainWindowStruct->REG_DEVICE);
        delete pMainWindowStruct->BASE;
        delete pMainWindowStruct;
        PostQuitMessage(0);
        break;
    default:
        
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
