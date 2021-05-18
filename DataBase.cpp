#include "DataBase.h"
#include <iostream>
#include "Common.h"



#define __SELECTID__ L"SELECT id FROM USBDeviceBase WHERE SerialNum = ?;\0"
#define __SELECTINFO__ L"SELECT SerialNum FROM USBDeviceBase WHERE id = ?;\0"
#define __SELECTSERIALNUM__  L"SELECT SerialNum FROM USBDeviceBase WHERE SerialNum = ?;\0"
#define __INSERTDATA__ L"INSERT INTO USBDeviceBase (DeviceName, SerialNum) VALUES(?,?);\0"
#define __INSERTTIME__ "INSERT INTO ConnectDateForDevice VALUES(%i,'%u-%02u-%02u', '%02u:%02u')"
#define __CREATETIMETABLE__  "CREATE TABLE IF NOT EXISTS ConnectDateForDevice(id INTEGER, Date TEXT, Time TEXT)"
#define __CREATEMAINTABLE__ "CREATE TABLE IF NOT EXISTS USBDeviceBase(id INTEGER PRIMARY KEY, DeviceName TEXT, SerialNum TEXT)"
#define __HOWMANYCOLLUMS__ L"SELECT id FROM ConnectDateForDevice WHERE Date = ?"

//Реализация конструкторов класса CDataBaseWrapper
CDataBaseWrapper::CDataBaseWrapper():  m_pDataBaseHandle(nullptr)
{
	char* m_pErrorDataBase = 0;
	
	sqlite3_open("UsbDevices.db", &m_pDataBaseHandle);
	if (sqlite3_exec(m_pDataBaseHandle, __CREATEMAINTABLE__, 0, 0, &m_pErrorDataBase))
	{		
		sqlite3_free(m_pErrorDataBase);
		ERRORINFO(m_pErrorDataBase);
	}
	if (sqlite3_exec(m_pDataBaseHandle, __CREATETIMETABLE__, 0, 0, &m_pErrorDataBase))
	{
		sqlite3_free(m_pErrorDataBase);
		ERRORINFO(m_pErrorDataBase);
	}
}

CDataBaseWrapper::~CDataBaseWrapper()
{
	sqlite3_close(m_pDataBaseHandle);
}
//__________________________________________________________

//Функция добавления данных в БД
void CDataBaseWrapper::AddDataToDataBase(const wchar_t* deviceName, const wchar_t* serialNumber) noexcept
{
	if (deviceName == nullptr || serialNumber == nullptr)
		return;

	switch (TakeSerialNumInfo(serialNumber))
	{	
	case SQLITE_DONE:		
		InsertUSBInfo(deviceName, serialNumber);
		//CreateTableForDate(TakeId(serialNumber));
	case SQLITE_ROW:
		AddConnectionDate(TakeId(serialNumber));
		break;
	case SQLITE_MISUSE:
		//throw "Wrong SQL prepare";
		break;	
	}		
}
//std::vector<wchar_t*>& vector, LPSYSTEMTIME systemtime


int CDataBaseWrapper::TakeId(const wchar_t* serialNumber) noexcept
{
	int id = 0;
	//SQLPrepare(__SELECTID__, 1, &id, nullptr,nullptr ,serialNumber);
	SQLPrepareToGetId(__SELECTID__, 1, &id, serialNumber);
	return id;
}

int CDataBaseWrapper::TakeSerialNumInfo(const wchar_t* serialNumber)
{	
	//return SQLPrepare(__SELECTSERIALNUM__, 1, nullptr, nullptr, nullptr,serialNumber);
	return SQLPrepareForUsbInfo( __SELECTSERIALNUM__  , 1,serialNumber);
}

void CDataBaseWrapper::InsertUSBInfo(const wchar_t* deviceName, const wchar_t* serialNumber) noexcept
{	
	//SQLPrepare(__INSERTDATA__, 2, nullptr, nullptr,nullptr ,deviceName, serialNumber);
	SQLPrepareForUsbInfo(__INSERTDATA__, 2, deviceName, serialNumber);
}

void CDataBaseWrapper::AddConnectionDate(int id) noexcept
{		
	SYSTEMTIME   SystemTime;	
	GetLocalTime(&SystemTime);
	try {
		SQLExecForDateTable(__INSERTTIME__, id, &SystemTime);
	}
	catch (const std::exception& error)
	{
		std::cout<<error.what()<<std::endl;
	}
}

//void CDataBaseWrapper::CreateTableForDate(int id) noexcept
//{
//	try 
//	{
//		SQLExecForDateTable(__CREATETIMETABLE__, id, nullptr);
//	}
//	catch (const std::exception& error)
//	{
//		std::cout << error.what() << std::endl;
//	}
//}

void CDataBaseWrapper::SQLExecForDateTable(const char* sql, int id, LPSYSTEMTIME SystemTime)
{
	char* m_pErrorDataBase;
	constexpr size_t requestSize = 128;
	char sqlRequest[requestSize];
	if (SystemTime == nullptr)
	{
		sprintf_s(sqlRequest, requestSize, sql, id);
	}	
	else
	{
		sprintf_s(sqlRequest, requestSize, sql,  id, SystemTime->wYear, SystemTime->wMonth, SystemTime->wDay, 
			SystemTime->wHour, SystemTime->wMinute);
	}
	if(sqlite3_exec(m_pDataBaseHandle, sqlRequest, 0, 0, &m_pErrorDataBase))
	{
		sqlite3_free(m_pErrorDataBase);
		ERRORINFO(m_pErrorDataBase);
	}
}

void CDataBaseWrapper::GetSerialNumByConnectTime(LPSYSTEMTIME systemtime, std::vector<std::wstring>& vectorOfSerialNumber)
{
	constexpr size_t requestSize = 128;
	wchar_t sqlRequest[requestSize];
	swprintf(sqlRequest, requestSize, L"%u-%02u-%02u", systemtime->wYear, systemtime->wMonth, systemtime->wDay);
	std::set<int> setOfId;
	SQLPrepareSet(__HOWMANYCOLLUMS__, 1, &setOfId, sqlRequest);
	for (auto i : setOfId)
	{
		SQLPrepareVector(__SELECTINFO__, 1, &vectorOfSerialNumber, i);
	}
}


int CDataBaseWrapper::SQLPrepareForUsbInfo(const wchar_t* sqlRequest, int argc, ...)
{
	va_list vl;
	va_start(vl, argc);
	sqlite3_stmt* m_pResultSelect = SQLPrepareStatement(sqlRequest, argc, false, vl);

	int sqlResult = sqlite3_step(m_pResultSelect);

	sqlite3_finalize(m_pResultSelect);
	va_end(vl);
	return sqlResult;
}	

int CDataBaseWrapper::SQLPrepareToGetId(const wchar_t* sqlRequest, int argc, int* id, ...)
{
	va_list vl;
	va_start(vl, id);
	sqlite3_stmt* m_pResultSelect = SQLPrepareStatement(sqlRequest, argc, false, vl);
	
	int sqlResult = sqlite3_step(m_pResultSelect);
	*id = sqlite3_column_int(m_pResultSelect, 0);
	
	sqlite3_finalize(m_pResultSelect);
	va_end(vl);
	return sqlResult;
}
int CDataBaseWrapper::SQLPrepareSet(const wchar_t* sqlRequest, int argc, std::set<int>* argSet, ...)
{
	va_list vl;
	va_start(vl, argSet);
	sqlite3_stmt* m_pResultSelect = SQLPrepareStatement(sqlRequest, argc, false, vl);	
	int sqlResult = sqlite3_step(m_pResultSelect);
	do
	{
		argSet->insert(sqlite3_column_int(m_pResultSelect, 0));
	} while (sqlite3_step(m_pResultSelect) == SQLITE_ROW);
	sqlite3_finalize(m_pResultSelect);
	va_end(vl);
	return sqlResult;
}
int CDataBaseWrapper::SQLPrepareVector(const wchar_t* sqlRequest, int argc,std::vector<std::wstring>* argVector, ...)
{	
	va_list vl;
	va_start(vl, argVector);
	sqlite3_stmt* m_pResultSelect = SQLPrepareStatement(sqlRequest, argc, true, vl);

	int sqlResult = sqlite3_step(m_pResultSelect);

	std::wstring tmpWstring((const wchar_t*)sqlite3_column_text16(m_pResultSelect, 0));
	argVector->push_back(tmpWstring);
	
	sqlite3_finalize(m_pResultSelect);
	va_end(vl);
	return sqlResult;
}

//int CDataBaseWrapper::ExecSql(const char* szTypes, ...)
//{
//	constexpr size_t requestSize = 128;
//	int id = 0;
//	va_list vl;
//	int tmp;
//	sqlite3_stmt* m_pResultSelect;
//	char* m_pErrorDataBase = 0;
//	va_start(vl, szTypes);
//	switch (szTypes[0]) {
//	case 'i':
//		tmp = va_arg(vl, int);
//		char sqlRequest[requestSize];
//		sprintf_s(sqlRequest, requestSize,
//			"CREATE TABLE IF NOT EXISTS ConnectDateForDeviceId%i(Hours INTEGER, Minutes INTEGER, Day INTEGER, Month INTEGER, Year INTEGER)",
//			tmp);
//		sqlite3_exec(m_pDataBaseHandle, sqlRequest, 0, 0, &m_pErrorDataBase);
//		SYSTEMTIME   lpSystemTime, lt;
//		GetSystemTime(&lpSystemTime);
//		sprintf_s(sqlRequest, requestSize, "INSERT INTO ConnectDateForDeviceId%i VALUES(%u,%u,%u,%u,%u)", tmp,
//			lpSystemTime.wHour + 3, lpSystemTime.wMinute, lpSystemTime.wDay, lpSystemTime.wMonth, lpSystemTime.wYear);
//		sqlite3_exec(m_pDataBaseHandle, sqlRequest, 0, 0, &m_pErrorDataBase);
//		break;
//	case 's':
//		if (szTypes[1] == 0)
//		{
//			sqlite3_prepare16_v2(m_pDataBaseHandle, L"SELECT id FROM USBDeviceBase WHERE SerialNum = ?;\0", -1, &m_pResultSelect, nullptr);
//			sqlite3_bind_text16(m_pResultSelect, 1, va_arg(vl, wchar_t*), -1, nullptr);
//			while (sqlite3_step(m_pResultSelect) == SQLITE_ROW) {
//				id = sqlite3_column_int(m_pResultSelect, 0);
//			}
//			sqlite3_finalize(m_pResultSelect);
//		}
//		else
//		{
//			sqlite3_prepare16_v2(m_pDataBaseHandle, L"INSERT INTO USBDeviceBase (DeviceName, SerialNum) VALUES(?,?);\0", -1, &m_pResultSelect, nullptr);
//			sqlite3_bind_text16(m_pResultSelect, 1, va_arg(vl, wchar_t*), -1, nullptr);
//			sqlite3_bind_text16(m_pResultSelect, 2, va_arg(vl, wchar_t*), -1, nullptr);
//			sqlite3_step(m_pResultSelect);
//			sqlite3_finalize(m_pResultSelect);
//		}
//		break;
//
//	default:
//		break;
//	}
//	va_end(vl);
//	return id;
//}

sqlite3_stmt* CDataBaseWrapper::SQLPrepareStatement(const wchar_t* sqlRequest, int argc, bool bBindInt, va_list vl)
{
	sqlite3_stmt* m_pResultSelect;
	char* m_pErrorDataBase = 0;
	int i = 0;
	int sqlResult = 0;
	
	sqlite3_prepare16_v2(m_pDataBaseHandle, sqlRequest, -1, &m_pResultSelect, nullptr);
	while (i != argc)
	{
		i++;
		if (bBindInt)
		{
			sqlite3_bind_int(m_pResultSelect, 1, va_arg(vl, int));
		}
		else
		{
			sqlite3_bind_text16(m_pResultSelect, i, va_arg(vl, wchar_t*), -1, nullptr);
		}
	}
	return m_pResultSelect;
}




	//for (auto i : setOfId)
	//{
	//	sqlite3_prepare16_v2(m_pDataBaseHandle, __SELECTINFO__, -1, &m_pResultSelect, nullptr);
	//	sqlite3_bind_int(m_pResultSelect, 1, i);
	//	sqlite3_step(m_pResultSelect);	
	//	std::wstring a((const wchar_t*)sqlite3_column_text16(m_pResultSelect, 0));
	//	vectorOfSerialNumber.push_back(a);
	//	sqlite3_finalize(m_pResultSelect);
	//}