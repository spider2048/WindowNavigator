#pragma once
#include "common.h"

namespace window {
	std::vector<WindowInfo> getWindows();
	void hideWindow(HWND hwnd);
	void setActiveWindow(HWND hwnd);
	std::string getWindowText(HWND hwnd);
	std::string getWindowClassName(HWND hwnd);
	fs::path getProcessName(HANDLE hProcess);
};