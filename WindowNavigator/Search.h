#pragma once
#include "common.h"
#include "Window.h"

namespace search {
	float levenshteinDistance(const std::string& word1, const std::string& word2);
	void liveSearch();
};