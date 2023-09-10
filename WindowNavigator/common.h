#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <filesystem>

#define FMT_HEADER_ONLY
#include <conio.h>
#include <Windows.h>
#include <fmt/core.h>

namespace fs = std::filesystem;
typedef std::tuple<HWND, std::string, fs::path> WindowInfo;