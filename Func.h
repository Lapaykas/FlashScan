#ifndef FUNC_H //include guard  защита от множественного подключени€, т.е. используетс€ только один экземпл€р
#define FUNC_H

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



template <typename T>
T* AllocWindowStruct(HWND hWnd)
{	
	T* retPointer = new T;	

	SetLastError(0);
	if (SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)retPointer) || GetLastError() != NULL)
	{
		delete retPointer;
		throw std::exception("Cannot create window long ptr");
	}	
	return retPointer;
}


#endif