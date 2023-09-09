#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <filesystem>

#include <conio.h>
#include <Windows.h>

namespace fs = std::filesystem;
typedef std::tuple<HWND, std::string, fs::path> WindowInfo;

BOOL CALLBACK _enumWindowsCallback(HWND hwnd, LPARAM lparam) {
	int len = 1 + GetWindowTextLengthA(hwnd);
	if (len == 1)
		return true;

	if (!IsWindowVisible(hwnd))
		return true;

	std::string title;
	title.resize(len);
	GetWindowTextA(hwnd, const_cast<char*>(title.c_str()), len);

	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);

	HANDLE hProcess = OpenProcess(
		PROCESS_QUERY_LIMITED_INFORMATION, false, pid
	);

	if (hProcess == INVALID_HANDLE_VALUE) {
		return true;
	}

	std::string processName;
	processName.resize(256);
	DWORD processNameLen = 256;
	QueryFullProcessImageNameA(hProcess, NULL, const_cast<char*>(processName.c_str()), &processNameLen);
	processName.resize(processNameLen);

	auto windows = reinterpret_cast<std::vector<WindowInfo>*>(lparam);
	windows->emplace_back(hwnd, title, processName);
	return true;
}

std::vector<WindowInfo> getWindows() {
	std::vector<WindowInfo> windows;
	EnumDesktopWindows(NULL, _enumWindowsCallback, (LPARAM)&windows);
	return windows;
}


float levenshteinDistance(const std::string& word1, const std::string& word2) {
	int m = word1.length();
	int n = word2.length();

	std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

	for (int i = 0; i <= m; ++i) {
		dp[i][0] = i;
	}

	for (int j = 0; j <= n; ++j) {
		dp[0][j] = j;
	}

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			int cost = (tolower(word1[i - 1]) == tolower(word2[j - 1])) ? 0 : 1;
			dp[i][j] = std::min<int>({
				dp[i - 1][j] + 1,
				dp[i][j - 1] + 1,
				dp[i - 1][j - 1] + cost
				});
		}
	}

	return (float)dp[m][n] / std::max<float>(m, n);
}

void liveSearch() {
	std::string liveBuffer;

	char pressed = '\0';
	while (true) {
		auto windows = getWindows();
		std::map<WindowInfo, float> distances;

		for (const auto& w : windows) {
			auto& [_, title, path] = w;
			distances[w] = 0.8f * levenshteinDistance(liveBuffer, title) +
				0.2f * levenshteinDistance(liveBuffer, path.filename().string());
		}

		std::sort(windows.begin(), windows.end(), [&](const WindowInfo& w1, const WindowInfo& w2) {
			return distances[w1] < distances[w2];
			});

		for (int i = 0; i < std::min<int>(windows.size(), 10); ++i) {
			auto& [_, title, path] = windows[i];
			std::cout << title << " " << path << std::endl;
		}

		std::cout << "> " << liveBuffer;
		pressed = _getch();
		system("cls");
		if (pressed == 8 && liveBuffer.size() > 0) {
			liveBuffer.pop_back();
		}
		else liveBuffer += pressed;

		if (pressed == 13) {
			HWND first = std::get<0>(windows.front());
			LockSetForegroundWindow(LSFW_UNLOCK);
			SetForegroundWindow(first);
			SetActiveWindow(first);
			ShowWindow(GetConsoleWindow(), SW_HIDE);
			liveBuffer.clear();
		}

	}
}

void handleWindowEvents() {
	HWND currentWindow = GetConsoleWindow();
	while (true) {
		if (GetKeyState(VK_F2) & 0x8000) {
			ShowWindow(currentWindow, SW_RESTORE);
			while (GetForegroundWindow() != currentWindow)
				SetForegroundWindow(currentWindow);
			LockSetForegroundWindow(LSFW_LOCK);
		}

		Sleep(100);
	}
}
int main() {
	std::thread t(liveSearch);
	t.detach();
	handleWindowEvents();
}
