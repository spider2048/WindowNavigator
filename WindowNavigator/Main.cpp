#include "common.h"
#include "Search.h"
#include "Window.h"

void handleWindowEvents() {
	HWND currentWindow = GetConsoleWindow();
	while (true) {
		if (GetKeyState(VK_F7) & 0x8000) {
			ShowWindow(currentWindow, SW_RESTORE);
			while (GetForegroundWindow() != currentWindow)
				SetForegroundWindow(currentWindow);
			LockSetForegroundWindow(LSFW_LOCK);
		}

		Sleep(100);
	}
}

int main() {
	std::thread t(search::liveSearch);
	t.detach();
	handleWindowEvents();
}
