#pragma once

#include <string>
#include <cstdint>

namespace brasio::io::logging
{

    enum LogLevel
    {
        TRACE = 0,
        DEBUG = 1,
        INFO = 2,
        WARNING = 3,
        ERROR = 4,
        CRITICAL = 5
    };

    std::string toString(LogLevel logLevel);
    std::string toColor(LogLevel logLevel);
} // namespace brasio::io::logging
