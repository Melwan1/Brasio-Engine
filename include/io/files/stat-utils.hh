#pragma once

#include <filesystem>

namespace fs = std::filesystem;

class StatUtils
{
public:
    static std::string writeTimeToString(const fs::path &filePath);
};
