#pragma once

#include <filesystem>

namespace fs = std::filesystem;

namespace brasio::io::files
{

    class StatUtils
    {
    public:
        static std::string writeTimeToString(const fs::path &filePath);
    };
} // namespace brasio::io::files
