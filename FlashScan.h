#pragma once

#include "resource.h"
#include "framework.h"
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
#include "Func.h"

//Функция регистрации класса главного окна
ATOM				MyRegisterClass(HINSTANCE hInstance);
//Функция регистрации всех окон, созданных в приложении
ATOM				RegWindowsClasses(HINSTANCE hInstance);
//Функция обработки ошибок при регистрации окон
std::wstring		DecodeErorrRegClasses(const ATOM err);
//Функция инициализации строк имени класса и названия окна
void				InitializeGlobalStrings(HINSTANCE hInstance);
//Функция регистрации приложения для получения уведомлений от системы
HDEVNOTIFY			RegProc(HWND hWnd) noexcept;
//Функция получения полного имени USB-накопителя
wchar_t*			GetUSBInfo(WPARAM wParam, LPARAM lParam) noexcept;
//Функция создания главного окна
BOOL				InitInstance(HINSTANCE hInstance, int nCmdShow, HWND& hWnd);
//Функция получения строки из имени и серийного номера устройства
std::wstring		GetConcateStringToAddToLogs(const wchar_t* arg1, const wchar_t* arg2);
//Функция инициализации главного окна(WM_CREATE)
void InitMainWindow(HWND hWnd, LPARAM lParam);
//Функция создания окон в основном окне
void CreateWindowsForMain(MAINWINDOWSTRUCT* argStruct, HWND hWnd);
//CALLBACK функция обработки сообщений
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//CALLBACK функция обработки сообщений для About
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
