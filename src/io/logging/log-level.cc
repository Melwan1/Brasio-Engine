#include <io/logging/log-level.hh>

#include <map>

#include <io/escapes/ansi-escapes.hh>

std::string toString(LogLevel logLevel)
{
    static std::map<LogLevel, std::string> map = {
        { LogLevel::TRACE, "TRACE" }, { LogLevel::DEBUG, "DEBUG" },
        { LogLevel::INFO, "INFO" },   { LogLevel::WARNING, "WARNING" },
        { LogLevel::ERROR, "ERROR" }, { LogLevel::CRITICAL, "CRITICAL" }
    };
    return map.at(logLevel);
}

std::string toColor(LogLevel logLevel)
{
    static std::map<LogLevel, std::string> map = {
        { LogLevel::TRACE, FG_ESC(0) },   { LogLevel::DEBUG, FG_ESC(21) },
        { LogLevel::INFO, FG_ESC(14) },   { LogLevel::WARNING, FG_ESC(202) },
        { LogLevel::ERROR, FG_ESC(196) }, { LogLevel::CRITICAL, FG_ESC(52) }
    };
    return map.at(logLevel);
}
