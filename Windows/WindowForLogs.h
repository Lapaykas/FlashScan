#include "windows.h"
#include <string>
#include "../DataBase.h"
#include "../resource.h"
#include "../Func.h"
#include "ClassName.h"
#include "../Common.h"

//������� ����������� ������ ���� ��� �����
ATOM	RegWindowForLogs(HINSTANCE hInstance);
//������� �������� ���� ��� �����
HWND	CreateWindowForLogs(HINSTANCE hInstance, HWND hWndParent);
//CALLBACK ������� ���� ��� ����� ��� ��������� ���������
LRESULT CALLBACK    WndProcForWindowOfLogs(HWND, UINT, WPARAM, LPARAM);

//hWindowListBox = CreateWindowW(windowClassName.c_str(), windowTitle.c_str(), WS_CHILDWINDOW, 0, 90, 400, 300, hParentHandle, (HMENU)IDW_LOG_WINDOW, params->hInst, nullptr);