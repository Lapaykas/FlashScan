#pragma once
#include <windows.h>
#include "DataBase.h"
#include "USBInfo.h"

typedef struct {
    HINSTANCE hInst;
    CDataBaseWrapper* BASE;
    HDEVNOTIFY REG_DEVICE;
}GLOBALSTRUCT, * PGLOBALSTRUCT;

const GUID guidForUSBDevices = { 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } };