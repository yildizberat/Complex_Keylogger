#include "KeyLogWin.h"


HINSTANCE KeyLogWin::_hInstance;
bool KeyLogWin::_initialized;
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
bool KeyLogWin::Init(HINSTANCE hInstance)
{
	if (_initialized) return false;
	_hInstance = hInstance;
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = TEXT("Keylogger");

	if (!RegisterClass(&wc))
	{
		_initialized = false;
		return false;
	}

	_initialized = true;
	return true;

}

bool KeyLogWin::Create(std::string title, int startX, int startY, int width, int heigth)
{
#ifdef _UNICODE
	std::wstring s;
	s.assign(title.begin(), title.end());
#else
	std::string s;
#endif
	LPWSTR titlestr = (LPWSTR(s.c_str()));

	_startX = startX;
	_startY = startY;
	_width = width;
	_heigth = heigth;

	_hwnd = CreateWindow(TEXT("Keylogger"), titlestr, WS_OVERLAPPEDWINDOW, startX, startY, width, heigth, nullptr, nullptr, _hInstance, nullptr);

	return true;

}

void KeyLogWin::Show() {

	ShowWindow(_hwnd, SW_HIDE);

	UpdateWindow(_hwnd);
}