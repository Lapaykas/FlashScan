#include "DataBase.h"
#include <iostream>
DataBase::DataBase(): resultSelect(nullptr), db(nullptr), err(nullptr), 
					needToAdd(true),deviceName(nullptr), serialNumber(nullptr) 						
{
	sqlite3_open("UsbDevices.db", &db);
	const char* sql = "CREATE TABLE IF NOT EXISTS USBDeviceBase(Name,SerialNum)";
	if (sqlite3_exec(db, sql, 0, 0, &err))
		{
		fprintf(stderr, "Ошибка SQL: %sn", err);
		sqlite3_free(err);
		}
		//fprintf(stderr, "Ошибка открытия/создания БД: %s\n", sqlite3_errmsg(db));
}

DataBase::~DataBase()
{
	sqlite3_close(db);
}

void DataBase::AddDataToDataBase(wchar_t *usbInfo) noexcept
{
	if (usbInfo == nullptr) 
		return;
	GetDeviceInfo(usbInfo);
	const char* sql_request = GetSQLRequest();

	sqlite3_prepare(db, "SELECT SerialNum FROM USBDeviceBase", -1, &resultSelect, NULL);
	while (sqlite3_step(resultSelect) == SQLITE_ROW)
	{
		unsigned const char* a = sqlite3_column_text(resultSelect, 0);
		if (strcmp(reinterpret_cast<const char*>(a),Wchar_tToChar(serialNumber))!=0) 
			needToAdd = true;
		else 
			needToAdd = false;
	}
	if (needToAdd)(sqlite3_exec(db, sql_request, 0, 0, &err));

}

char* DataBase::Wchar_tToChar(wchar_t* tmp) const noexcept
{
	size_t origsize = wcslen(tmp) + 1;
	size_t convertedChars = 0;
	const size_t newsize = origsize * 2;
	char* dstChar = new(std::nothrow) char[newsize]; //текучка памяти
	wcstombs_s(&convertedChars, dstChar, newsize, tmp, _TRUNCATE);
	return dstChar;
}

void DataBase::GetDeviceInfo(wchar_t* usbInfo) noexcept
{
	wchar_t* word = nullptr;
	wchar_t* pPos = nullptr;
	word = wcstok_s(usbInfo, L"\\?'\'#", &pPos);
	deviceName = wcstok_s(NULL, L"\\?'\'#", &pPos);
	serialNumber = wcstok_s(NULL, L"\\?'\'#", &pPos);
}

const char* DataBase::GetSQLRequest() const noexcept
{
	wchar_t sql[256];
	swprintf_s(sql, L"INSERT INTO USBDeviceBase VALUES('%s','%s');", deviceName, serialNumber);
	//перевод в char полученного sql запроса
	size_t origsize = wcslen(sql) + 1;
	size_t convertedChars = 0;
	const size_t newsize = origsize * 2;
	char* nstring = new char[newsize];
	wcstombs_s(&convertedChars, nstring, newsize, sql, _TRUNCATE);
	const char* sql_request = nstring;

	return sql_request;
}

//static int callback(void* data, int argc, char** argv, char** azColName)
//{
//	for (int i = 0; i < argc; i )
//	{
//		char* a = argv[i];
//		char* b = Base.Wchar_tToChar(serialNumber);
//		if (*a == *b) needToAdd = false;
//		else needToAdd = true;
//	}
//	return 0;
//}