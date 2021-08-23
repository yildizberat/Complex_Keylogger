#pragma once
#include<Windows.h>
#include<iostream>
class KeyLogWin
{
public:
	static bool Init(HINSTANCE hInstance);

	bool Create(std::string title, int startX, int startY, int width, int heigth);
	void Show();


private:
	static HINSTANCE _hInstance;
	static bool _initialized;
	HWND _hwnd;
	int _startX;
	int _startY;
	int _width;
	int _heigth;


};

