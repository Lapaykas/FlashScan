#pragma once

#define ERRORINFO(errorMessage) \
do{ \
char error[256]; \
sprintf_s(error, 256,"%s %s %d %s", __FILE__ ,__FUNCTION__, __LINE__, errorMessage); \
throw std::exception(error);}\
while(0);


#include <windows.h>
#include "DataBase.h"
#include "USBInfo.h"

//Структура для главного окна
typedef struct {
    HINSTANCE hInst;
    CDataBaseWrapper* BASE;
    HDEVNOTIFY REG_DEVICE;
	HWND hLogWindow;
}MAINWINDOWSTRUCT, *PMAINWINDOWRUCT;

//Структура для окна с кнопками
typedef struct
{
	HWND hButtonWindowRegister;
	HWND hRegisterWindow;
}BUTTONWINDOWSSTRUCT, *PBUTTONWINDOWSTRUCT;

//Структура для окна с записями из регистра
typedef struct
{
	HWND hListboxWindow;
	UINT sizeHScroll;
}REGISTERWINDOWSSTRUCT, *PREGISTERWINDOWSTRUCT;

const GUID guidForUSBDevices = { 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } };