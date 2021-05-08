#include "USBInfo.h"
#include <string>
//Реализация конструкторов класса CUsbInfoRetrieved
CUsbInfoRetrieved::CUsbInfoRetrieved(wchar_t* usbInfo) :m_pDeviceName(nullptr), m_pSerialNumber(nullptr)
{
	TakeDeviceInfo(usbInfo);
}

CUsbInfoRetrieved::~CUsbInfoRetrieved()
{
	m_pDeviceName = nullptr;
	m_pSerialNumber = nullptr;
}

CUsbInfoRetrieved::CUsbInfoRetrieved(const CUsbInfoRetrieved& other)
{
	m_pDeviceName = other.m_pDeviceName;
	m_pSerialNumber = other.m_pSerialNumber;
}

const CUsbInfoRetrieved& CUsbInfoRetrieved::operator=(const CUsbInfoRetrieved& other)
{
	if (&other == this)
		return *this;
	m_pDeviceName = other.m_pDeviceName;
	m_pSerialNumber = other.m_pSerialNumber;
	return *this;
}

CUsbInfoRetrieved::CUsbInfoRetrieved(CUsbInfoRetrieved&& other) noexcept
{
	m_pDeviceName = other.m_pDeviceName;
	m_pSerialNumber = other.m_pSerialNumber;
	other.m_pDeviceName = nullptr;
	other.m_pSerialNumber = nullptr;
}

const CUsbInfoRetrieved& CUsbInfoRetrieved::operator=(CUsbInfoRetrieved&& other) noexcept
{
	if (&other == this)
		return *this;

	m_pDeviceName = other.m_pDeviceName;
	m_pSerialNumber = other.m_pSerialNumber;
	other.m_pDeviceName = nullptr;
	other.m_pSerialNumber = nullptr;
	return *this;
}
//__________________________________________________________
//Функция получения имени и серийного номера USB накопителя
void CUsbInfoRetrieved::TakeDeviceInfo(wchar_t* usbInfo) noexcept
{
	wchar_t* word = nullptr;
	wchar_t* pPos = nullptr;
	word = wcstok_s(usbInfo, L"\\?'\'#", &pPos);
	m_pDeviceName = wcstok_s(nullptr, L"\\?'\'#", &pPos);
	m_pSerialNumber = wcstok_s(nullptr, L"\\?'\'#", &pPos);
}
//Функция получения имени устройства
wchar_t const* const CUsbInfoRetrieved::GetDeviceName() const noexcept
{
	return m_pDeviceName;
}
//Функция получения серийного номера устройства
wchar_t const* const CUsbInfoRetrieved::GetSerialNumber() const noexcept
{
	return m_pSerialNumber;
}