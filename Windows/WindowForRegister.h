#include <windows.h>
#include "string"
#include "../Common.h"
#include "../Resource.h"
#include "../Func.h"
#include <vector>
#include "ClassName.h"

//Функция регистрации класса окна для получения списка устройств из регистра 
ATOM    RegWindowForRegisters(HINSTANCE hInstance);
//Функция создания окна для регистра
HWND	CreateWindowForRegister();
//CALLBACK Функция окна для регистра для обработки сообщений
LRESULT CALLBACK    WndProcForWindowOfRegister(HWND, UINT, WPARAM, LPARAM);
//Функция инициализации окна для регистра(WM_CREATE)
void InitRegisterWindow(HWND hWnd, LPARAM lParam);
//Функция добавления в окно ListBox информации о всех подлюченных USB устройствах
void PrintListOfUSBDevices(REGISTERWINDOWSSTRUCT* argStruct);

//hWindowRegister = CreateWindowW(windowClassName.c_str(), windowTitle.c_str(), WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME, 30, 40, 500, 200, nullptr, nullptr, nullptr, params);