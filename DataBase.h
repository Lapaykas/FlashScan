#pragma once
#include  "./SQLlite/sqlite3.h" 
#include <stdarg.h>
#include <windows.h>
#include <set>
#include <vector>
#include <string>
class CDataBaseWrapper //переименовать нормально
{
public:
	CDataBaseWrapper();
	~CDataBaseWrapper();
	void AddDataToDataBase(const wchar_t *deviceName, const wchar_t* serialNumber) noexcept;
	void GetSerialNumByConnectTime(LPSYSTEMTIME systemtime, std::vector<std::wstring>& vectorOfSerialNumber);
private:
	void InsertUSBInfo(const wchar_t* deviceName, const wchar_t* serialNumber) noexcept;
	int TakeId(const wchar_t* serialNumber) noexcept;
	void AddConnectionDate(int id) noexcept;
	//void CreateTableForDate(int id) noexcept;
	int TakeSerialNumInfo(const wchar_t* serialNumber);

	sqlite3_stmt* SQLPrepareStatement(const wchar_t* sqlRequest, int argc, bool bBindInt, va_list vl);
	int SQLPrepareForUsbInfo(const wchar_t* sqlRequest, int argc, ...);
	int SQLPrepareToGetId(const wchar_t* sqlRequest, int argc, int* id, ...);
	int SQLPrepareSet(const wchar_t* sqlRequest, int argc, std::set<int>* argSet, ...);
	int SQLPrepareVector(const wchar_t* sqlRequest, int argc, std::vector<std::wstring>* argVector, ...);

	void SQLExecForDateTable(const char* sql, int id, LPSYSTEMTIME SystemTime);
	// int SQLPrepare(const wchar_t* sqlRequest, int argc, int* id, std::set<int>* argSet, std::vector<std::wstring>* argVector, ...);
	sqlite3* m_pDataBaseHandle = 0; 
};
// убрать m_pResultSelect
// обернуть все в функции с беск. числом параметров


