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

//������� ����������� ������ �������� ����
ATOM				MyRegisterClass(HINSTANCE hInstance);
//������� ����������� ���� ����, ��������� � ����������
ATOM				RegWindowsClasses(HINSTANCE hInstance);
//������� ��������� ������ ��� ����������� ����
std::wstring		DecodeErorrRegClasses(const ATOM err);
//������� ������������� ����� ����� ������ � �������� ����
void				InitializeGlobalStrings(HINSTANCE hInstance);
//������� ����������� ���������� ��� ��������� ����������� �� �������
HDEVNOTIFY			RegProc(HWND hWnd) noexcept;
//������� ��������� ������� ����� USB-����������
wchar_t*			GetUSBInfo(WPARAM wParam, LPARAM lParam) noexcept;
//������� �������� �������� ����
BOOL				InitInstance(HINSTANCE hInstance, int nCmdShow, HWND& hWnd);
//������� ��������� ������ �� ����� � ��������� ������ ����������
std::wstring		GetConcateStringToAddToLogs(const wchar_t* arg1, const wchar_t* arg2);
//������� ������������� �������� ����(WM_CREATE)
void InitMainWindow(HWND hWnd, LPARAM lParam);
//������� �������� ���� � �������� ����
void CreateWindowsForMain(MAINWINDOWSTRUCT* argStruct, HWND hWnd);
//CALLBACK ������� ��������� ���������
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//CALLBACK ������� ��������� ��������� ��� About
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
