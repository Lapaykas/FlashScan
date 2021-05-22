#include "windows.h"
#include <string>
#include "../DataBase.h"
#include "../resource.h"
#include "../Common.h"
#include "WindowForRegister.h"
#include "ClassName.h"
#include "../Common.h"
#include "../Func.h"

//Функция регистрации класса окна для кнопок
ATOM				RegWindowForButtons(HINSTANCE hInstance);
//Функция создания окна для кнопок
HWND				CreateWindowForButtons(HINSTANCE hInstance, HWND hWndParent);
//CALLBACK Функция окна для кнопок для обработки сообщений
LRESULT CALLBACK    WndProcForWindowOfButtons(HWND, UINT, WPARAM, LPARAM);
//Функция инициализации окна для кнопок(WM_CREATE)
void				InitButtonWindow(HWND hWnd);
//hWindowButton = CreateWindowW(windowClassName.c_str(), windowTitle.c_str(), WS_CHILDWINDOW, 0, 0, 400, 80, hParentHandle, nullptr, params->hInst, params);
