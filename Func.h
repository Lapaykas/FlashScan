#include <windows.h>
#include <tchar.h>
#include <vector>
#include <cfgmgr32.h>
#include <string>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

UINT CalcLBItemWidth(HWND hLB, LPWSTR Text);
void GetUsbInfoFromRegister(std::vector<std::wstring>& VectorOfDeviceInfo);
void QueryKey(HKEY hKey, std::vector<std::wstring>* argVector);
void GetSerialNumbers(TCHAR* argBuffer, std::vector<std::wstring>* argVector);
DWORD GetCSubKeys(HKEY hKey);
