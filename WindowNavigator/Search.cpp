#include "Search.h"

namespace search {
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

		int pressed = '\0';
		while (true) {
			auto windows = window::getWindows();
			std::map<WindowInfo, float> distances;

			for (const auto& w : windows) {
				auto& [_, title, path] = w;
				distances[w] = 0.5f * levenshteinDistance(liveBuffer, title) +
					0.5f * levenshteinDistance(liveBuffer, path.filename().replace_extension().string());
			}

			std::sort(windows.begin(), windows.end(), [&](const WindowInfo& w1, const WindowInfo& w2) {
				return distances[w1] < distances[w2];
				});

			for (int i = 0; i < std::min<int>(windows.size(), 10); ++i) {
				auto& [_, title, path] = windows[i];
				// std::cout << title << " ~ " << path.filename().string() << " " << distances[windows[i]] << std::endl;
				fmt::println("{}: {} ~ {}", i+1, title, path.filename().string());
			}

			fmt::print("> {}", liveBuffer);
			pressed = _getch();
			std::fflush(stdin);
			
			if (pressed < 0)
				continue;

			std::fflush(stdout);
			system("cls");
			std::fflush(stdout);

			if (pressed == 8 && liveBuffer.size() > 0)  // backspace
				liveBuffer.pop_back();
			else if (pressed == 13 && windows.size() > 0) {  // enter
				HWND first = std::get<0>(windows.front());
				window::setActiveWindow(first);
				window::hideWindow(GetConsoleWindow());
				liveBuffer.clear();
			} else if (isprint(pressed))
				liveBuffer += pressed;
		}
	}
};