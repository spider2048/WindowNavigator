#include "Window.h"
#include <optional>

BOOL CALLBACK _enumWindowsCallback(HWND hwnd, LPARAM lparam) {	
	if (!IsWindowVisible(hwnd) || !IsWindowEnabled(hwnd))
		return true;

	auto title = window::getWindowText(hwnd);
	if (title.size() == 0)
		return true;

	std::string className = window::getWindowClassName(hwnd);
	if (className.find("Windows.UI.Core.CoreWindow") != -1)
		return true;

	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, pid);
	if (hProcess == INVALID_HANDLE_VALUE)
		return true;

	auto windows = reinterpret_cast<std::vector<WindowInfo>*>(lparam);
	windows->emplace_back(hwnd, title, window::getProcessName(hProcess));
	return true;
}

namespace window {
	std::vector<WindowInfo> getWindows() {
		std::vector<WindowInfo> windows;
		EnumWindows(_enumWindowsCallback, (LPARAM)&windows);
		return windows;
	}

	void setActiveWindow(HWND hwnd) {
		LockSetForegroundWindow(LSFW_UNLOCK);

		WINDOWPLACEMENT wp;
		memset(&wp, 0, sizeof(wp));
		wp.length = sizeof(wp);

		GetWindowPlacement(hwnd, &wp);
		switch (wp.showCmd) {
		case SW_HIDE:
		case SW_MINIMIZE:
			ShowWindow(hwnd, SW_NORMAL);
		}

		SetForegroundWindow(hwnd);
	}

	void hideWindow(HWND hwnd) {
		ShowWindow(hwnd, SW_HIDE);
	}

	std::string getWindowText(HWND hwnd) {
		int len = 1 + GetWindowTextLengthA(hwnd);
		if (len == 1)
			return "";

		std::string title(len, '\0');
		GetWindowTextA(hwnd, const_cast<char*>(title.c_str()), len);
		return title;
	}

	std::string getWindowClassName(HWND hwnd) {
		std::string className(256, '\0');
		GetClassNameA(hwnd, const_cast<char*>(className.c_str()), 256);
		return className;
	}

	fs::path getProcessName(HANDLE hProcess) {
		std::string processName(256, '\0');
		DWORD processNameLen = 256;
		QueryFullProcessImageNameA(hProcess, NULL, const_cast<char*>(processName.c_str()), &processNameLen);
		processName.resize(processNameLen);
		return fs::path(processName);
	}
};