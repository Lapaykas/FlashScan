// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Func.h"

//Функция получения длины строки в пикселях(в том числе и невидимой области)
UINT CalcLBItemWidth(HWND hLB, LPWSTR Text)
{
	RECT r;
	HDC hLBDC = GetDC(hLB);
	HDC hDC = CreateCompatibleDC(hLBDC);
	HFONT hFont = (HFONT)SendMessage(hLB, WM_GETFONT, 0, 0);
	HGDIOBJ hOrgFont = SelectObject(hDC, hFont);
	ZeroMemory(&r, sizeof(r));
	DrawTextW(hDC, Text, -1, &r, DT_CALCRECT | DT_SINGLELINE | DT_NOCLIP);
	SelectObject(hDC, hOrgFont);
	DeleteDC(hDC);
	ReleaseDC(hLB, hLBDC);
	return (r.right - r.left) + (2 * GetSystemMetrics(SM_CXEDGE)) + 1;
}

//Результирующая функция получения вектора с названиями и серийными номерами USB устройств
void GetUsbInfoFromRegister(std::vector<std::wstring> &VectorOfDeviceInfo)
{
	HKEY hDeviceNameKey;
	if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Enum\\USBSTOR", 0, KEY_READ, &hDeviceNameKey) == ERROR_SUCCESS)
	{
		QueryKey(hDeviceNameKey, &VectorOfDeviceInfo);
	}
}

//Функция получения имени USB устройств из названий каталогов регистра
void QueryKey(HKEY hKey, std::vector<std::wstring>* argVector)
{
	TCHAR    BufferDeviceName[MAX_KEY_LENGTH];   // buffer for subkey name	
	DWORD    BufferDeviceNameSize; ;                   // size of name string 	
	DWORD	 retCode;
	for (auto i = 0ul; i < GetCSubKeys(hKey); i++)
	{
		BufferDeviceNameSize = MAX_KEY_LENGTH;
		retCode = RegEnumKeyEx(hKey, i, BufferDeviceName, &BufferDeviceNameSize, NULL, NULL, NULL, NULL);
		if (retCode == ERROR_SUCCESS)
		{
			GetSerialNumbers(BufferDeviceName, argVector);
		}
	}
	RegCloseKey(hKey);
}

//Функция получения серийных номеров USB устройств из названий каталогов регистра
void GetSerialNumbers(TCHAR* argBuffer, std::vector<std::wstring>* argVector)
{
	TCHAR    BufferSerialNumber[MAX_KEY_LENGTH];   // buffer for subkey name
	DWORD    BufferSerialNumberSize;
	DWORD	 retCode;

	constexpr size_t SubDirPathSize = 1024;
	wchar_t SubDirPath[SubDirPathSize];
	swprintf(SubDirPath, SubDirPathSize, L"SYSTEM\\CurrentControlSet\\Enum\\USBSTOR\\%s", argBuffer);
	HKEY hSerialNumberKey;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, SubDirPath, 0, KEY_READ, &hSerialNumberKey);
	for (auto j = 0ul; j < GetCSubKeys(hSerialNumberKey); j++)
	{
		BufferSerialNumberSize = MAX_KEY_LENGTH;
		retCode = RegEnumKeyEx(hSerialNumberKey, j, BufferSerialNumber, &BufferSerialNumberSize, NULL, NULL, NULL, NULL);
		if (retCode == ERROR_SUCCESS)
		{
			std::wstring wstrResult;
			wstrResult = L"Device Name: " + std::wstring(argBuffer) + L" Serial Number: " + std::wstring(BufferSerialNumber);
			argVector->emplace_back(wstrResult);
			//VectorOfSerialNumbers.push_back(BufferSerialNumber);
		}
	}
	RegCloseKey(hSerialNumberKey);
}
//Функция получения списка подкаталогов по указаному ключу в реестре
DWORD GetCSubKeys(HKEY hKey)
{
	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
	DWORD    cchClassName = MAX_PATH;  // size of class string 
	DWORD    cSubKeys = 0;               // number of subkeys 
	DWORD    cbMaxSubKey;              // longest subkey size 
	DWORD    cchMaxClass;              // longest class string 
	DWORD    cValues;              // number of values for key 
	DWORD    cchMaxValue;          // longest value name 
	DWORD    cbMaxValueData;       // longest value data 
	DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time 


	DWORD cchValue = MAX_VALUE_NAME;

	// Get the class name and the value count. 
	RegQueryInfoKey(
		hKey,                    // key handle 
		achClass,                // buffer for class name 
		&cchClassName,           // size of class string 
		NULL,                    // reserved 
		&cSubKeys,               // number of subkeys 
		&cbMaxSubKey,            // longest subkey size 
		&cchMaxClass,            // longest class string 
		&cValues,                // number of values for this key 
		&cchMaxValue,            // longest value name 
		&cbMaxValueData,         // longest value data 
		&cbSecurityDescriptor,   // security descriptor 
		&ftLastWriteTime);       // last write time 

	return cSubKeys;

}