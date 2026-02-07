#include <io/files/stat-utils.hh>

#include <chrono>

std::string StatUtils::writeTimeToString(const fs::path &filePath)
{
    if (!fs::exists(filePath))
    {
        return "null";
    }
    auto fileWriteTime = fs::last_write_time(filePath);
    auto systemClockWriteTime =
        std::chrono::clock_cast<std::chrono::system_clock>(fileWriteTime);
    std::time_t structTimePoint =
        std::chrono::system_clock::to_time_t(systemClockWriteTime);
    std::string res = std::ctime(&structTimePoint);
    return res.substr(0, res.length() - 1);
}
