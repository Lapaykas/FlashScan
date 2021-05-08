#pragma once
class CUsbInfoRetrieved
{
public:
	//Перечень конструкторов класса UsbInfo
	CUsbInfoRetrieved(wchar_t* usbInfo);
	~CUsbInfoRetrieved();
	CUsbInfoRetrieved(const CUsbInfoRetrieved&);
	const CUsbInfoRetrieved& operator=(const CUsbInfoRetrieved&);
	CUsbInfoRetrieved(CUsbInfoRetrieved&&) noexcept;
	const CUsbInfoRetrieved& operator=(CUsbInfoRetrieved&&) noexcept;
	//___________________________________________

	void TakeDeviceInfo(wchar_t* usbInfo) noexcept;
	wchar_t const* const GetDeviceName() const noexcept;
	wchar_t const* const GetSerialNumber() const noexcept;
private:
	wchar_t* m_pDeviceName;
	wchar_t* m_pSerialNumber;
};


