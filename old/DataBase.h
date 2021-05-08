#pragma once
#include  "./SQLlite/sqlite3.h" 

class DataBase //переименовать нормально
{
public:
	DataBase();
	~DataBase();
	void AddDataToDataBase(wchar_t *usbInfo) noexcept;
private:
	char* Wchar_tToChar(wchar_t* tmp) const noexcept;
	void GetDeviceInfo(wchar_t* usbInfo) noexcept;
	const char* GetSQLRequest() const noexcept;

	sqlite3_stmt* resultSelect;
	sqlite3* db = 0; 
	char* err = 0;
	bool needToAdd;
	wchar_t* deviceName;
	wchar_t* serialNumber;
};

//сделать класс, получающий имя и серийник
//добавить дополнительную таблицу с временем подключения флешек

