#pragma once

#define ERRORINFO(errorMessage) \
do{ \
char error[256]; \
sprintf_s(error, 256,"%s %s %d %s", __FILE__ ,__FUNCTION__, __LINE__, errorMessage); \
throw std::exception(error);}\
while(0);

#define MAIN_CLASS_ERROR 1
#define BUTTON_CLASS_ERROR 2
#define LOG_CLASS_ERROR 4
#define REGISTER_CLASS_ERROR 8

#include <windows.h>
#include "DataBase.h"
#include "USBInfo.h"
#include <memory>

//Структура для главного окна
typedef struct _MAINWINDOWSTRUCT
{
	HINSTANCE hInst = nullptr;
	std::unique_ptr<CDataBaseWrapper> BASE;
	//	CDataBaseWrapper* BASE;
	HDEVNOTIFY REG_DEVICE = nullptr;
	HWND hLogWindow = NULL;
}MAINWINDOWSTRUCT, * PMAINWINDOWRUCT;

//Структура для окна с кнопками
typedef struct _BUTTONWINDOWSSTRUCT
{
	HWND hButtonWindowRegister = NULL;
	HWND hRegisterWindow = NULL;
}BUTTONWINDOWSSTRUCT, * PBUTTONWINDOWSTRUCT;

//Структура для окна с записями из регистра
typedef struct _REGISTERWINDOWSSTRUCT
{
	HWND hListboxWindow = NULL;
	UINT sizeHScroll = NULL;
}REGISTERWINDOWSSTRUCT, * PREGISTERWINDOWSTRUCT;

const GUID guidForUSBDevices = { 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } };